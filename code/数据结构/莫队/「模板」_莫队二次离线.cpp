/*
 * @Author: watering_penguin 
 * @Date: 2023-02-09 09:24:10 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-09 12:02:25
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
struct node{
    int l,r,i,ans;
}Q[N];
int a[N];
vector <int> zt;
int kuaichang;
bool operator <(const node &x,const node &y){
    if(x.l/kuaichang==y.l/kuaichang){
        return ((x.l/kuaichang)&1)?x.r>y.r:x.r<y.r;
    }
    return x.l<y.l;
}
int tong[N],sum[N];
struct gai{
    int l,r,op,i;
};
vector <gai> v[N];
int res[N];
signed main(){
    int n=read(),m=read(),k=read();
    kuaichang=sqrt(m);
    if(k>14){
        for(int i=1;i<=m;i++)puts("0");
        return 0;
    }
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=m;i++){
        Q[i].l=read(),Q[i].r=read(),Q[i].i=i;
    }
    for(int i=0;i<16384;i++){
        if(__builtin_popcount(i)==k)zt.push_back(i);
    }
    sort(Q+1,Q+m+1);
    for(int i=1;i<=n;i++){
        sum[i]=tong[a[i]];
        for(int x:zt)++tong[a[i]^x];
    }
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        if(l>Q[i].l)v[r].push_back({Q[i].l,l-1,1,i});
        while(l>Q[i].l)--l,Q[i].ans-=sum[l];
        if(r<Q[i].r)v[l-1].push_back({r+1,Q[i].r,-1,i});
        while(r<Q[i].r)++r,Q[i].ans+=sum[r];
        if(l<Q[i].l)v[r].push_back({l,Q[i].l-1,-1,i});
        while(l<Q[i].l)Q[i].ans+=sum[l],++l;
        if(r>Q[i].r)v[l-1].push_back({Q[i].r+1,r,1,i});
        while(r>Q[i].r)Q[i].ans-=sum[r],--r;
    }
    memset(tong,0,sizeof(tong));
    for(int i=1;i<=n;i++){
        for(int x:zt)++tong[a[i]^x];
        for(gai x:v[i]){
            for(int j=x.l;j<=x.r;j++){
                if(j<=i&&k==0)Q[x.i].ans+=x.op*(tong[a[j]]-1);
                else Q[x.i].ans+=x.op*tong[a[j]];
            }
        }
    }
    for(int i=1;i<=m;i++)Q[i].ans+=Q[i-1].ans;
    for(int i=1;i<=m;i++)res[Q[i].i]=Q[i].ans;
    for(int i=1;i<=m;i++)cout<<res[i]<<endl;
    return 0;
}