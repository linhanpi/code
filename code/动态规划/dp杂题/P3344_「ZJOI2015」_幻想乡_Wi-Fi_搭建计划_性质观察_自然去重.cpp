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
const int N=1e2+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
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
struct node{
    int x,y,id;
}jd[N],wl[N];
int dp[N][N][N];
inline double uj(node x,node y){
    return sqrt(fang(x.x-y.x)+fang(x.y-y.y));
}
bool operator <(const node &x,const node &y){
    if(x.id!=y.id)return x.id<y.id;
    return x.x<y.x;
}
signed main(){
	int n=read(),m=read(),R=read();
    for(int i=1;i<=n;i++){
        jd[i].x=read(),jd[i].y=read();
    }
    for(int i=1;i<=m;i++){
        wl[i].x=read(),wl[i].y=read(),wl[i].id=read();
    }
    int tot=n;
    for(int i=1;i<=n;i++){
        bool flag=1;
        for(int j=1;j<=m;j++){
            if(uj(jd[i],wl[j])<=R){
                flag=0;
            }
        }
        if(flag){
            tot--;
            jd[i].id=1;
        }
    }
    sort(jd+1,jd+n+1);
    n=tot;
    cout<<tot<<endl;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=m;k++){
                for(int t=1;t<=m;t++){
                    if(uj(jd[i+1],wl[t])<=R){
                        if(wl[t].y>R)dp[i+1][j][t]=min(dp[i+1][j][t],dp[i][j][k]+(k!=t)*wl[t].id);
                        else dp[i+1][t][k]=min(dp[i+1][t][k],dp[i][j][k]+(j!=t)*wl[t].id);
                    }
                }
            }
        }
    }
    int ans=inf;
    for(int i=0;i<=m;i++){
        for(int j=0;j<=m;j++){
            ans=min(ans,dp[n][i][j]);
        }
    }
    cout<<ans<<endl;
	return 0;
}
