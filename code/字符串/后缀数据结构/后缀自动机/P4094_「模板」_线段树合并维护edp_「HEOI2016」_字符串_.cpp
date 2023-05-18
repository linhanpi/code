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
template<typename T>inline T red() {
	T x=0;
	bool f=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=true;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>inline void write(T x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e4+7;
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
inline int qmi(int x,int y,int mod){
	int ans=1;
	x%=mod;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
inline int fang(int x) {return x*x;}
struct xds{
	int ls,rs,sum;
	#define ls(p) tree[p].ls
	#define rs(p) tree[p].rs
	#define sum(p) tree[p].sum
}tree[N*4];
int n,q;
int cnt,root[N];
int bt(){
	int p=++cnt;
	ls(p)=rs(p)=sum(p)=0;
	return p;
}
void pu(int p){
	sum(p)=(ls(p)?sum(ls(p)):0)+(rs(p)?sum(rs(p)):0);
	return ;
}
void add(int p,int l,int r,int pos,int x){
	if(l==r){
		sum(p)+=x;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)add(ls(p)=(ls(p)?ls(p):bt()),l,mid,pos,x);
	else add(rs(p)=(rs(p)?rs(p):bt()),mid+1,r,pos,x);
	pu(p);
	return ;
}
int cha(int p,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(ql<=l&&r<=qr)return sum(p);
	int ans=0,mid=(l+r)>>1;
	if(ql<=mid&&ls(p))ans+=cha(ls(p),l,mid,ql,qr);
	if(qr>mid&&rs(p))ans+=cha(rs(p),mid+1,r,ql,qr);
	return ans;
}
int hb(int p,int q,int l,int r){
	if(!p||!q)return p+q;
	int mid=(l+r)>>1;
	int now=bt();
	sum(now)=sum(p)+sum(q);
	if(l==r)return now;
	ls(now)=hb(ls(p),ls(q),l,mid);
	rs(now)=hb(rs(p),rs(q),mid+1,r);
	return now;
}
struct zdj{
	int t[26],f,len;
	#define t(p,c) sam[p].t[c]
	#define f(p) sam[p].f
	#define len(p) sam[p].len
}sam[N];
int tot,last;
void insert(int c){
	int p=last,np=last=++tot;
	len(np)=len(p)+1;
	for(;p&&!t(p,c);p=f(p))t(p,c)=np;
	if(!p)f(np)=1;
	else{
		int v=t(p,c);
		if(len(v)==len(p)+1)f(np)=v;
		else{
			int nv=++tot;
			sam[nv]=sam[v];
			len(nv)=len(p)+1;
			for(;p&&t(p,c)==v;p=f(p))t(p,c)=nv;
			f(v)=f(np)=nv;
		}
	}
	return ;
}
int ed[N];
vector <int> v[N];
char s[N];
int fa[N][20];
bool ck(int end,int len,int l,int r){
	int p=ed[end];
	for(int i=bzt;i>=0;i--)if(len(fa[p][i])>=len)p=fa[p][i];
	return cha(root[p],1,n,l+len-1,r);
}
void ycl(){
	last=tot=1;
	len(0)=-inf;
	return ;
}
int ans[N];
void dfsbz(int now){
	fa[now][0]=f(now);
	for(int i=1;i<=bzt;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
	for(int y:v[now]){
		dfsbz(y);
	}
	return ;
}
void dfs(int now){
	for(int y:v[now]){
		dfs(y);
		root[now]=hb(root[now],root[y],1,n);
	}
	return ;
}
signed main(){
	ycl();
	n=read(),q=read();
	scanf("%s",s+1);
	reverse(s+1,s+n+1);
	for(int i=1;i<=n;i++)insert(s[i]-'a');
	for(int i=1;i<=tot;i++)root[i]=bt();
	for(int i=1,p=1;i<=n;i++){
		p=t(p,s[i]-'a');
		ed[i]=p;
		add(root[p],1,n,i,1);
	}
	for(int i=2;i<=tot;i++)v[f(i)].push_back(i);
	dfsbz(1);
	dfs(1);
	for(int i=1;i<=q;i++){
		int a=n-read()+1,b=n-read()+1,c=n-read()+1,d=n-read()+1;
		swap(a,b),swap(c,d);
		int l=0,r=min(b-a+1,d-c+1);
		while(l<r){
			int mid=(l+r+1)>>1;
			if(ck(d,mid,a,b))l=mid;
			else r=mid-1;
		}
		cout<<l<<endl;
	}
	
	return 0;
}
