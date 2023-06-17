#include <bits/stdc++.h>
using namespace std;
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
#define ad() (d<int>())
template<typename T>inline T d(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=2e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e15+7;
const int base=131;
const int mod=998244353;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_al(l,r) uniform_al_distribution<ld>(l,r)(rnd)
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
inline void chkmax(int &x, register int y){if(y>x)x=y;}
inline void chkmin(int &x, register int y){if(y<x)x=y;}
int n,m;
int x[N],X[N],v[N],dp[N];
struct node{
	int opt,xx,id;
}q[N];
int ans[N];
signed main() {
	freopen("miner.in","r",stdin);
	freopen("miner.out","w",stdout);
	n=ad(),m=ad();
	int maxx=ad();
	for(int i=1;i<=n;++i){
		x[i]=ad(),v[i]=ad();
		X[i]=x[i];
		chkmax(maxx,x[i]*v[i]);
	}
	for(int i=1;i<=m;++i){
		int opt=ad();
		if(opt==1){
			int y=ad();
			q[i]={opt,y,i};
			x[y]=2e10;
		}
		else{
			int k=ad();
			q[i]={opt,k,i};
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=maxx;j>=x[i]*v[i];--j){
			chkmax(dp[j],dp[j-x[i]*v[i]]+v[i]);
		}
	}
	memset(ans,-1,sizeof(ans));
	for(int i=m;i>=1;--i){
		if(q[i].opt==1){
			x[q[i].xx]=X[q[i].xx];
			int id=q[i].xx;
			for(int j=maxx;j>=x[id]*v[id];--j){
				chkmax(dp[j],dp[j-x[id]*v[id]]+v[id]);
			}
		}
		else ans[q[i].id]=dp[q[i].xx];
	}
	for(int i=1;i<=m;++i){
		if(~ans[i]){
            write(ans[i]);
            puts("");
		}
	}
	
	return 0;
}
/*
3 8 50
3 3
4 2
6 4
2 25
2 8
2 7
2 12
1 2
2 25
1 3
2 40
*/