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
const int inf=INT_MAX;
const int base=131;
const int mod=1e4+7;
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
char s[N],t[N];
int dp[2][N];
struct zdj{
	int t[26];
	#define t(p,i) kmp[p].t[i]
}kmp[N];
int ne[N];
signed main(){
	scanf("%s",s+1);
	scanf("%s",t+1);
	int n=strlen(s+1),m=strlen(t+1);
	t[++m]='#';
	for(int i=2,j=0;i<=m;i++){
		while(j&&t[j+1]!=t[i])j=ne[j];
		j+=(t[j+1]==t[i]);
		ne[i]=j;
	}
	for(int i=0;i<m;i++){
		for(int c=0;c<26;c++){
			if(i>0&&c!=t[i+1]-'a')t(i,c)=t(ne[i],c);
			else t(i,c)=i+('a'+c==t[i+1]);
		}
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=m;j++){
			dp[(i+1)&1][j]=-0x3f3f3f3f3f3f3f3f;
		}
		for(int j=0;j<m;j++){
			if(s[i+1]!='?'){
				int p=t(j,s[i+1]-'a');
				if(p==m-1)dp[(i+1)&1][p]=max(dp[i&1][j]+1,dp[(i+1)&1][p]);
				else dp[(i+1)&1][p]=max(dp[i&1][j],dp[(i+1)&1][p]);
			}
			else{
				for(int c=0;c<26;c++){
					int p=t(j,c);
					if(p==m-1)dp[(i+1)&1][p]=max(dp[i&1][j]+1,dp[(i+1)&1][p]);
					else dp[(i+1)&1][p]=max(dp[i&1][j],dp[(i+1)&1][p]);
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=m;i++){
		ans=max(ans,dp[n&1][i]);
	}
	cout<<ans<<endl;
	return 0;
}