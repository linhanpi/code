#include<bits/stdc++.h>
#define int long long
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
    int l,r,sum,add;
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define sum(p) tree[p].sum
    #define add(p) tree[p].add
}tree[N*4];
void bt(int p,int l,int r){
    l(p)=l,r(p)=r;
    sum(p)=add(p)=0;
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    bt(lson,l,mid);
    bt(rson,mid+1,r);
    return ;
}
void pu(int p){
    sum(p)=sum(lson)+sum(rson);
    return ;
}
void pd(int p){
    if(add(p)){
        sum(lson)+=(r(lson)-l(lson)+1)*add(p);
        sum(rson)+=(r(rson)-l(rson)+1)*add(p);
        add(lson)+=add(p);
        add(rson)+=add(p);
        add(p)=0;
    }
    return ;
}
void cg(int p,int L,int R,int v){
    if(L<=l(p)&&r(p)<=R){
        sum(p)+=(r(p)-l(p)+1)*v;
        add(p)+=v;
        return ;
    }
    int mid=(l(p)+r(p))>>1;
    pd(p);
    if(L<=mid)cg(lson,L,R,v);
    if(R>mid)cg(rson,L,R,v);
    pu(p);
    return ;
}
int ask(int p,int L,int R){
    if(L<=l(p)&&r(p)<=R){
        return sum(p);
    }
    int mid=(l(p)+r(p))>>1;
    int res=0;
    pd(p);
    if(L<=mid)res+=ask(lson,L,R);
    if(R>mid)res+=ask(rson,L,R);
    pu(p);
    return res;
}
struct cha{
    int op,l,r,id,v;
}q[N],tl[N],tr[N];
int ans[N];
int n,m;
inline void ztef(int st,int en,int l,int r){
    if(l==r){
        for(int i=st;i<=en;i++){
            if(q[i].op==2)ans[q[i].id]=l;
        }
        return ;
    }
    int mid=(l+r)>>1;
    bool fl=0,fr=0;
    int L=0,R=0;
    // bt(1,1,n);
    for(int i=st;i<=en;i++){
        if(q[i].op==1){
            if(q[i].v>mid){
                cg(1,q[i].l,q[i].r,1);
                tr[++R]=q[i];
            }
            else tl[++L]=q[i];
        }
        else{
            int v=ask(1,q[i].l,q[i].r);
            if(v<q[i].v){
                q[i].v-=v;
                fl=1;
                tl[++L]=q[i];
            }
            else{
                fr=1;
                tr[++R]=q[i];
            }
        }
    }
    for(int i=st;i<=en;i++){
        if(q[i].op==1&&q[i].v>mid)cg(1,q[i].l,q[i].r,-1);
    }
    for(int i=1;i<=L;i++)q[st+i-1]=tl[i];
    for(int i=L+1;i<=L+R;i++)q[st+i-1]=tr[i-L];
    if(fl)ztef(st,st+L-1,l,mid);
    if(fr)ztef(st+L,en,mid+1,r);
    return ;
}
signed main(){
    n=read(),m=read();
    bt(1,1,n);
    int Q=0;
    for(int i=1;i<=m;i++){
        q[i].op=read(),q[i].l=read(),q[i].r=read(),q[i].v=read();
        if(q[i].op==2)q[i].id=++Q;
    }
    ztef(1,m,-n,n);
    for(int i=1;i<=Q;i++){
        write(ans[i]);
        puts("");
    }
	return 0;
}
/*
*/