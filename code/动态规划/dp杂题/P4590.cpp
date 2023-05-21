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
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
#define popcount(S) __builtin_popcount(S)
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
char s[N];
int dp[2][40010][3],res[20];
inline int gn(int st,char now){
    int num=0,sum=0,last=0,c=0;
    for(int i=0;i<15;i++){
        sum+=(((c=max(num+(now==s[i]),max(last,num+((st>>i)&1))))-last)<<i);
        num+=(st>>i)&1;
        last=c;
    }
    return sum;
}
int count(int k){
	int res=0;
	for(int i=0;i<15;i++){
		res+=(k>>i)&1;
	}
	return res;
}
signed main(){
	int n=read(),k=read();
    scanf("%s",s);
    dp[0][0][0]=1;
    for(int i=0;i<n;i++){
        memset(dp[(i&1)^1],0,sizeof(dp[(i&1)^1]));
        for(int j=0;j<(1<<k);j++){
            int ne=gn(j,'N');
            (dp[(i&1)^1][ne][1]+=dp[i&1][j][0])%mod;
            (dp[(i&1)^1][ne][1]+=dp[i&1][j][1])%mod;
            (dp[(i&1)^1][ne][1]+=dp[i&1][j][2])%mod;
            ne=gn(j,'O');
            (dp[(i&1)^1][ne][0]+=dp[i&1][j][0])%mod;
            (dp[(i&1)^1][ne][2]+=dp[i&1][j][1])%mod;
            (dp[(i&1)^1][ne][0]+=dp[i&1][j][2])%mod;
            ne=gn(j,'I');
            (dp[(i&1)^1][ne][0]+=dp[i&1][j][0])%mod;
            (dp[(i&1)^1][ne][0]+=dp[i&1][j][1])%mod;
        }
    }
    for(int j=0;j<(1<<k);j++){
        for(int l=0;l<=2;l++){
            (res[count(j)]+=dp[n&1][j][l])%=mod;
        }
    }
    for(int i=0;i<=k;i++){
        cout<<res[i]<<endl;
    }
	return 0;
}