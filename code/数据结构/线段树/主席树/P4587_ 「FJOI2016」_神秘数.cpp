/*
 * @Author: watering_penguin 
 * @Date: 2023-02-04 11:00:02 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-04 13:58:02 
 */

#include<bits/stdc++.h>
//#define int long long
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
const int M=1e8+5;
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
struct hjt_tree{
	int ls,rs,sum;
	#define ls(p) tree[p].ls
	#define rs(p) tree[p].rs
	#define sum(p) tree[p].sum
}tree[N*100];
int root[N],tot;
int bt(){
	tot++;
	ls(tot)=rs(tot)=sum(tot)=0;
	return tot;
}
void pu(int p){
	sum(p)=sum(ls(p))+sum(rs(p));
	return ;
}
int insert(int now,int l,int r,int pos){
	int p=bt();
	tree[p]=tree[now];
	if(l==r){
		sum(p)+=pos;
		return p;
	}
	int mid=(l+r)>>1;
	if(pos<=mid){
		ls(p)=insert(ls(p),l,mid,pos);
	}
	else rs(p)=insert(rs(p),mid+1,r,pos);
	pu(p);
	return p;
}
int ask(int p,int q,int l,int r,int k){
	if(l==r)return sum(q)-sum(p);
	int mid=(l+r)>>1,res=0;
	if(k>mid){
		return sum(ls(q))-sum(ls(p))+ask(rs(p),rs(q),mid+1,r,k);
	}
	else return ask(ls(p),ls(q),l,mid,k);
}
int a[N],maxn;
signed main(){
//	freopen("T1.in","r",stdin);
//	freopen("T1.out","w",stdout);
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		maxn=max(maxn,a[i]);
	}
	for(int i=1;i<=n;i++){
		root[i]=insert(root[i-1],0,maxn,a[i]);
	}
	int m=read();
	while(m--){
		int l=read(),r=read();
		if(l>r)swap(l,r);
		int ans=1;
		while(1){
			int res=ask(root[l-1],root[r],0,maxn,ans-1);
//			cout<<"ans res "<<ans<<" "<<res<<endl;
			if(res>=ans-1)ans=res+2;
			else break;
		}
		write(ans-1);
		puts("");
//		cout<<ans-1<<endl;
	}
	return 0;
}
/*
*/