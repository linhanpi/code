#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e6+10;
struct edge{
	int next,to;
}e[N<<2];
int first[N],len;
void add(int a,int b)
{
	e[++len]=edge{first[a],b};
	first[a]=len;
}
struct my_stack{
	int len,t[N];
	void push(int x){t[++len]=x;}
	int top(){return t[len--];}
}t;
int vis[N],p[N],dfn[N],low[N],cnt,col[N],tot;
void dfs2(int x,int id)
{
	vis[x]=1;
	if(p[x]&&id>x) add(x^1,x);
	for(int i=first[x],y;i;i=e[i].next)
		if(!vis[y=e[i].to]) dfs2(y,id);
}
void dfs(int x)
{
	dfn[x]=low[x]=++cnt;
	t.push(x);
	for(int i=first[x],y;i;i=e[i].next)
		if(!dfn[y=e[i].to]) dfs(y),low[x]=min(low[x],low[y]);
		else if(!col[y=e[i].to]) low[x]=min(low[x],low[y]);
	if(dfn[x]==low[x])
	{
		col[x]=++tot;
		int y=t.top();
		while(y!=x) col[y]=tot,y=t.top();
	}
}
int flag,f[N],g[N];
void dfs3(int x)
{
	vis[x]=1;
	int w=f[col[x]];
	for(int i=first[x],y;i;i=e[i].next)
	{
		if(!vis[y=e[i].to]) dfs3(y);
		if(col[y]!=col[x]&&g[col[y]]&&w) flag=1;
		g[col[x]]|=g[col[y]];
	}
}
int n,m;
inline char gc()
{
	static char buf[1<<20],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++;
}
inline int rd()
{
	register int a=0,c=0;
	while(c>'9'||c<'0') c=gc();
	while(c>='0'&&c<='9') a=(a<<3)+(a<<1)+(c&15),c=gc();
	return a;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	n=rd(),m=rd();
	for(int i=0;i<2*n;i+=4) p[i]=p[i+1]=1;
	for(int i=1,x,y;i<=m;i++)
	{
		x=rd()-1,y=rd()-1;
		add(x,y),add(y^1,x^1);
	}
	for(int i=2*n;i;i--)
		if(!p[i-1]) dfs2(i-1,i-1);
	for(int i=0;i<2*n;i++)
		if(!dfn[i]) dfs(i);
	for(int i=0;i<2*n;i++) vis[i]=0;
	for(int i=0;i<n;i++)
		if(col[i<<1]==col[i<<1|1])
			return puts("Bob"),0;
	for(int i=0;i<2*n;i++)
		if(!p[i]) f[col[i]]++,g[col[i]]=1;
	for(int i=1;i<=tot;i++)
		if(f[col[i]]>1) return puts("Bob"),0;
	for(int i=0;i<2*n;i++) if(!vis[i]) dfs3(i);
	puts(flag?"Bob":"Alice");
}
