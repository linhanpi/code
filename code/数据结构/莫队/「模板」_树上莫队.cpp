/*
 * @Author: watering_penguin 
 * @Date: 2023-02-09 14:16:19 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-09 15:22:37
 */
#include<bits/stdc++.h>
#define int long long
// #define uint unsigned int
// #define rint register int
// #define ll long long
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
const int M=(1<<26)+5;
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
int st[N],ed[N],ys[N],si[N],son[N],fa[N],tp[N],dep[N],num;
vector <int> v[N];
void dfs1(int now){
    si[now]=1;
    st[now]=++num;
    ys[num]=now;
    dep[now]=dep[fa[now]]+1;
    for(int y:v[now]){
        if(y==fa[now])continue;
        fa[y]=now;
        dfs1(y);
        si[now]+=si[y];
        if(si[y]>si[son[now]]){
            son[now]=y;
        }
    }
    ed[now]=++num;
    ys[num]=now;
    return ;
}
void dfs2(int now,int td){
    tp[now]=td;
    if(!son[now])return ;
    dfs2(son[now],td);
    for(int y:v[now]){
        if(y==fa[now]||y==son[now])continue;
        dfs2(y,y);
    }
    return ;
}
int cha(int x,int y){
    while(tp[x]!=tp[y]){
        if(dep[tp[x]]<dep[tp[y]])swap(x,y);
        x=fa[tp[x]];
    }
    if(dep[x]<dep[y])swap(x,y);
    return y;
}
struct node{
    int l,r,i;
}no[N];
int kuaichang;
bool operator <(const node &x,const node &y){
    if(x.l/kuaichang==y.l/kuaichang){
        return ((x.l/kuaichang)&1)?x.r>y.r:x.r<y.r;
    }
    return x.l<y.l;
}
int a[N],d[N],cnt;
int tong[N],vis[N],res,ans[N];
void jia(int x){
    x=ys[x];
    if(vis[x]){
        res-=(--tong[a[x]]==0);
        vis[x]^=1;
    }
    else{
        res+=(++tong[a[x]]==1);
        vis[x]^=1;
    }
    return ;
}
int L[N];
signed main(){
    int n=read(),m=read();
    kuaichang=sqrt(2*n);
    for(int i=1;i<=n;i++)a[i]=read(),d[++cnt]=a[i];
    sort(d+1,d+n+1);
    cnt=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(d+1,d+cnt+1,a[i])-d;
    }
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs1(1);
    dfs2(1,1);
    // for(int i=1;i<=2*n;i++){
    //     cout<<ys[i]<<" ";
    // }
    // cout<<endl;
    for(int i=1;i<=m;i++){
        int a=read(),b=read();
        if(st[a]>st[b])swap(a,b);
        L[i]=cha(a,b);
        if(L[i]==a){
            L[i]=0;
            no[i].l=st[a],no[i].r=st[b];
        }
        else{
            no[i].l=ed[a],no[i].r=st[b];
        }
        no[i].i=i;
    }
    sort(no+1,no+m+1);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l>no[i].l)jia(--l);
        while(r<no[i].r)jia(++r);
        while(l<no[i].l)jia(l++);
        while(r>no[i].r)jia(r--);
        if(L[no[i].i])jia(st[L[no[i].i]]);
        ans[no[i].i]=res;
        if(L[no[i].i])jia(st[L[no[i].i]]);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}