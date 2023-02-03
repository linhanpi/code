#include<bits/stdc++.h>
#define int long long
#define double long double
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
int n;
double dp[N],a[N],ans[N];
int ceng;
void fz(int L,int R,int pl,int pr){
    if(L>R) return;
    int mid=(L+R)>>1,pos=pl;
    dp[mid]=a[pl]+sqrt(mid-pl)-a[mid];
    for(int i=max(1ll,pl);i<=min(mid,pr);i++){
        double res=a[i]+sqrt(mid-i)-a[mid];
        if((res-dp[mid])>=eps)dp[mid]=res,pos=i;
    }
    if(L==R)return ;
    fz(L,mid-1,pl,pos);
    fz(mid+1,R,pos,pr);
    return ;
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    fz(1,n,1,n);
    for(int i=1;i<=n;i++){
        ans[i]=dp[i];
    }
    reverse(a+1,a+n+1);
    fz(1,n,1,n);
    for(int i=1;i<=n;i++){
        if((dp[i]-ans[n-i+1])>=eps)ans[n-i+1]=dp[i];
    }
    for(int i=1;i<=n;i++){
        printf("%.0Lf\n",ceil(ans[i]));
    }
	return 0;
}
/*
ababbab
aba
1
*/