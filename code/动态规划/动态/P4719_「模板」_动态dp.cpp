#include<bits/stdc++.h>
// #define int long long//信仰
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
const int inf=1e9;
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
inline bool dengyu(double x,double y){return abs(x-y)<=eps;}
inline bool dayu(double x,double y){return x-y>=eps;}
inline bool xiaoyu(double x,double y){return y-x>=eps;}
int a[N];
vector <int> v[N];
int f[N][2],g[N][2];
int n,q;
struct juzheng{
	int a,b,c,d;
	juzheng(){a=b=c=d=0;}
}I,G[N],ans;
void mtycl(int x){
	G[x].a=G[x].c=g[x][0],G[x].b=g[x][1],G[x].d=-inf;
	return ;
}
juzheng operator *(const juzheng &x,const juzheng &y){
	juzheng c;
	c.a=max(x.a+y.a,x.b+y.c);
	c.b=max(x.a+y.b,x.b+y.d);
	c.c=max(x.c+y.a,x.d+y.c);
	c.d=max(x.c+y.b,x.d+y.d);
	return c;
}
struct shupou{
	int num;
	int si[N],fa[N],deep[N],son[N],top[N],ys[N],dfn[N],ed[N];
	void dfs1(int now){
		f[now][1]=a[now],si[now]=1,deep[now]=deep[fa[now]]+1;
		for(int y:v[now]){
			if(y==fa[now])continue;
			fa[y]=now;
			dfs1(y);
			si[now]+=si[y];
			f[now][1]+=f[y][0],f[now][0]+=max(f[y][0],f[y][1]);
			if(si[y]>si[son[now]])son[now]=y;
		}
		return ;
	}
	void dfs2(int now,int tp){
		g[now][1]=a[now],top[now]=tp,ys[dfn[now]=++num]=now;
		if(!son[now]){
			ed[now]=now;
			return ;
		}
		dfs2(son[now],tp),ed[now]=ed[son[now]];
		for(int y:v[now]){
			if(y==son[now]||y==fa[now])continue;
			dfs2(y,y);
			g[now][1]+=f[y][0],g[now][0]+=max(f[y][0],f[y][1]);
		}
		return ;
	}
}sp;
struct xianduanshu{
	juzheng val[N<<2];
	int root[N],ls[N<<2],rs[N<<2],tot;
	inline int new_node(){
		int now=++tot;
		ls[now]=rs[now]=0;
		return now;
	}
	void pu(int p){
		val[p]=val[rs[p]]*val[ls[p]];
		return ;
	}
	int bd(int l,int r){
		int p=new_node();
		if(l==r){
			val[p]=G[sp.ys[l]];
			return p;
		}
		int mid=(l+r)>>1;
		ls[p]=bd(l,mid);
		rs[p]=bd(mid+1,r);
		pu(p);
		return p;
	}
	void gai(int p,int l,int r,int pos){
		if(l==r)return val[p]=G[sp.ys[l]],void();
		int mid=(l+r)>>1;
		if(pos<=mid)gai(ls[p],l,mid,pos);
		else gai(rs[p],mid+1,r,pos);
		pu(p);
		return ;
	}
	void cha(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return ans=ans*val[p],void();
		int mid=(l+r)>>1;
		if(mid<qr)cha(rs[p],mid+1,r,ql,qr);
		if(ql<=mid)cha(ls[p],l,mid,ql,qr);
		return ;
	}
}xds;
int gai(int x,int val){
	g[x][1]+=val-a[x],a[x]=val;
	while(sp.top[x]!=1){
		int tp=sp.top[x],ft=sp.fa[tp];
		ans=xds.val[xds.root[tp]];
		g[ft][1]-=ans.a,g[ft][0]-=max(ans.a,ans.b);
		mtycl(x),xds.gai(xds.root[tp],sp.dfn[tp],sp.dfn[sp.ed[tp]],sp.dfn[x]);
		ans=xds.val[xds.root[tp]];
		g[ft][1]+=ans.a,g[ft][0]+=max(ans.a,ans.b);
		x=ft;
	}
	mtycl(x),xds.gai(xds.root[1],sp.dfn[1],sp.dfn[sp.ed[1]],sp.dfn[x]);
	ans=xds.val[xds.root[1]];
	return max(ans.a,ans.b);
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),vv=read();
		v[u].push_back(vv);
		v[vv].push_back(u);
	}
	sp.dfs1(1);
	sp.dfs2(1,1);
	for(int i=1;i<=n;i++)mtycl(i);
	for(int i=1;i<=n;i++){
		if(sp.top[i]==i)xds.root[i]=xds.bd(sp.dfn[i],sp.dfn[sp.ed[i]]);
	}
	int las=0;
	while(q--){
		int x=read();
		las=gai(x^las,read());
		write(las);
		puts("");
	}
	return 0;
}
