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
const int N=1e6+5;
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
inline bool dengyu(double x,double y){return abs(x-y)<=eps;}
inline bool dayu(double x,double y){return x-y>=eps;}
inline bool xiaoyu(double x,double y){return y-x>=eps;}
struct juzheng{
	int a,b,c,d;
	juzheng(){a=b=c=d=0;}
};
juzheng operator *(const juzheng &x,const juzheng &y){
	juzheng c;
	c.a=max(x.a+y.a,x.b+y.c);
	c.b=max(x.a+y.b,x.b+y.d);
	c.c=max(x.c+y.a,x.d+y.c);
	c.d=max(x.c+y.c,x.d+y.d);
	return c;
}
int a[N];
int si[N],fa[N];
vector <int> v;
int f[N][2],g[N][2];
void dfs1(int now,int fath){
	dp[now][1]=a[now],si[now]=1,deep[now]=deep[fa[now]]+1;
	for(int y:v[now]){
		if(y==fath)continue;
		fa[y]=fath;
		
	}
	return ;
}
signed main(){
	int n=read(),q=read();

	return 0;
}
