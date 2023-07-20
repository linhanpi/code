#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
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
int fa[N],son[N],vis[N],zai[N],tp[N],si[N],dep[N],se[N];
pii xw[N];int tot,noww;
void dfs1(int now){
    // cout<<"now "<<now<<" "<<noww<<endl;
    zai[now]=noww;
    vis[now]=1;
	int maxn=0;
	si[now]=1;
	dep[now]=dep[fa[now]]+1;
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i];
		if(y==fa[now])continue;
        if(zai[y]==noww){
            xw[++tot]={now,y};
            continue;
        }
        if(vis[y])continue;
        if(se[now]==se[y])continue;
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
    vis[now]=2;
	tp[now]=top;
	if(!son[now])return ;
	dfs2(son[now],top);
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i];
		if(y==fa[now]||y==son[now])continue;
        if(se[now]==se[y])continue;
        if(vis[y]==2)continue;
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
	int n=read(),m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
    for(int i=1;i<=n;i++)se[i]=read();
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            noww=i;
            dfs1(i);
            dfs2(i,i);
        }
    }
	bool flag=0;
    for(int i=1;i<=tot;i++){
        int x=xw[i].first,y=xw[i].second;
        int l=cha(x,y);
        // cout<<"x y "<<x<<" "<<y<<" "<<l<<endl;
        if((dep[x]+dep[y]-2*dep[l]+1)&1){
            flag=1;
            break;
        }
    }
    if(flag)puts("Yes");
    else puts("No");
	return 0;
}