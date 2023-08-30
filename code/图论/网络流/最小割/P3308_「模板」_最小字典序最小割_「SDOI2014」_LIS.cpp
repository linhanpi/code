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
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
struct edge{
    int v,f;
};
struct node{
    int w;
    int p,id;
}nd[N];
vector <edge> E,E_;
vector <int> G[N];
int n,m,s,t,T,cur[N],dep[N],A[N],B[N],C[N],dp[N],len,stk[N],tp;
int add(int u,int v,int w){
	E.push_back((edge){v,w});
	E.push_back((edge){u,0});
	G[u].push_back(E.size()-2);
	G[v].push_back(E.size()-1);
	return E.size()-2;
}
bool bfs(int S,int T){
    for(int i=1;i<=2*(n+1);i++){
        dep[i]=0;
        dep[S]=1;
    }
	queue <int> q;
    q.push(S);
	while(q.size()){
		int u=q.front(); q.pop();
		for(int i=0;i<G[u].size();++i){
			edge e=E[G[u][i]];
			if(e.f&&!dep[e.v]){
				dep[e.v]=dep[u] + 1;
				q.push(e.v);
			}
		}
	}
	return dep[T];
}
int dfs(int u,int in,int T){
	if(u==T){
        return in;
    }
	int flow=0;
	for(int& i=cur[u];i<G[u].size();++i){
		edge& e=E[G[u][i]];
		if(e.f&&in&&dep[e.v]==dep[u]+1){
			int d=dfs(e.v,min(in,e.f),T);
			flow+=d;
            E[G[u][i]^1].f+=d;
			in-=d;
            e.f-=d;
		}
	}
	return flow;
}
inline bool cmp(node x,node y){
    return x.w<y.w;
}
void back(int u,int v){
	while(bfs(u,s)){
        for(int i=1;i<=t;i++){
            cur[i]=0;
        }
		dfs(u,inf,s);
	}
	while(bfs(t,v)){
        for(int i=1;i<=t;i++){
            cur[i]=0;
        }
		dfs(t,inf,v);
	}
}
signed main(){
    T=read();
	while(T--){
    n=read();
	E.clear();
    for(int i=0;i<=N-1;i++){
        G[i].clear();
    }
    for(int i=1;i<=n;i++){
        stk[i]=dp[i]=0;
    }
	tp=len=0;
    for(int i=1;i<=n;i++){
        A[i]=read();
    }
    for(int i=1;i<=n;i++){
        B[i]=read();
    }
    for(int i=1;i<=n;i++){
        C[i]=read();
    }
	s=n*2+1; t=s+1;
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<=i;j++){
            if(A[j]<A[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
            len=max(len,dp[i]);
        }
    }
    for(int i=1;i<=n;i++){
		nd[i].w=C[i];
        nd[i].p=add(i,n+i,B[i]);
        nd[i].id=i;
		if(dp[i]==1){
            add(s,i,inf);
        }
		if(dp[i]==len){
            add(i+n,t,inf);
        }
        for(int j=i+1;j<=n;j++){
            if(dp[j]==dp[i]+1&&A[j]>A[i]){
                add(i+n,j,inf);
            }
        }
	}
    int mxf=0;
	while(bfs(s,t)){
        for(int i=1;i<=t;i++){
            cur[i]=0;
        }
		mxf+=dfs(s,inf,t);
	}
	sort(nd+1,nd+n+1,cmp);
    for(int i=1;i<=n;i++){
		int p=nd[i].p;
        int u=nd[i].id;
		if(E[p].f==0&&!bfs(u,u+n)){
			back(u,u+n);
			E[p].f=E[p^1].f=0;
			stk[++tp]=u;
		}
	}
	sort(stk+1,stk+tp+1);
    cout<<mxf<<" "<<tp<<endl;
    for(int i=1;i<=tp;i++){
        cout<<stk[i]<<" ";
    }
	puts("");
	}
	return 0;
}