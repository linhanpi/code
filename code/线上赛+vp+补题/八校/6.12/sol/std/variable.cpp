#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1210,M=250020,inf=0x3f3f3f3f;
int read(){
	int f=1,g=0;
	char ch=getchar();
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) g=g*10+ch-'0';
	return f*g;
}
int cnt,n,m,S,T;
ll sum[N],ans;
int fir[N],firr[N],siz;
struct edge{int u,v,w,nex;}e[M];
void add(int u,int v,int w){
	e[++siz]=(edge){u,v,w,fir[u]};fir[u]=siz;
	e[++siz]=(edge){v,u,0,fir[v]};fir[v]=siz;
}
int dist[N],que[N];
void dec(int x,int fl){e[x].w-=fl;e[x^1].w+=fl;}
bool bfs(int S,int T){
	memset(dist,0x3f,4*(cnt+1));
	int l=1,r=1;que[l]=S;dist[S]=0;
	while (l<=r){
		int x=que[l];
		for (int i=fir[x];i;i=e[i].nex)
		if ((e[i].w)&&(dist[e[i].v]>dist[x]+1)){
			que[++r]=e[i].v;
			dist[e[i].v]=dist[x]+1;
		}
		l++;
	}
	return dist[T]!=inf;
}
int dfs(int x,int flow,int &T){
	if (x==T) return flow;
	int fl=0,t=0;
	for (int i=firr[x];i;i=e[i].nex)
	if (e[i].w&&(dist[e[i].v]>dist[x])){
		t=dfs(e[i].v,min(flow-fl,e[i].w),T);
		dec(i,t);fl+=t;
		if (fl==flow) {firr[x]=i;return fl;}
	}
	firr[x]=0;
	return fl;
}
ll dinic(int S,int T){
	ll flow=0;
	while (bfs(S,T)){
		for (int i=0;i<=cnt;i++) firr[i]=fir[i];
		flow+=dfs(S,2147483647,T);
		//cerr<<flow<<endl;
	}
	return flow;
}
int g[N];
int main(){
	freopen("variable.in","r",stdin);
	freopen("variable.out","w",stdout);
	
	int sT=read();
	while (sT--){
		siz=1;
		memset(fir,0,sizeof(fir));
		memset(g,0,sizeof(g));
		int n=read(),W=read(),p=read(),q=read();
		cnt=n+1;
		S=0;T=n+1;
		for (int i=1;i<=p;i++){
			int x=read(),y=read(),z=read(),a=read(),b=read(),c=read(),d=read(),e=read(),f=read();
			add(x,y,a*2);add(y,x,a*2);
			add(z,y,b*2);add(y,z,b*2);
			add(x,z,c*2);add(z,x,c*2);
			g[x]+=d-f;
			g[y]+=e-d;
			g[z]+=f-e;
		}
		for (int i=1;i<=q;i++){
			int x=read(),y=read(),r=read();
			if (r==2){
				add(x,T,inf);
				add(S,y,inf);
			}
			else if (r==1){
				add(x,y,inf);
				add(y,x,inf);
			}
			else add(x,y,inf);
		}
		ll cur=-n;
		for (int i=1;i<=n;i++){
			add(i,T,2);
			if (g[i]<0) {add(S,i,-g[i]*2);cur+=g[i];}
			else {add(i,T,g[i]*2);cur-=g[i];}
		}
		printf("%lld\n",(ll)W*(dinic(S,T)+cur));
	}
	return 0;
}
