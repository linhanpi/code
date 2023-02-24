/*
 * @Author: watering_penguin 
 * @Date: 2023-02-22 17:11:04 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-23 17:31:53
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
const int N=2e6+5;
const int M=6e4+5;
const int mo=7000007;
const int inf=1e16+9;
const int base=131;
const int mod=1e9+7;
const double eps=1e-6;
const pii lpii={0,0};
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
    x%=mod;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
struct node{
    int op,x,l,r,k,v,i;
}Q[N],tl[N],tr[N];
bool operator <(const node &x,const node y){
    if(x.x!=y.x)return x.x<y.x;
    return x.op<y.op;
}
int n;
int c[N];
void add(int x,int y){
    for(int i=x+1;i<=n+1;i+=lowbit(i)){
        c[i]+=y;
    }
    return ;
}
int cha(int x){
    int res=0;
    for(int i=x+1;i;i-=lowbit(i)){
        res+=c[i];
    }
    return res;
}
vector <int> v[N];
int fa[N],si[N],son[N],dep[N],tp[N],st[N],ed[N],num;
void dfs1(int now){
    si[now]=1;
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
    return ;
}
void dfs2(int now,int top){
    tp[now]=top;
    st[now]=++num;
    if(son[now])dfs2(son[now],top);
    for(int y:v[now]){
        if(y==fa[now]||y==son[now])continue;
        dfs2(y,y);
    }
    ed[now]=num;
    return ;
}
int lca(int x,int y){
    while(tp[x]!=tp[y]){
        if(dep[tp[x]]<dep[tp[y]])swap(x,y);
        x=fa[tp[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
int gs(int x,int y){
    while(tp[x]!=tp[y]){
        if(fa[tp[x]]==y)return tp[x];
        x=fa[tp[x]];
    }
    return tp[x]==x?x:son[y];
}
int ans[N];
int d[N];
void ztef(int st,int en,int l,int r){
    // cout<<"st en "<<st<<" "<<en<<" "<<l<<" "<<r<<endl;
    // if(st>en)return ;
    if(l==r){
        for(int i=st;i<=en;i++){
            if(Q[i].op)ans[Q[i].i]=d[l];
        }
        return ;
    }
    int mid=(l+r)>>1;
    int sl=0,sr=0,L=0,R=0;
    for(int i=st;i<=en;i++){
        if(!Q[i].op){
            // cout<<"jia "<<Q[i].op<<" "<<Q[i].x<<" "<<Q[i].l<<" "<<Q[i].r<<" "<<Q[i].k<<" "<<Q[i].v<<endl;
            if(Q[i].k<=mid){
                add(Q[i].l,Q[i].v),add(Q[i].r+1,-Q[i].v);
                tl[++L]=Q[i];
            }
            else tr[++R]=Q[i];
        }
        else{
            int res=cha(Q[i].l);
            // cout<<"cha "<<Q[i].op<<" "<<Q[i].x<<" "<<Q[i].l<<" "<<Q[i].r<<" "<<Q[i].k<<" "<<Q[i].v<<" "<<res<<endl;
            if(res>=Q[i].k)sl=1,tl[++L]=Q[i];
            else sr=1,Q[i].k-=res,tr[++R]=Q[i];
        }
    }
    // for(int i=st;i<=en;i++){
    //     if(!Q[i].op)if(Q[i].k<=mid)add(Q[i].l-1,-Q[i].v),add(Q[i].r,Q[i].v);
    // }
    for(int i=1;i<=L;i++)Q[st+i-1]=tl[i];
    for(int i=L+1;i<=L+R;i++)Q[st+i-1]=tr[i-L];
    // cout<<"-----------------------------------------\n";
    if(sl)ztef(st,st+L-1,l,mid);
    if(sr)ztef(st+L,en,mid+1,r);
    return ;
}
signed main(){
    // freopen("fruit2.in","r",stdin);
    // freopen("1.txt","w",stdout);
    n=read();
    int m=read(),T=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs1(1);
    dfs2(1,1);
    int cnt=0;
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),k=read();
        d[i]=k;
        if(st[x]>st[y])swap(x,y);
        if(st[x]<=st[y]&&ed[y]<=ed[x]){
            int z=gs(y,x);
            Q[++cnt]={0,1,st[y],ed[y],k,1,0};
            Q[++cnt]={0,st[z],st[y],ed[y],k,-1,0};
            if(ed[z]<n){
                Q[++cnt]={0,st[y],ed[z]+1,n,k,1,0};
                Q[++cnt]={0,ed[y]+1,ed[z]+1,n,k,-1,0};
            }
        }
        else{
            Q[++cnt]={0,st[x],st[y],ed[y],k,1,0};
            Q[++cnt]={0,ed[x]+1,st[y],ed[y],k,-1,0};
        }
    }
    sort(d+1,d+m+1);
    int len=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=cnt;i++)Q[i].k=lower_bound(d+1,d+len+1,Q[i].k)-d;
    for(int i=1;i<=T;i++){
        int x=read(),y=read(),k=read();
        if(st[x]>st[y])swap(x,y);
        Q[++cnt]={1,st[x],st[y],0,k,0,i};
    }
    sort(Q+1,Q+cnt+1);
    // for(int i=1;i<=cnt;i++){
    //     cout<<Q[i].x<<endl;
    // }
    ztef(1,cnt,1,len);
    for(int i=1;i<=T;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
