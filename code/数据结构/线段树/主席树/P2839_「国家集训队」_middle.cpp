/*
 * @Author: watering_penguin 
 * @Date: 2023-02-18 14:55:00 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-22 17:42:03
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
    int ls,rs,lmax,rmax,sum;
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
    #define lmax(p) tree[p].lmax
    #define rmax(p) tree[p].rmax
    #define sum(p) tree[p].sum
}tree[N];
int root[N],tot;
int bt(){
    ++tot;
    ls(tot)=rs(tot)=lmax(tot)=rmax(tot)=sum(tot)=0;
    return tot;
}
void pu(int p){
    sum(p)=sum(ls(p))+sum(rs(p));
    lmax(p)=max(lmax(ls(p)),sum(ls(p))+lmax(rs(p)));
    rmax(p)=max(rmax(rs(p)),sum(rs(p))+rmax(ls(p)));
    return ;
}
int insert(int now,int l,int r,int pos,int x){
    int p=bt();
    tree[p]=tree[now];
    if(l==r){
        sum(p)=x;
        if(sum(p)>0)lmax(p)=x,rmax(p)=x;
        else lmax(p)=rmax(p)=0;
        return p;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)ls(p)=insert(ls(p),l,mid,pos,x);
    else rs(p)=insert(rs(p),mid+1,r,pos,x);
    pu(p);
    return p;
}
int chasum(int p,int l,int r,int L,int R){
    if(L<=l&&r<=R)return sum(p);
    int mid=(l+r)>>1;
    int res=0;
    if(L<=mid)res+=chasum(ls(p),l,mid,L,R);
    if(mid<R)res+=chasum(rs(p),mid+1,r,L,R);
    return res;
}
pii chahmx(int p,int l,int r,int L,int R){
    if(L<=l&&r<=R){
        return {sum(p),rmax(p)};
    }
    int mid=(l+r)>>1;
    pii lres=lpii,rres=lpii;
    if(L<=mid)lres=chahmx(ls(p),l,mid,L,R);
    if(mid<R)rres=chahmx(rs(p),mid+1,r,L,R);
    pii res;
    res.first=lres.first+rres.first;
    res.second=max(rres.second,rres.first+lres.second);
    return res;
}
pii chaqmx(int p,int l,int r,int L,int R){
    if(L<=l&&r<=R){
        return {sum(p),lmax(p)};
    }
    int mid=(l+r)>>1;
    pii lres=lpii,rres=lpii;
    if(L<=mid)lres=chaqmx(ls(p),l,mid,L,R);
    if(mid<R)rres=chaqmx(rs(p),mid+1,r,L,R);
    pii res;
    res.first=lres.first+rres.first;
    res.second=max(lres.second,lres.first+rres.second);
    return res;
}
int a[N],d[N];
vector <int> v[N];
int q[N];
int n;
bool ck(int mid){
    int res=0;
    res+=chasum(root[mid],1,n,q[1],q[2]);
    // cout<<"mid "<<mid<<" "<<q[1]<<" "<<q[2]<<" "<<res<<endl;
    res+=chahmx(root[mid],1,n,q[0],q[1]-1).second;
    // cout<<"hmx "<<chahmx(root[mid],1,n,q[0],q[1]-1).second<<endl;
    res+=chaqmx(root[mid],1,n,q[2]+1,q[3]).second;
    // cout<<"qmx "<<chaqmx(root[mid],1,n,q[2]+1,q[3]).second<<endl;
    return res>=0;
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=d[i]=read();
    sort(d+1,d+n+1);
    int len=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(d+1,d+len+1,a[i])-d,v[a[i]].push_back(i);
    for(int i=1;i<=n;i++){
        root[0]=insert(root[0],1,n,i,1);
    }
    for(int i=1;i<=len+1;i++){
        root[i]=root[i-1];
        for(int y:v[i]){
            // cout<<i<<" "<<y<<endl;
            root[i]=insert(root[i],1,n,y,-1);
        }
    }
    int T=read();
    int last=0;
    while(T--){
        for(int i=0;i<4;i++)q[i]=(read()+last)%n+1;
        sort(q,q+4);
        int l=1,r=len;
        while(l<r){
            // cout<<"l r "<<l<<" "<<r<<endl;
            int mid=(l+r)>>1;
            if(ck(mid))l=mid+1;
            else r=mid;
        }
        last=d[l];
        cout<<d[l]<<endl;
    }
    return 0;
}