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
const int N=1e3+5;
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
int n,m;
struct node{
    int dao,id;
};
vector <node> vv[N];
vector <int> v[N];
vector <int> scc[N];
int low[N],dfn[N],ins[N],c[N],sta[N];
int cnt,top,num;
void tarjan(int now){
    low[now]=dfn[now]=++num;
    sta[++top]=now;
    ins[now]=1;
    for(int y:v[now]){
        if(!dfn[y]){
            tarjan(y);
            low[now]=min(low[now],low[y]);
        }
        else if(ins[y])low[now]=min(low[now],low[y]);
    }
    if(dfn[now]==low[now]){
        ++cnt;int y;
        do{
            y=sta[top--];
            ins[y]=0;
            scc[cnt].push_back(y);
            c[y]=cnt;
        }while(y!=now);
    }
    return ;
}
bitset <N> dao[N],vis;
int noww;
void dfs(int now){
    vis[now]=1;
    if(now==noww)return ;
    while(1){
        bitset <N> out=~vis&dao[now];
        int p=out._Find_first();
        if(p==N)break;
        dfs(p);
    }
    return ;
}
int ans[200005];
signed main(){
	n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        vv[a].push_back({b,i});
        dao[a][b]=1;
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])tarjan(i);
    }
    for(int i=1;i<=n;i++){
        noww=i;
        vis.reset();
        for(node it:vv[i]){
            int y=it.dao;
            if(vis[y])ans[it.id]=1;
            else dfs(y);
        }
        reverse(vv[i].begin(),vv[i].end());
        vis.reset();
        for(node it:vv[i]){
            int y=it.dao;
            if(vis[y])ans[it.id]=1;
            else dfs(y);
        }
    }
    // for(int i=1;i<=m;i++){
    //     cout<<(ans[i]?"same":"diff")<<endl;
    // }
    for(int i=1;i<=n;i++){
        for(node it:vv[i]){
            if(c[i]^c[it.dao]){
                ans[it.id]^=1;
            }
        }
    }
    for(int i=1;i<=m;i++){
        cout<<(ans[i]?"same":"diff")<<endl;
    }
    return 0;
}
