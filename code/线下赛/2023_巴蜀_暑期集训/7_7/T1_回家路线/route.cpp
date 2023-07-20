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
const int M=2e5+5;
const int bzt=18;
const int inf=9223372036854775807;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-5;
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
	int x,y,id;
};
int n,m,A,B,C,maxt,ans=inf;
int x[N],y[N],p[N],q[N],l[N],dp[N];
vector <int> dao[M];
queue <int> qi[M];
vector <node> st[M];

#define Y(i) (dp[i]+A*q[i]*q[i]-B*q[i])
#define X(i) (q[i])
#define K(i) (2*A*p[i])

double xie(node i,node j){
	if(i.x==j.x)return inf;
	return (1.0*(i.y-j.y))/(1.0*(i.x-j.x));
}
inline void insert(int i){
	int pos=y[i];
	node now=(node){X(i),Y(i),i};
	while(st[pos].size()-l[pos]>=2){
		int len=st[pos].size();
		if(xie(st[pos][len-1],st[pos][len-2])<xie(st[pos][len-1],now))break;
		st[pos].pop_back();
	}
	st[pos].push_back(now);
	return ;
}
inline void shan(double xi,int pos){
	while(st[pos].size()-l[pos]>=2){
		if(xie(st[pos][l[pos]],st[pos][l[pos]+1])>xi)return ;
		++l[pos];
	}
	return ;
}
signed main(){
    freopen("route.in","r",stdin);
    freopen("route.out","w",stdout);
	n=read(),m=read(),A=read(),B=read(),C=read();
	for(int i=1;i<=m;i++){
		x[i]=read(),y[i]=read(),p[i]=read(),q[i]=read();
		maxt=max(maxt,q[i]);
	}
	for(int i=1;i<=m;i++){
		dao[p[i]].push_back(i);
	}
	st[1].push_back((node){0,0,0});
	for(int t=0;t<=maxt;t++){
		while(!qi[t].empty()){
			insert(qi[t].front());
			qi[t].pop();
		}
		int len=dao[t].size()-1;
		for(int k=0;k<=len;k++){
			int id=dao[t][k];
			int pos=x[id];
			if(st[pos].size()==l[pos])continue;
			double xi=K(id);
			shan(xi,pos);
			int j=st[pos][l[pos]].id;
			dp[id]=dp[j]+1ll*A*(p[id]-q[j])*(p[id]-q[j])+1ll*B*(p[id]-q[j])+C;
			qi[q[id]].push(id);
			if(y[id]==n){
				ans=min(ans,dp[id]+q[id]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}