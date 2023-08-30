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
const int N=1e3+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e9+7;
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
    int dao,liu,fan;
};
vector <biandata> v[N];
inline void jiabian(int x,int y,int f){
    v[x].push_back({y,f,(int)v[y].size()});
    v[y].push_back({x,0,(int)v[x].size()-1});
    return ;
}
int deep[N],gap[N],nowhu[N];
int st,ed,tot;
int maxflow;
void bfs(){
    memset(deep,-1,sizeof(deep));
    memset(gap,0,sizeof(gap));
    queue <int> q;
    deep[ed]=0;
    gap[0]=1;
    q.push(ed);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(biandata it:v[now]){
            int y=it.dao;
            if(~deep[y])continue;
            deep[y]=deep[now]+1;
            gap[deep[y]]++;
            q.push(y);
        }
    }
    return ;
}
int dfs(int now,int flow){
    if(now==ed){
        maxflow+=flow;
        return flow;
    }
    int used=0;
    for(int i=nowhu[now];i<(int)v[now].size();i++){
        nowhu[now]=i;
        int y=v[now][i].dao;
        if(!v[now][i].liu||deep[y]+1!=deep[now])continue;
        int maxn=dfs(y,min(v[now][i].liu,flow-used));
        if(maxn){
            v[now][i].liu-=maxn;
            v[y][v[now][i].fan].liu+=maxn;
            used+=maxn;
        }
        if(used==flow)return used;    
    }
    --gap[deep[now]];
    if(!gap[deep[now]])deep[st]=tot+1;
    deep[now]++;
    gap[deep[now]]++;
    return used;
}
void ISAP(){
    maxflow=0;
    bfs();
    while(deep[st]<tot){
        memset(nowhu,0,sizeof(nowhu));
        dfs(st,inf);
    }
    return ;
}
int quan[N],ke[N][2];
signed main(){
    // freopen("variable.in","r",stdin);
    // freopen("variable.out","w",stdout);
	int T=read();
    while(T--){
        memset(quan,0,sizeof(quan));
        memset(ke,0,sizeof(ke));
        int n=read(),W=read(),p=read(),q=read();
        tot=n;
        st=++tot,ed=++tot;
        for(int i=1;i<=tot;i++)v[i].clear();
        for(int i=1;i<=p;i++){
            int x=read(),y=read(),z=read(),a=read(),b=read(),c=read(),d=read(),e=read(),f=read();
            quan[x]+=d-f;
            quan[y]+=e-d;
            quan[z]+=f-e;
            jiabian(x,y,2*a);
            jiabian(y,x,2*a);
            jiabian(x,z,2*c);
            jiabian(z,x,2*c);
            jiabian(y,z,2*b);
            jiabian(z,y,2*b);
        }
        for(int i=1;i<=q;i++){
            int x=read(),y=read(),op=read();
            if(op==2){
                ke[y][1]=1;
                ke[x][0]=1;
            }
            if(op==1){
                jiabian(x,y,inf);
                jiabian(y,x,inf);
            }
            if(op==0){
                jiabian(y,x,inf);
            }
        }
        for(int i=1;i<=n;i++){
            if(ke[i][0])jiabian(st,i,inf);
            jiabian(i,ed,-quan[i]-1);
            if(ke[i][1])jiabian(i,ed,inf);
            jiabian(st,i,quan[i]+1);
        }
        ISAP();
        // maxflow-=1e6*n;
        cout<<maxflow*W<<endl;
    }
	return 0;
}
