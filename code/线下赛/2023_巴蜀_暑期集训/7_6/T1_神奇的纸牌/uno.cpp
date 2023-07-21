#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned long long
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
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}
int n,p;
inline int P(int n,int m){
    int res=1;
    for(int i=n;i>=n-m+1;i--){
        res=(res*i)%p;
    }
    return res;
}
queue <int> q;
int you[6];
int c[20][20];
void ycl(){
    c[0][0]=1;
    for(int i=1;i<=18;i++){
        c[0][i]=1;
        for(int j=1;j<=i;j++){
            c[j][i]=(c[j-1][i-1]+c[j][i-1])%p;
        }
    }
    return ;
}
int youu;
int mp[6][6];
int vis[6],viss[6];
void bfs(){
    q.push(youu);
    memset(vis,0,sizeof(vis));
    while(!q.empty()){
        int now=q.front();
        q.pop();
        vis[now]=1;
        for(int i=1;i<=4;i++){
            if(vis[i]||(!mp[now][i]))continue;
            q.push(i);
        }
    }
    return ;
}
int f[20];
signed main(){
    freopen("uno.in","r",stdin);
    freopen("uno.out","w",stdout);
	n=read(),p=read();
    ycl();
    for(int i=1;i<=16;i++){
        for(int j=0;j<=i;j++){
            f[i]=(f[i]+((j&1)?(p-c[i-j][i]*qmi(i-j+1,n,p)%p):c[i-j][i]*qmi(i-j+1,n,p)%p))%p;
        }
    }
    int ans=1;
    for(int st=1;st<(1<<15);st++){
        memset(mp,0,sizeof(mp));
        memset(viss,0,sizeof(viss));
        youu=0;
        int tep=st;
        int cn=0,tot=0;
        while(tep){
            ++tot;
            if(tep&1){
                memset(you,0,sizeof(you));
                cn++;
                int tmp=tot;
                int tott=0;
                while(tmp){
                    ++tott;
                    if(tmp&1){
                        youu=tott;
                        viss[tott]=1;
                        you[tott]=1;
                    }
                    tmp>>=1;
                }
                for(int i=1;i<=4;i++){
                    for(int j=i+1;j<=4;j++){
                        if(you[i]&&you[j]){
                            mp[i][j]=mp[j][i]=1;
                        }
                    }
                }
            }
            tep>>=1;
        }
        if(cn>n)continue;
        bfs();
        bool flag=0;
        for(int i=1;i<=4;i++){
            if(viss[i]&&(!vis[i])){
                flag=1;
                break;
            }
        }
        if(flag){
            continue;
        }
        ans=(ans+f[cn]%p)%p;
    }
    cout<<ans<<endl;
	return 0;
}
/*
2 114514
*/
/*
1 114514
*/