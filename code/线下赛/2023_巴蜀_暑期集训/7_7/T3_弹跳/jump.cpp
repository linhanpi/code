#include<bits/stdc++.h>
// #define int long long//信仰
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
const int N=70005+5;
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
int n,m,w,h;
int px[N],py[N];
set <pii> s[N<<2];
vector <int> nv[N];
struct node{
    int dis,pos;
};
bool operator <(const node &x,const node &y){
    return x.dis>y.dis;
}
priority_queue <node> q;
int dist[N<<2],vis[N<<2];
int P[N<<2],T[N<<2],L[N<<2],R[N<<2],D[N<<2],U[N<<2];
vector <int> v[N];
void gai(int p,int l,int r,int id){
    s[p].insert({py[id],id});
    if(l==r)return ;
    int mid=(l+r)>>1;
    if(px[id]<=mid)gai(lson,l,mid,id);
    else gai(rson,mid+1,r,id);
    return ;
}
void sc(int p,int l,int r,int id){
    if(L[id]<=l&&r<=R[id]){
        set<pii>::iterator it;
        while(1){
            it=s[p].lower_bound({D[id],-1});
            if(it==s[p].end()||it->first>U[id])break;
            int dao=it->second;
            if(dist[dao]>dist[id+n]){
                dist[dao]=dist[id+n];
                q.push({dist[dao],dao});
            }
            s[p].erase(it);
        }
        return ;
    }
    int mid=(l+r)>>1;
    if(L[id]<=mid)sc(lson,l,mid,id);
    if(R[id]>mid)sc(rson,mid+1,r,id);
    return ;
}
signed main(){
    // freopen("jump.in","r",stdin);
    // freopen("jump.out","w",stdout);
	n=read(),m=read(),w=read(),h=read();
    for(int i=1;i<=n;i++){
        px[i]=read(),py[i]=read();
        if(i!=1){
            gai(1,1,w,i);
        }
    }
    for(int i=1;i<=m;i++){
        P[i]=read(),T[i]=read(),L[i]=read(),R[i]=read(),D[i]=read(),U[i]=read();
        v[P[i]].push_back(i+n);
    }
    // for(int i=1;i<=n;i++)dist[i]=inf;
    memset(dist,0x3f,sizeof(dist));
    dist[1]=0;
    q.push({0,1});
    while(!q.empty()){
        node it=q.top();
        q.pop();
        int now=it.pos;
        if(vis[now])continue;
        vis[now]=1;
        if(now<=n){
            for(int y:v[now]){
                dist[y]=dist[now]+T[y-n];
                q.push({dist[y],y});
            }
        }
        else sc(1,1,w,now-n);
    }
    for(int i=2;i<=n;i++){
        write(dist[i]);
        puts("");
    }
	return 0;
}
