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
#define lson (now<<1)
#define rson (now<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e18+7;
const int base=131;
const int mod=998244353;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
struct node{
    int dao,quan;
};
vector <node> v[N],fan[N];
priority_queue <pii> q;
int lg[N],qian[N];
vector <int> you[N];
bool zai[N],vis[N];
int dist[N];
int n,m;
int ans=0;
void dfs(int now){
    you[now].push_back(now);
    if(lg[now]==n)return ;
    dfs(lson);
    dfs(rson);
    for(int y:you[lson]){
        you[now].push_back(y);
        zai[y]=1,vis[y]=0;
        dist[y]=inf;
    }
    for(int y:you[rson]){
        you[now].push_back(y);
        zai[y]=1,vis[y]=0;
        dist[y]=inf;
    }
    zai[now]=1;
    q.push({0,now});
    for(int y:you[now]){
        if(y==now)continue;
        for(node it:fan[y]){
            int z=it.dao;
            if(z>=now)continue;
            dist[y]=min(dist[y],qian[now]-qian[z]+it.quan);
            q.push({-dist[y],y});
        }
    }
    while(!q.empty()){
        pii it=q.top();
        q.pop();
        int now=it.second;
        if(vis[now])continue;
        vis[now]=1;
        for(node it:v[now]){
            int y=it.dao,w=it.quan;
            if(!zai[y])continue;
            if(dist[now]+w<dist[y]){
                dist[y]=dist[now]+w;
                q.push({-dist[y],y});
            }
        }
    }
    vis[now]=zai[now]=0;
    dist[now]=inf;
    int xl=0,xr=0,cntxl=0,cntxr=0;
    for(int y:you[lson]){
        xl=(xl+(dist[y]==inf?0:dist[y]))%mod;
        cntxl=(cntxl+(dist[y]==inf?0:1));
        vis[y]=0;
        zai[y]=0;
        dist[y]=inf;
    }
    for(int y:you[rson]){
        xr=(xr+(dist[y]==inf?0:dist[y]))%mod;
        cntxr=(cntxr+(dist[y]==inf?0:1));
        vis[y]=0;
        zai[y]=0;
        dist[y]=inf;
    }
    int sl=0,sr=0,cntsl=0,cntsr=0;
    for(int y:you[lson]){
        sl=(sl+qian[y]-qian[now])%mod;
        cntsl++;
    }
    for(int y:you[rson]){
        sr=(sr+qian[y]-qian[now])%mod;
        cntsr++;
    }
    ans=(ans+xl+xr+sl+sr+sl*cntxr%mod+xl*cntsr%mod+sr*cntxl%mod+xr*cntsl%mod)%mod;
    return ;
}
signed main(){
    freopen("trade.in","r",stdin);
    freopen("trade.out","w",stdout);
	n=read(),m=read();
    for(int i=1;i<=(1<<n)-2;i++){
        int w=read();
        v[i+1].push_back({(i+1)>>1,w});
        qian[i+1]=qian[(i+1)>>1]+w;
    }
    for(int i=1;i<=(1<<n)-2;i++){
        lg[i]=lg[i>>1]+1;
    }
    lg[(1<<n)-1]=n;
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),w=read();
        v[x].push_back({y,w});
        fan[y].push_back({x,w});
    }
    dfs(1);
    cout<<ans<<endl;
	return 0;
}
