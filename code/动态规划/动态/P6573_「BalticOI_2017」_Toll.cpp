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
int k,n,m,o,lim;
struct node{
	int a[6][6];
}tree[200005];
const node operator *(const node &x,const node &y){
	node z;memset(z.a,0x3f,sizeof(z.a));
	for(int i=0;i<k;i++)
		for(int j=0;j<k;j++)
			for(int p=0;p<k;p++)z.a[i][j]=min(z.a[i][j],x.a[i][p]+y.a[p][j]);
	return z;
}
void build(int k,int l,int r){
	memset(tree[k].a,0x3f,sizeof(tree[k].a));
	if(l==r)return;
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
}
void change(int k,int l,int r,int x,int a,int b,int y){
	if(l==r){
		tree[k].a[a][b]=y;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)change(k*2,l,mid,x,a,b,y);
	else change(k*2+1,mid+1,r,x,a,b,y);
	tree[k]=tree[k*2]*tree[k*2+1];
}
node query(int k,int l,int r,int x,int y){
	if(l>=x&&r<=y)return tree[k];
	int mid=l+r>>1;
	if(y<=mid)return query(k*2,l,mid,x,y);
	else if(x>mid)return query(k*2+1,mid+1,r,x,y);
	else return query(k*2,l,mid,x,y)*query(k*2+1,mid+1,r,x,y);
}
signed main(){
    k=read(),n=read(),m=read(),o=read();
	lim=(n-1)/k+1;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		change(1,1,lim,x/k+1,x%k,y%k,z);
	}
	for(int i=1;i<=o;i++){
		int x=read(),y=read();
		if(x/k==y/k)puts("-1");
		else{
			node res=query(1,1,lim,x/k+1,y/k);
			if(res.a[x%k][y%k]==0x3f3f3f3f3f3f3f3f)puts("-1");
			else printf("%lld\n",res.a[x%k][y%k]);
		}
	}
	return 0;
}