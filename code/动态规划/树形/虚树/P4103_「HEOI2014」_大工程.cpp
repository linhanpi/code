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
const int N=2e6+5;
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
struct yuanshu{
	int num;
	int si[N],son[N],deep[N],top[N],fa[N],dfn[N];
	vector <int> v[N];
	void dfs1(int now,int fath){
		si[now]=1,fa[now]=fath;
		deep[now]=deep[fath]+1;
		for(int y:v[now]){
			if(y==fath)continue;
			dfs1(y,now);
			si[now]+=si[y];
			if(si[y]>si[son[now]])son[now]=y;
		}
		return ;
	}
	void dfs2(int now,int tp){
		top[now]=tp,dfn[now]=++num;
		if(son[now])dfs2(son[now],tp);
		for(int y:v[now]){
			if(y==son[now]||y==fa[now])continue;
			dfs2(y,y);
		}
		return ;
	}
	void spycl(){
		dfs1(1,0);
		dfs2(1,1);
		return ;
	}
	inline int lca(int x,int y){
		while(top[x]!=top[y]){
			if(deep[top[x]]<deep[top[y]])swap(x,y);
			x=fa[top[x]];
		}
		if(deep[x]>deep[y])swap(x,y);
		return x;
	}
}ys;
bool cmp(const int &x,const int &y){
	return ys.dfn[x]<ys.dfn[y];
}
int dfn[N];
struct xushu{
	int h[N],tot,m;
	int ansmin,ansmax,anssum;
	int maxn[N],minn[N],si[N];
	bool vis[N];
	vector <int> v[N];
	void ycl(){
		ansmin=inf,ansmax=-inf,anssum=0;
		memset(maxn,-0x3f,sizeof(maxn));
		memset(minn,0x3f,sizeof(minn));
	}
	void cl(){
		ansmin=inf,ansmax=-inf,anssum=0;
		for(int i=1;i<=tot;i++)v[h[i]].clear(),si[h[i]]=0,vis[h[i]]=0,minn[h[i]]=inf,maxn[h[i]]=-inf;
		return ;
	}
	void xsycl(){
		h[++tot]=1;
		int cnt=tot;
		sort(h+1,h+tot+1,cmp);
		for(int i=1;i<tot;i++){
			h[++cnt]=ys.lca(h[i],h[i+1]);
		}
		sort(h+1,h+cnt+1,cmp);
		tot=unique(h+1,h+cnt+1)-h-1;
		for(int i=1;i<tot;i++){
			int l=ys.lca(h[i],h[i+1]);
			v[l].push_back(h[i+1]);
		}
		sort(h+1,h+tot+1);
		tot=unique(h+1,h+cnt+1)-h-1;
		return ;
	}
	void dfs(int now){
		if(vis[now])si[now]=1;
		for(int y:v[now]){
			dfs(y);
			si[now]+=si[y];
			minn[y]+=ys.deep[y]-ys.deep[now];
			maxn[y]+=ys.deep[y]-ys.deep[now];
			ansmin=min(ansmin,minn[now]+minn[y]);
			minn[now]=min(minn[now],minn[y]);
			ansmax=max(ansmax,maxn[now]+maxn[y]);
			maxn[now]=max(maxn[now],maxn[y]);
			anssum+=(ys.deep[y]-ys.deep[now])*si[y]*(m-si[y]);
		}
		if(vis[now]){
			ansmin=min(ansmin,minn[now]);
			ansmax=max(ansmax,maxn[now]);
			maxn[now]=max(maxn[now],0ll);
			minn[now]=min(minn[now],0ll);
		}
		return ;
	}
}xs;
signed main(){
	int n=read();
    for(int i=1;i<n;i++){
		int a=read(),b=read();
		ys.v[a].push_back(b);
		ys.v[b].push_back(a);
	}
	ys.spycl();
	xs.ycl();
	int q=read();
	while(q--){
		xs.m=xs.tot=read();
		for(int i=1;i<=xs.m;i++){
			xs.h[i]=read();
			xs.vis[xs.h[i]]=1;
		}
		xs.xsycl();
		xs.dfs(1);
		cout<<xs.anssum<<" "<<xs.ansmin<<" "<<xs.ansmax<<endl;
		xs.cl();
	}
	return 0;
}
