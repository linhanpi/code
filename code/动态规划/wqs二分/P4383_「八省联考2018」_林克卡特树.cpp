#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
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
const int inf=1e12+7;
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
struct biandata{
    int dao,quan;
};
vector <biandata> v[N];
struct dpdata{
    int res;
    int x;
}dp[N][3],g[N];
void pt(int now,int k){
    cout<<"now "<<now<<" "<<"k "<<k<<" "<<dp[now][k].res<<" "<<dp[now][k].x<<endl;
}
void ptg(int now){
    cout<<"now "<<now<<" "<<g[now].res<<" "<<g[now].x<<endl;
}
void dfs(int now,int mid,int fath){
    // dp[now][2].res=-mid,dp[now][2].x=1;
    int val=0;
    for(biandata it:v[now]){
        int y=it.dao;
        if(y==fath)continue;
        dfs(y,mid,now);
        if(g[y].res>0)dp[now][2].res+=g[y].res,dp[now][2].x+=g[y].x;
        if((val=dp[now][1].res+dp[y][1].res+it.quan-mid)>dp[now][2].res||val==dp[now][2].res&&dp[now][2].x>dp[now][1].x+dp[y][1].x+1)dp[now][2].res=val,dp[now][2].x=dp[now][1].x+dp[y][1].x+1;
        if(g[y].res>0)dp[now][1].res+=g[y].res,dp[now][1].x+=g[y].x;
        if((val=dp[now][0].res+dp[y][1].res+it.quan)>dp[now][1].res||val==dp[now][1].res&&dp[now][1].x>dp[now][0].x+dp[y][1].x)dp[now][1].res=val,dp[now][1].x=dp[now][0].x+dp[y][1].x;
        if(g[y].res>0)dp[now][0].res+=g[y].res,dp[now][0].x+=g[y].x;
    }
    if((val=dp[now][2].res)>g[now].res||val==g[now].res&&g[now].x>dp[now][2].x)g[now].res=val,g[now].x=dp[now][2].x;
    if((val=dp[now][1].res-mid)>g[now].res||val==g[now].res&&g[now].x>dp[now][1].x+1)g[now].res=val,g[now].x=dp[now][1].x+1;
    if((val=dp[now][0].res)>g[now].res||val==g[now].res&&g[now].x>dp[now][0].x)g[now].res=val,g[now].x=dp[now][0].x;
    // pt(now,0);
    // pt(now,1);
    // pt(now,2);
    // ptg(now);
    return ;
}
signed main(){
	int n=read(),k=read()+1;
    for(int i=1;i<n;i++){
        int a=read(),b=read(),w=read();
        v[a].push_back({b,w});
        v[b].push_back({a,w});
    }
    dfs(1,0,0);
    // cout<<g[1].res<<" "<<g[1].x<<endl;
    int l=-inf,r=inf,ans=0;
    while(l<r){
        memset(dp,0,sizeof(dp));
        memset(g,0,sizeof(g));
        int mid=((l+r)>>1);
        dfs(1,mid,0);
        if(g[1].x>k)l=mid+1;
        else{
            r=mid;
            ans=g[1].res+k*mid;
        }
    }
    cout<<ans<<endl;
	return 0;
}
