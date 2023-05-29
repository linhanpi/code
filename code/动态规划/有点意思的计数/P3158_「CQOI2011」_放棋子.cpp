#include<bits/stdc++.h>
#define int long long//信仰
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
const int N=35+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+9;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
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
inline int fang(int x) {return x*x;}
int zhs[N*N][N*N];
void ycl(){
	zhs[0][0]=1;
	for(int i=1;i<=30*30;i++){
		zhs[0][i]=1;
		for(int j=1;j<=i;j++){
			zhs[j][i]=(zhs[j-1][i-1]+zhs[j][i-1])%mod;
		}
	}
	return ;
}
int g[N][N][N];
int dp[N][N][N];
int a[N];
signed main(){
	ycl();
	int n=read(),m=read(),c=read();
	for(int i=1;i<=c;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=c;k++){
				for(int ii=0;ii<=i;ii++){
					for(int jj=0;jj<=j;jj++){
						g[i][j][k]=(g[i][j][k]+((((i-ii+j-jj)&1)?mod-1:1)*zhs[ii][i]%mod*zhs[jj][j]%mod*zhs[a[k]][ii*jj]%mod+mod))%mod;
					}
				}
			}
		}
	}
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=c;k++){
				for(int l=0;l<=i-1;l++){
					for(int r=0;r<=j-1;r++){
						if((i-l)*(j-r)<a[k])continue;
						dp[i][j][k]=(dp[i][j][k]+dp[l][r][k-1]*g[i-l][j-r][k]%mod*zhs[i-l][n-l]%mod*zhs[j-r][m-r]%mod)%mod;
					}
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans=(ans+dp[i][j][c])%mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
