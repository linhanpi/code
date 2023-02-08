/*
 * @Author: watering_penguin 
 * @Date: 2023-02-07 11:23:17 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-07 17:33:02
 */
#include<bits/stdc++.h>
#define int long long
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
const int inf=INT_MAX;
const int base=131;
const int mod=51061;
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
int fa[N],dson[N],tp[N],si[N],dep[N],dfn[N],ys[N],cnt;
vector <int> v[N];
int f[N],son[N][2],sw[N];
void dfs1(int now){
    f[now]=fa[now];
    dfn[now]=++cnt;
    ys[cnt]=now;
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
            dson[now]=y;
        }
    }
    return ;
}
void dfs2(int now,int top){
    tp[now]=top;
    if(!dson[now])return ;
    dfs2(dson[now],top);
    for(int i=0;i<(int)v[now].size();i++){
        int y=v[now][i];
        if(y==fa[now]||y==dson[now])continue;
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
struct st{
    int l,r,maxn,add;
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define maxn(p) tree[p].maxn
    #define add(p) tree[p].add
}tree[N*4];
void pu(int p){
    maxn(p)=max(maxn(lson),maxn(rson));
    return ;
}
void pd(int p){
    if(add(p)){
        maxn(lson)+=add(p);
        maxn(rson)+=add(p);
        add(lson)+=add(p);
        add(rson)+=add(p);
        add(p)=0;
    }
    return ;
}
void bt(int p,int l,int r){
    l(p)=l,r(p)=r;
    if(l==r){
        maxn(p)=dep[ys[l]];
        return ;
    }
    int mid=(l+r)>>1;
    bt(lson,l,mid);
    bt(rson,mid+1,r);
    pu(p);
    return ;
}
void gai(int p,int L,int R,int k){
    if(L<=l(p)&&r(p)<=R){
        maxn(p)+=k;
        add(p)+=k;
        return ;
    }
    pd(p);
    int mid=(l(p)+r(p))>>1;
    if(L<=mid)gai(lson,L,R,k);
    if(R>mid)gai(rson,L,R,k);
    pu(p);
    return ;
}
int chaa(int p,int L,int R){
    if(L<=l(p)&&r(p)<=R){
        return maxn(p);
    }
    pd(p);
    int mid=(l(p)+r(p))>>1;
    int res=0;
    if(L<=mid)res=max(res,chaa(lson,L,R));
    if(R>mid)res=max(res,chaa(rson,L,R));
    pu(p);
    return res;
}
bool nroot(int now){
    return son[f[now]][0]==now||son[f[now]][1]==now;
}
void rotate(int now){
    int fa=f[now],gfa=f[fa],k=son[fa][1]==now,w=son[now][k^1];
    if(nroot(fa))son[gfa][son[gfa][1]==fa]=now;
    son[fa][k]=w,son[now][k^1]=fa;
    if(w)f[w]=fa;
    f[now]=gfa,f[fa]=now;
    return ;
}
void splay(int now){
    while(nroot(now)){
        int fa=f[now],gfa=f[fa];
        if(nroot(fa))rotate((son[fa][1]==now)^(son[gfa][1]==fa)?fa:now);
        rotate(now);
    }
    return ;
}
int fsplayr(int now){
    while(son[now][0])now=son[now][0];
    return now;
}
void acc(int x){
    for(int y=0,w;x;x=f[y=x]){
        splay(x);
        if(son[x][1])w=fsplayr(son[x][1]),gai(1,dfn[w],dfn[w]+si[w]-1,1);
        if(son[x][1]=y)w=fsplayr(y),gai(1,dfn[w],dfn[w]+si[w]-1,-1);
    }
    return;
}
signed main(){
    int n=read(),m=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs1(1);
    dfs2(1,1);
    bt(1,1,n);
    while(m--){
        int op=read();
        if(op==1){
            int x=read();
            acc(x);
        }
        if(op==2){
            int x=read(),y=read();
            int l=cha(x,y);
            int ans=chaa(1,dfn[x],dfn[x])+chaa(1,dfn[y],dfn[y])-2*chaa(1,dfn[l],dfn[l])+1;
            write(ans);
            puts("");
        }
        if(op==3){
            int x=read();
            int ans=chaa(1,dfn[x],dfn[x]+si[x]-1);
            write(ans);
            puts("");
        }
    }
    return 0;
}