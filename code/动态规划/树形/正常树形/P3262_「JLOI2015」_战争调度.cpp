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
const int N=2e3+5;
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
int dz[N][12],zd[N][12];
int dp[N][N],vis[15];
int n,m;
void dfs(int x,int y){
	for(int i=0;i<=1<<y;i++) dp[x][i]=0;
	if(!y){
        for(int i=1;i<=n;i++){
            if(vis[i]) dp[x][1]+=dz[x][i]; 
            else dp[x][0]+=zd[x][i];
        }
        return ;
    }
	vis[y]=0;
    dfs(x<<1,y-1);
    dfs(x<<1|1,y-1);
	for(int i=0;i<=1<<(y-1);i++){
        for(int j=0;j<=1<<(y-1);j++){
            dp[x][i+j]=max(dp[x][i+j],dp[x<<1][i]+dp[x<<1|1][j]);
        }
    }
	vis[y]=1;
    dfs(x<<1,y-1);
    dfs(x<<1|1,y-1);
	for(int i=0;i<=1<<(y-1);i++){
        for(int j=0;j<=1<<(y-1);j++){
            dp[x][i+j]=max(dp[x][i+j],dp[x<<1][i]+dp[x<<1|1][j]);
        }
    }
    return ;
}
signed main(){
	n=read()-1,m=read();
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++){
            dz[i+(1<<n)][j]=read();
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++){
            zd[i+(1<<n)][j]=read();
        }
    }
    dfs(1,n);
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,dp[1][i]);
    }
    cout<<ans<<endl;
	return 0;
}
