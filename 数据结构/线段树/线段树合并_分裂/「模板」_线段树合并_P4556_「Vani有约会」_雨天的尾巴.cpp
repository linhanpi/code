#include<bits/stdc++.h>
#define int long long
// #define double long double
//#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red() {
	T x=0;
	bool f=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=true;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>inline void write(T x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=1e5+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod=(1<<30);
const double eps=1e-6;
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
struct st{
    int ls,rs,maxn,maxd;
    st(){
        ls=rs=0;
        maxn=maxd=0;
    }
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
    #define maxn(p) tree[p].maxn
    #define maxd(p) tree[p].maxd
}tree[N*60];
int tot;
int root[N];
inline int bt(){
    tot++;
    ls(tot)=rs(tot)=maxn(tot)=maxd(tot)=0;
    return tot;
}
void pu(int p){
    if(!ls(p)&&!rs(p))return ;
    if(!ls(p))maxn(p)=maxn(rs(p)),maxd(p)=maxd(rs(p));
    if(!rs(p))maxn(p)=maxn(ls(p)),maxd(p)=maxd(ls(p));
    if(maxn(ls(p))>=maxn(rs(p))){
        maxd(p)=maxd(ls(p));
    }
    else maxd(p)=maxd(rs(p));
    maxn(p)=max(maxn(ls(p)),maxn(rs(p)));
    if(maxn(p)<=0){
        maxd(p)=0;
    }
    return ;
}
void add(int p,int l,int r,int pos,int x){
    if(l==r){
        maxn(p)+=x;
        if(maxn(p)>0)maxd(p)=pos;
        else maxd(p)=0;
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        if(!ls(p))ls(p)=bt();
        add(ls(p),l,mid,pos,x);
    }
    else{
        if(!rs(p))rs(p)=bt();
        add(rs(p),mid+1,r,pos,x);
    }
    pu(p);
    return ;
}
int hb(int p,int q,int l,int r){
    if(!p||!q)return p+q;
    if(l==r){
        maxn(p)+=maxn(q);
        maxd(p)=l;
        return p;
    }
    int mid=(l+r)>>1;
    ls(p)=hb(ls(p),ls(q),l,mid);
    rs(p)=hb(rs(p),rs(q),mid+1,r);
    pu(p);
    return p;
}
vector <int> v[N];
int fa[N],son[N],tp[N],si[N],deep[N];
void dfs1(int now){
    int maxn=0;
    si[now]=1;
    deep[now]=deep[fa[now]]+1;
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
        if(deep[tp[x]]<deep[tp[y]])swap(x,y);
        x=fa[tp[x]];
    }
    if(deep[x]<deep[y])swap(x,y);
    return y;
}
int ans[N];
void dfs3(int now){
    for(int i=0;i<(int)v[now].size();i++){
        int y=v[now][i];
        if(y==fa[now])continue;
        dfs3(y);
        root[now]=hb(root[now],root[y],1,N-5);
    }
    ans[now]=maxd(root[now]);
    return ;
}
signed main(){
    int n=read(),m=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        root[i]=bt();
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),z=read();
        int l=cha(x,y);
        add(root[x],1,N-5,z,1);
        add(root[y],1,N-5,z,1);
        add(root[l],1,N-5,z,-1);
        if(fa[l]){
            add(root[fa[l]],1,N-5,z,-1);
        }
    }
    dfs3(1);
    for(int i=1;i<=n;i++){
        write(ans[i]);
        puts("");
    }
	return 0;
}
/*
*/