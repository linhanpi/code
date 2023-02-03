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
const int M=26;
const int mo=7000007;
const int inf=1e16+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;
const double eps=1e-6;
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
int a[N];
int dp[N];
int sum[N];
int ll;
int w(int i,int j){
	int res=sum[j]-sum[i]-ll+j-i-1;
	return res*res;
}
struct node{
	int j,l,r;
}q[N];
int top;
int ef(int i){
	int l=q[top].l,r=q[top].r;
	while(l<=r){
		int mid=(l+r)>>1;
		if(dp[i]+w(i,mid)<dp[q[top].j]+w(q[top].j,mid))r=mid-1;
		else l=mid+1;
	}
	return l;
}
signed main(){
	memset(dp,0x3f,sizeof(dp));
	int n=read(),now=1;
	ll=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	} 
	dp[0]=0;
	q[++top]={0,1,n};
	for(register int i=1;i<=n;++i){
		dp[i]=dp[q[now].j]+w(q[now].j,i);
// 		cout<<"i "<<q[now].j<<" "<<dp[i]<<endl;
		while(i<q[top].l&&dp[i]+w(i,q[top].l)<dp[q[top].j]+w(q[top].j,q[top].l))top--;
		int pos=ef(i);
		q[top].r=pos-1;
		if(pos<=n)q[++top]={i,pos,n};
		if(i==q[now].r)now++;
	}
	cout<<dp[n]<<endl;
	return 0;
}
/*
5
(()()
1 1 2 2
*/