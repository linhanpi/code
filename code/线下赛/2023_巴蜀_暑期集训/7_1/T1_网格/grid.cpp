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
const int M=5e6+5;
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
struct node{
    int x,y,t;
    node(){}
    node(int x,int y,int t):x(x),y(y),t(t){}
}a[N];
int t,q;
int n,m,c;
bool cmp1(const node&a,const node&b){
    return a.x==b.x?(a.y==b.y?a.t<b.t:a.y<b.y):a.x<b.x;
}
bool cmp2(const node&a,const node&b){
    return a.y==b.y?a.x<b.x:a.y<b.y;
}
vector<int> v[N];
int dfn[N],low[N],fa[N],num;
bool you;
void tarjan(int u){
    dfn[u]=low[u]=++num;
    int cnt=0;
    for(int i=0;i<(int)v[u].size();i++){
        int y=v[u][i];
        if(!dfn[y]){
            fa[y]=u;
            tarjan(y);
            low[u]=min(low[u],low[y]);
            if(low[y]>=dfn[u]){
                if(fa[u])you=1;
                else cnt++;
            }
        }else if(y!=fa[u])low[u]=min(low[u],dfn[y]);
    }
    if(cnt>1)you=1;
	return ;
}
void jiabian(int x,int y,int radx,int rady){
    for(int dx=-radx;dx<=radx;dx++){
        for(int dy=-rady;dy<=rady;dy++){
            int cx=x+dx,cy=y+dy;
            if(1<=cx&&cx<=n&&1<=cy&&cy<=m){
                a[++t]=node(cx,cy,0);
            }
        }
    }
	return ;
}
signed main(){
    int T=read();
    while(T--){
        cin>>n>>m>>c;
        t=q=0;
        for(int i=1;i<=c;i++){
            int x,y;cin>>x>>y;
            jiabian(x,y,1,1);
            jiabian(1,y,0,0);
			jiabian(n,y,0,0);
			jiabian(x,1,0,0);
			jiabian(x,m,0,0);
            a[++t]=node(x,y,-1);
        }
        jiabian(1,1,2,2);
		jiabian(1,m,2,2);
		jiabian(n,1,2,2);
		jiabian(n,m,2,2);
        sort(a+1,a+1+t,cmp1);
        int cp=0;
		node buf(inf,inf,1);
        for(int i=1;i<=t;i++){
            if(a[i].x!=buf.x||a[i].y!=buf.y){
                buf=a[i];a[++cp]=buf;
            }
        }
        t=cp;
        for(int i=1;i<=t;i++)if(a[i].t!=-1)a[i].t=++q;
        for(int i=1;i<=q;i++)v[i].clear(),dfn[i]=0;
        num=0;
        for(int i=2;i<=t;i++){
            if(a[i].x==a[i-1].x&&a[i].t!=-1&&a[i-1].t!=-1){
                v[a[i].t].push_back(a[i-1].t);
                v[a[i-1].t].push_back(a[i].t);
            }
        }
        sort(a+1,a+1+t,cmp2);
        for(int i=2;i<=t;i++){
            if(a[i].y==a[i-1].y&&a[i].t!=-1&&a[i-1].t!=-1){
                v[a[i].t].push_back(a[i-1].t);
                v[a[i-1].t].push_back(a[i].t);
            }
        } 
        if(q<=1){
            cout<<-1<<'\n';
            continue;
        }
        if(q==2&&v[1].size()){
            int id[2];
            for(int i=1;i<=t;i++)if(a[i].t>=1&&a[i].t<=2)id[a[i].t-1]=i;
            if(abs(a[id[0]].x-a[id[1]].x)+abs(a[id[0]].y-a[id[1]].y)==1){
                cout<< -1<<'\n';
                continue;
            }
			else{
                cout<<1<<'\n';
                continue;
            }
        }
        you=0;
        tarjan(1);
        if(num!=q){
            cout<< 0<<'\n';
        }
		else cout<<(you?1:2)<<'\n';
    }
    return 0;
}