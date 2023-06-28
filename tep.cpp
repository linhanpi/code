#include<bits/stdc++.h>
using namespace std;
int n,k,rt;
int ver[400005],ne[400005],head[400005],cnt;
bool vis[200005],used[200005],vised[200005];
int col[200005],ans=1e9,tot;
inline void link(int x,int y){
	ver[++cnt]=y;
	ne[cnt]=head[x];
	head[x]=cnt;
}
int siz[200005],mxp[200005];
void find(int x,int fi,int tot){
	siz[x]=1;mxp[x]=0;
	for(int i=head[x];i;i=ne[i]){
		int u=ver[i];
		if(u==fi||vis[u])continue;
		find(u,x,tot);
		siz[x]+=siz[u];mxp[x]=max(mxp[x],siz[u]);
	}
	mxp[x]=max(mxp[x],tot-siz[x]);
	if(mxp[x]<mxp[rt])rt=x;
}
vector<int> vec[200005];
queue<int> q;
inline bool push(vector<int> &v){
	for(int i=0;i<v.size();i++){
		if(!used[v[i]])return 1;
		q.push(v[i]);
	}tot++;
	return 0;
}
int fa[200005];
void dfs1(int x,int fi){
	fa[x]=fi;
	for(int i=head[x];i;i=ne[i]){
		int u=ver[i];
		if(u==fi||vis[u])continue;
		dfs1(u,x);
	}
}
int stk[200005],top;
void del(int x,int fi){
	stk[top++]=x;used[x]=1;
	for(int i=head[x];i;i=ne[i]){
		int u=ver[i];
		if(u==fi||vis[u])continue;
		del(u,x);
	}
}
inline void calc(int x){
	tot=0;
	while(!q.empty())q.pop();
	vised[col[x]]=1;
	if(push(vec[col[x]]))return ;
	dfs1(x,x);
	while(!q.empty()){
		int u=q.front();q.pop();
		if(!vised[col[fa[u]]]){
			vised[col[fa[u]]]=1;
			if(push(vec[col[fa[u]]]))return ;
		}
	}
	ans=min(ans,tot);
}
void solve(int x){
	vis[x]=1;del(x,x);
	calc(x);
	while(top)--top,used[stk[top]]=vised[col[stk[top]]]=0;
	for(int i=head[x];i;i=ne[i]){
		int u=ver[i];
		if(vis[u])continue;
		rt=0;
		find(u,x,siz[u]);
		solve(rt);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		link(x,y);link(y,x);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&col[i]);
		vec[col[i]].push_back(i);
	}
	mxp[rt=0]=n;
	find(1,1,n);
	solve(rt);
	printf("%d",ans-1);

	return 0;
}