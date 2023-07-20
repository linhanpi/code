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
const int N=4000+5;
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
int tong[N],p[N];
int dp[N][N],g[N][N],ls[N],rs[N];
vector <int> v[N];
int si[N],siz[N];
int c[N][N];
void ycl(){
    c[0][0]=1;
    for(int i=1;i<=N-5;i++){
        c[0][i]=1;
        for(int j=1;j<=i;j++){
            c[j][i]=(c[j-1][i-1]+c[j][i-1])%mod;
        }
    }
    return ;
}
void dfs(int now){
    for(int y:v[now]){
        dfs(y);
        si[now]+=si[y];
        siz[now]+=siz[y];
    }
    if(ls[now]&&rs[now]){
        for(int i=0;i<=si[ls[now]];i++){
            for(int j=0;j<=si[rs[now]];j++){
                dp[now][i+j]=(dp[now][i+j]+dp[ls[now]][i]*dp[rs[now]][j]%mod)%mod;
            }
        }
    }
    else if(ls[now]||rs[now]){
        int y=v[now][0];
        for(int i=0;i<=si[y];i++){
            dp[now][i]=dp[y][i];
        }
    }
    else{
        dp[now][0]=1;
    }
    // cout<<"----------------------------------------------\n";
    // for(int i=0;i<=si[now];i++){
    //     cout<<"now "<<now<<" "<<i<<" "<<dp[now][i]<<endl;
    // }
    // cout<<"----------------------------------------------\n";
    for(int i=0;i<=si[now];i++){
        g[now][i+1]=(g[now][i+1]+dp[now][i])%mod;
        g[now][i]=(g[now][i]+mod-dp[now][i])%mod;
    }
    si[now]++;
    memcpy(dp[now],g[now],sizeof(dp[now]));
    // cout<<"----------------------------------------------\n";
    // for(int i=0;i<=si[now];i++){
    //     cout<<"now "<<now<<" "<<i<<" "<<dp[now][i]<<endl;
    // }
    // cout<<"----------------------------------------------\n";
    // cout<<"tong "<<now<<" "<<tong[now]<<endl;
    memset(g[now],0,sizeof(g[now]));
    for(int i=0;i<=si[now];i++){
        if(!dp[now][i])continue;
        int re=1,no=tong[now];
        for(int j=0;j<=tong[now];j++){
            if(j>i)break;
            g[now][i-j]=(g[now][i-j]+dp[now][i]*re%mod*c[j][i]%mod)%mod;
            re=(re*no)%mod;
            no--;
        }
        // cout<<"i "<<i<<endl;
        // cout<<"----------------------------------------------\n";
        // for(int i=0;i<=si[now];i++){
        //     cout<<"now "<<now<<" "<<i<<" "<<g[now][i]<<endl;
        // }
        // cout<<"----------------------------------------------\n";
    }
    memcpy(dp[now],g[now],sizeof(dp[now]));
    // si[now]++;
    siz[now]+=tong[now];
    // cout<<"----------------------------------------------\n";
    // for(int i=0;i<=si[now];i++){
    //     cout<<"now "<<now<<" "<<i<<" "<<dp[now][i]<<endl;
    // }
    // cout<<"----------------------------------------------\n";
    return ;
}
signed main(){
    // freopen("he.in","r",stdin);
    // freopen("he.out","w",stdout);
    ycl();
    int n=read(),k=read();
    for(int i=1;i<=k;i++){
        p[i]=read();
        tong[p[i]]++;
    }
    for(int i=1;i<=n;i++){
        ls[i]=read();
        rs[i]=read();
        if(ls[i])v[i].push_back(ls[i]);
        if(rs[i])v[i].push_back(rs[i]);
    }
    dfs(1);
    int ans=0;
    for(int i=0;i<=n;i++){
        ans=(ans+dp[1][i])%mod;
    }
    cout<<ans<<endl;
	return 0;
}
