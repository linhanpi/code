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
const int N=25+5;
const int M=1e2+5;
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
int cnta,cntb;
int a[N],b[N],t[N];
int sta[N],stb[N],flag[N];
int ans=inf,aans=inf;
inline bool cmp_a(int x,int y){
    return b[x]==b[y]?a[x]<a[y]:b[x]>b[y];
}
inline bool cmp_b(int x,int y){
    return a[x]==a[y]?b[x]<b[y]:a[x]>a[y];
}
inline int js(){
	int sa=0,sb=0;
	for(int i=1;i<=cnta;i++){
		sa+=a[sta[i]];
	}
	for(int i=1;i<=cntb;i++){
		sb+=b[stb[i]];
		if(sa>sb)sa+=a[stb[i]];
		else sa=sb+a[stb[i]];
	}
	int res=max(sa,sb);
	sa=sb=0;
	for(int i=1;i<=cntb;i++){
		sb+=b[stb[i]];
	}
	for(int i=1;i<=cnta;i++){
		sa+=a[sta[i]];
		if(sb>sa)sb+=b[sta[i]];
		else sb=sa+b[sta[i]];
	}
	return max(res,max(sa,sb));
}
int n;
void sa(){
	double t=3000;
	while(t>1e-15){
		int a1=ran_int(1,cnta),a2=ran_int(1,cnta);
		int b1=ran_int(1,cntb),b2=ran_int(1,cntb);
		// cout<<a1<<" "<<a2<<" "<<b1<<" "<<b2<<endl;
		if(cnta)swap(sta[a1],sta[a2]);
		if(cntb)swap(stb[b1],stb[b2]);
		int res=js();
		int cha=ans-res;
		if(cha>0){
			ans=res;
		}
		else if(exp(1.0*cha/t)<=ran_real(0,1)){
			if(cnta)swap(sta[a1],sta[a2]);
			if(cntb)swap(stb[b1],stb[b2]);
		}
		t*=Down;
	}
	return ;
}
void solve(){
	ans=inf;
	cnta=cntb=0;
	for(int i=1;i<=n;i++){
		if(flag[i])stb[++cntb]=i;
		else sta[++cnta]=i;
	}
	sort(sta+1,sta+cnta+1,cmp_a);
	sort(stb+1,stb+cntb+1,cmp_b);
	ans=js();
	// sa();
	// sa();
	sa();
	sa();
	aans=min(aans,ans);
	return ;
}
void dfs(int deep){
	if(deep>n){
		solve();
		return ;
	}
	else if(t[deep]==1){
		flag[deep]=0;
		dfs(deep+1);
		return;
	}
	else if(t[deep]==2){
		flag[deep]=1;
		dfs(deep+1);
		return ;
	}
	else{
		flag[deep]=0;
		dfs(deep+1);
		flag[deep]=1;
		dfs(deep+1);
		return ;
	}
	return ;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		t[i]=read(),a[i]=read(),b[i]=read();
	}
	dfs(1);
	cout<<aans<<endl;
	return 0;
}
