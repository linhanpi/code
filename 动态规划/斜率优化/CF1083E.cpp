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
const int N=1e6+5;
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
struct node{
    int x,y,a;
}no[N];
bool operator <(const node &x,const node &y){
    return x.x<y.x;
}
int dp[N];
#define X(i) (no[i].x)
#define k(i) (no[i].y)
#define Y(i) (dp[i])
int q[N];
inline double xie(int i,int j){
    if(X(i)==X(j))return inf;
    return (double)(dp[i]-dp[j])/(X(i)-X(j));
}
signed main(){
    int n=read();
    for(int i=1;i<=n;i++){
        no[i].x=read(),no[i].y=read(),no[i].a=read();
    }
    sort(no+1,no+n+1);
    int l=1,r=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        while(l<r&&xie(q[l],q[l+1])>=k(i))l++;
        // cout<<l<<" "<<r<<" "<<xie(q[l],q[l+1])<<" "<<k(i)<<endl;
        // cout<<"i "<<i<<" "<<no[i].x<<" "<<no[i].y<<" "<<no[i].a<<" "<<q[l]<<endl;
        dp[i]=dp[q[l]]+no[i].y*(no[i].x-no[q[l]].x)-no[i].a;
        while(l<r&&xie(q[r],q[r-1])<=xie(q[r],i))r--;
        q[++r]=i;
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
	return 0;
}
/*
ababbab
aba
1
*/