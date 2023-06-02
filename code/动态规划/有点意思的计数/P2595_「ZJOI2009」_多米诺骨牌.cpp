#include<bits/stdc++.h>
#define int long long//信仰
// #define uint unsigned int
// #define rint register int
// #define ll long long
// #define double long double
#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=20+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=19901013;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
int n,m;
int tmp[2][1<<16],dp[N][N][N][N],g[N][N],f[N];
bool mp[N][N];
void js(int xs,int ys,int xz){
    // cout<<"xs ys xz "<<xs<<" "<<ys<<" "<<xz<<endl;
    int maxs=(1<<xz-xs+1)-1;
    for(int st=0;st<=maxs;st++)tmp[0][st]=0;
    tmp[0][maxs]=1;
    int lp=0,np=1;
    for(int i=ys;i<=n;i++){
        for(int j=xs;j<=xz;j++){
            for(int st=0;st<=maxs;st++)tmp[np][st]=0;
            for(int st=0;st<=maxs;st++){
                // cout<<i<<" "<<j<<" "<<st<<endl;
                if(!tmp[lp][st])continue;
                if(!(st&(1<<xz-xs))&&mp[i][j]&&mp[i-1][j]){
                    tmp[np][(st<<1)&maxs|1]=mjia(tmp[np][(st<<1)&maxs|1],tmp[lp][st]);
                }
                if(!(st&1)&&mp[i][j]&&j>xs&&mp[i][j-1]){
                    tmp[np][(st<<1)&maxs|3]=mjia(tmp[np][(st<<1)&maxs|3],tmp[lp][st]);
                }
                tmp[np][(st<<1)&maxs]=mjia(tmp[np][(st<<1)&maxs],tmp[lp][st]);
            }
            if(j==xz){
                for(int st=0;st<=maxs;st++)dp[xs][ys][xz][i]=mjia(dp[xs][ys][xz][i],tmp[np][st]);
            }
            lp^=1,np^=1;
        }
    }
    return ;
}
char s[N];
int l[N],r[N],cnt;
signed main(){
	n=read(),m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++){
            mp[i][j]=(s[j]=='.');
        }
    }
    // cout<<1<<endl;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int k=i;k<=m;k++){
                js(i,j,k);
            }
        }
    }
    // cout<<1<<endl;
    int ans=0;
    for(int i=0;i<=(1<<m-1)-1;i++){
        memset(g,0,sizeof(g));
        memset(f,0,sizeof(f));
        cnt=0;
        l[++cnt]=1;
        int ret=1,tep=i;
        while(tep){
            if(tep&1){
                r[cnt]=ret;
                l[++cnt]=ret+1;
            }
            tep>>=1;
            ret++;
        }
        r[cnt]=m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                g[i][j]=1;
                for(int k=1;k<=cnt;k++){
                    g[i][j]=mcheng(g[i][j],dp[l[k]][i][r[k]][j]);
                }
            }
        }
        f[1]=g[1][1];
        for(int i=2;i<=n;i++){
            f[i]=g[1][i];
            for(int j=2;j<=i;j++){
                f[i]=mjian(f[i],mcheng(f[j-1],g[j][i]));
            }
        }
        if(cnt&1)ans=mjia(ans,f[n]);
        else ans=mjian(ans,f[n]);
    }
    cout<<ans<<endl;
	return 0;
}
