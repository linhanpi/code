#include<bits/stdc++.h>
#define int long long
//#define double long double
//#define pii pair <int,int>
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
const int N=4005;
const int M=805;
const int mo=7000007;
const int inf=1e12+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;
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
int n,k;
int dp[N][M],a[N][N];
int ceng;
int w(int j,int i){
    return (a[i][i]-a[i][j-1]-a[j-1][i]+a[j-1][j-1]);
}
void fz(int L,int R,int pl,int pr){
    if(R<L)return ;
    int mid=(L+R)>>1,pos;
    dp[mid][ceng]=inf;
    for(int i=max(1ll,pl);i<=min(mid,pr);i++){
        int res=dp[i-1][ceng-1]+w(i,mid);
        // cout<<i<<" "<<mid<<" "<<w(i,mid)<<endl;
        if(res<dp[mid][ceng])dp[mid][ceng]=res,pos=i;
    }
    if(L==R)return ;
    fz(L,mid-1,pl,pos);
    fz(mid+1,R,pos,pr);
    return ;
}
signed main(){
    n=read(),k=read();
	for(int i=1;i<=n;i++){
        dp[i][0]=inf;
        for(int j=1;j<=n;j++){
            a[i][j]=read();
            a[i][j]=a[i][j]-a[i-1][j-1]+a[i][j-1]+a[i-1][j];
        }
    }
    // cout<<a[8][8]<<" "<<a[7][7]<<" "<<a[7][8]<<" "<<a[8][7]<<endl;
    for(ceng=1;ceng<=k;ceng++){
        fz(1,n,1,n);
    }
	cout<<dp[n][k]/2<<endl;
	return 0;
}
/*
ababbab
aba
1
*/