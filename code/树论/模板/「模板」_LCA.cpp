#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool flag=false;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') flag=true;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return flag?~x+1:x;
}
inline void write(int x){
	if(x<0){putchar('-');x=(~x+1);}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=5e5+5;
vector <int> v[N];
int fa[N],son[N],tp[N],si[N],dep[N];
void dfs1(int now){
	int maxn=0;
	si[now]=1;
	dep[now]=dep[fa[now]]+1;
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i];
		if(y==fa[now])continue;
		fa[y]=now;
		dfs1(y);
		si[now]+=si[y];
		if(si[y]>maxn){
			maxn=si[y];
			son[now]=y;
		}
	}
	return ;
}
void dfs2(int now,int top){
	tp[now]=top;
	if(!son[now])return ;
	dfs2(son[now],top);
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i];
		if(y==fa[now]||y==son[now])continue;
		dfs2(y,y);
	}
	return ;
}
inline int cha(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])swap(x,y);
		x=fa[tp[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	return y;
}
int main(){
	int n=read(),m=read(),q=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs1(q);
	dfs2(q,q);
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		cout<<cha(x,y)<<endl;
	}
	return 0;
}