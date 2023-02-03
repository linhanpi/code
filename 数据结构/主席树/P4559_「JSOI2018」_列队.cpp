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
const int N=5e5+5;
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
struct node{
    int ls,rs,sum,si;
    node(){
        ls=rs=sum=si=0;
    }
    #define sum(p) tree[p].sum
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
    #define si(p) tree[p].si
}tree[N*30];
int tot;
int insert(int now,int l,int r,int pos){
    int p=++tot;
    tree[p]=tree[now];
    sum(p)+=pos,si(p)++;
    if(l==r){
        return p;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        ls(p)=insert(ls(p),l,mid,pos);
    }
    else rs(p)=insert(rs(p),mid+1,r,pos);
    return p;
}
int gx(int x,int y){
    return (y-x+1)*(x+y)/2;
}
int ask(int p,int q,int l,int r,int k,int pos){
    if(si(q)-si(p)==0)return 0;
    if(l>=pos+k-1)return sum(q)-sum(p)-gx(pos+k-1,pos+k-2+si(q)-si(p));
    if(r<=pos+k-2+si(q)-si(p))return -sum(q)+sum(p)+gx(pos+k-1,pos+k-2+si(q)-si(p));
    int mid=(l+r)>>1;
    return ask(ls(p),ls(q),l,mid,k,pos)+ask(rs(p),rs(q),mid+1,r,k+si(ls(q))-si(ls(p)),pos);
}
int root[N],a[N];
signed main(){
    int n=read(),m=read();
    int maxn=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
        maxn=max(maxn,a[i]);
    }
    for(int i=1;i<=n;i++){
        root[i]=insert(root[i-1],1,maxn,a[i]);
    }
    while(m--){
        int l=read(),r=read(),k=read();
        write(ask(root[l-1],root[r],1,maxn,1,k));
        puts("");
    }
	return 0;
}
/*
*/