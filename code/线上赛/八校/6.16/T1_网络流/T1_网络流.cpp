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
const int N=1e5+5;
const int NN=1e5+5;
const int INF=1e15;
int n,k;
int mp[N][15][15];
namespace _4pts{
	int a[NN];
	void mian(){
		memset(a,0,sizeof a);
		int ans=0,lst=0;
		for(int i=1;i<n;++i){
			a[i]=ad();
			if(a[i]==0){
				ans+=lst*(lst+1)/2;
				lst=0;
			}
			else ++lst;
		}
		cout<<ans<<endl;
        return ;
	}
}
int m,e,s,t;
int to[N],ne[N],val[N],h[N],now[N];
inline void add( int x, int y, int z){
	to[++e]=y,val[e]=z,ne[e]=h[x],h[x]=e;
}
inline void adde( int x, int y, int z){
	add(x,y,z);
	add(y,x,0);
}

queue<int> q;
int dep[N];
inline bool bfs(){
	while(q.size()) q.pop();
	memset(dep,0,sizeof dep);
	dep[s]=1;
	q.push(s);
	now[s]=h[s];
	while(q.size()){
		int x=q.front();
		q.pop();
		for( int i=h[x];i;i=ne[i]){
			int y=to[i];
			if(val[i] && !dep[y]){
				q.push(y);
				dep[y]=dep[x]+1;
				now[y]=h[y];
				if(y==t) return 1;
			}
		}
	}
	return 0;
}
inline int dfs( int x, int flow){
	if(x==t) return flow;
	int st=flow,i;
	for(i=now[x];i && st;i=ne[i]){
		int y=to[i];
		if(dep[y]==dep[x]+1 && val[i]){
			int k=dfs(y,min(st,val[i]));
			if(!k) dep[y]=0;
			val[i]-=k;
			val[i^1]+=k;
			st-=k;
		}
	}
	now[x]=i;
	return flow-st;
}
inline int maxflow(){
	int maxflow=0,flow;
	while(bfs()){
		while(flow=dfs(s,INF)) maxflow+=flow;
	}
	return maxflow;
}
inline int ha( int x, int y){
	return (x-1)*k+y;
}
int rem[N];
signed main() {
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
	n=ad(),k=ad();
	if(k==1){
		_4pts::mian();
		return 0;
	}
	for( int i=1;i<n;++i){
		char c[15];
		for( int j=1;j<=k;++j){
			scanf("%s",c+1);
			for( int jj=1;jj<=k;++jj){
				mp[i][j][jj]=(c[jj]=='1');
			}
		}
	}
	int ans=0;
	for( int i=1;i<n;++i){
		memset(h,0,sizeof h);
		e=1,s=0,t=100000;
		for( int j=1;j<=k;++j){
			adde(s,ha(i,j)<<1,1);
			adde(ha(i,j)<<1,ha(i,j)<<1|1,1);
			adde(ha(i+1,j)<<1,ha(i+1,j)<<1|1,1);
		}
		for( int j=1;j<=k;++j){
			for( int jj=1;jj<=k;++jj){
				if(mp[i][j][jj]){
					adde(ha(i,j)<<1|1,ha(i+1,jj)<<1,1);
				}
			}
		}
		int cnt=0;
		rem[++cnt]=e;
		for( int now=i+1;now<n;++now){
			for(int j=1;j<=k;++j){
				adde(ha(now+1,j)<<1,ha(now+1,j)<<1|1,1);
			}
			for( int j=1;j<=k;++j){
				for( int jj=1;jj<=k;++jj){
					if(mp[now][j][jj]){
						adde(ha(now,j)<<1|1,ha(now+1,jj)<<1,1);
					}
				}
			}
			rem[++cnt]=e;
		}
		int kaka=0;
		for(int ka=cnt,now=n;ka>=1;--ka,--now){
			e=rem[ka];
			for(int j=1;j<=k;++j){
				adde(ha(now,j)<<1|1,t,1);
			}
			int tmp=maxflow();
			ans+=kaka+tmp;
			kaka+=tmp;
		}
	}
	cout<<ans<<endl;
    return 0;
}
/*
14 1
0
1
1
1
0
1
1
1
0
0
1
1
0
*/