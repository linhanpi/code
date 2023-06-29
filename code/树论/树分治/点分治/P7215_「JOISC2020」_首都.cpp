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
vector <int> v[N],you[N];
int se[N];
int fa[N],si[N],maxn[N];
bool vis[N];
int rt,nowtot;
int sta[N],top;
bool visshan[N],visse[N];
void zz(int x,int fi,int tot){
	si[x]=1;maxn[x]=0;
	for(int u:v[x]){
		if(u==fi||vis[u])continue;
		zz(u,x,tot);
		si[x]+=si[u];maxn[x]=max(maxn[x],si[u]);
	}
	maxn[x]=max(maxn[x],tot-si[x]);
	if(maxn[x]<maxn[rt])rt=x;
}
queue <int> q;
inline bool push(vector<int> &v){
	for(int i=0;i<v.size();i++){
		if(!visshan[v[i]])return 1;
		q.push(v[i]);
	}
	nowtot++;
	return 0;
}
void dfs(int now,int fath){
	fa[now]=fath;
	for(int y:v[now]){
		if(y==fath||vis[y])continue;
		dfs(y,now);
	}
	return ;
}
void shan(int now,int fath){
	sta[top++]=now,visshan[now]=1;
	for(int y:v[now]){
		if(y==fath||vis[y])continue;
		shan(y,now);
	}
	return ;
}
int ans=inf;
inline void js(int now){
	nowtot=0;
	while(!q.empty())q.pop();
	visse[se[now]]=1;
	if(push(you[se[now]]))return ;
	dfs(now,now);
	while(!q.empty()){
		int y=q.front();q.pop();
		if(!visse[se[fa[y]]]){
			visse[se[fa[y]]]=1;
			if(push(you[se[fa[y]]]))return ;
		}
	}
	ans=min(ans,nowtot);
	return ;
}
void dfz(int now){
	vis[now]=1;shan(now,now);
	js(now);
	while(top)top--,visshan[sta[top]]=visse[se[sta[top]]]=0;
	for(int y:v[now]){
		if(vis[y])continue;
		rt=0;
		zz(y,now,si[y]);
		dfz(rt);
	}
	return ;
}
signed main(){
	int n=read(),k=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		se[i]=read();
		you[se[i]].push_back(i);
	}
	maxn[rt=0]=n;
	zz(1,1,n);
	dfz(rt);
	cout<<ans-1<<endl;
	return 0;
}
