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
const int N=2e4+5;
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
int k[N],b[N];
struct kechijiuhua_lichaoxds{
	struct data{
		int ls,rs,maxn;
		#define ls(p) tree[p].ls
		#define rs(p) tree[p].rs
		#define maxn(p) tree[p].maxn 
	}tree[N*60];
	int tot,root[N];
	inline int new_node(){
		int now=++tot;
		ls(now)=rs(now)=maxn(now)=0;
		return now;
	}
	inline int zhi(int id,int x){
		return k[id]*x+b[id];
	}
	inline int getmx(int a,int c,int x){
		int b=zhi(a,x),d=zhi(c,x);
		return (b<d)?a:c;
	}
	int quanju_gai(int now,int l,int r,int id){
		int mid=(l+r)>>1;
		int p=new_node();
		tree[p]=tree[now];
		if(zhi(id,mid)<zhi(maxn(p),mid))swap(id,maxn(p));
		if(zhi(id,l)<zhi(maxn(p),l))ls(p)=quanju_gai(ls(p),l,mid,id);
		if(zhi(id,r)<zhi(maxn(p),r))rs(p)=quanju_gai(rs(p),mid+1,r,id);
		return p;
	}
	int cha(int p,int l,int r,int x){
		if(l==r){
			return maxn(p);
		}
		int mid=(l+r)>>1;
		if(x<=mid)return getmx(maxn(p),cha(ls(p),l,mid,x),x);
		else return getmx(maxn(p),cha(rs(p),mid+1,r,x),x);
	}
}lcs;
int a[N],g[N],f[N];
struct tubao{
	deque <int> d;
	#define x(i) (i)
	#define y(i) (g[i])
	inline ld xie(int i,int j){
		return (ld)(y(i)-y(j))/(x(i)-x(j));
	}
	int cross(int i,int j,int k){
  		return (j-i)*(g[k]-g[j])-(k-j)*(g[j]-g[i]);
	}
	inline void hb(tubao &x){
		int top=x.d.size()-1;
		if(x.d.size()>d.size()){
			for(int it:d){
				while(top>=1&&cross(x.d[top-1],x.d[top],it)<=0)--top,x.d.pop_back();
				++top,x.d.push_back(it);
			}
			swap(x.d,d);
		}
		else{
			for(;~top;top--){
				while(d.size()>1&&cross(x.d[top],d[0],d[1])<=0)d.pop_front();
				d.push_front(x.d[top]);
			}
		}
		return ;
	}
	inline int cha(ld k){
		int l=0,r=d.size()-1;
		while(l<r){
			int mid=(l+r)>>1;
			if(xie(d[mid],d[mid+1])<=k)l=mid+1;
			else r=mid;
		}
		return y(d[l])-x(d[l])*k;
	}
}tb[N];
int st[N],top;
signed main(){
	int n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	b[0]=inf;
	for(int i=1,maxn=0;i<=n;i++){
		maxn=max(maxn,a[i]);
		f[i]=i*maxn;
	}
	for(int i=2;i<=m;i++){
		swap(f,g);
		lcs.tot=top=0;
		for(int j=1;j<=n;j++){
			tb[j].d.resize(1),tb[j].d[0]=j-1;
			while(top&&a[st[top]]<=a[j])tb[j].hb(tb[st[top--]]);
			lcs.root[j]=lcs.root[st[top]];
			st[++top]=j;
			b[j]=tb[j].cha(a[j]);
			k[j]=a[j];
			lcs.root[j]=lcs.quanju_gai(lcs.root[j],1,n,j);
			int re=lcs.cha(lcs.root[j],1,n,j);
			f[j]=k[re]*j+b[re];
		}
	}
	cout<<f[n]<<endl;
	return 0;
}