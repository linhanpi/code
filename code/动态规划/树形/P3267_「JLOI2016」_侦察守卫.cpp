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
const int N=5e5+5;
const int M=1e2+5;
const int bzt=18;
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
int a[N],vis[N];
vector <int> v[N];
int dp[N][25],g[N][25];
int n,d;
void dfs(int now,int fa){
    if(vis[now])dp[now][0]=g[now][0]=a[now];
    else dp[now][0]=g[now][0]=0;
    for(int i=1;i<=d;i++)dp[now][i]=a[now];
    for(int y:v[now]){
        if(y==fa)continue;
        dfs(y,now);
        for(int j=d;j>=0;j--){
            dp[now][j]=min(dp[now][j]+g[y][j],dp[y][j+1]+g[now][j+1]);
        }
        for(int j=d;j>=0;j--)dp[now][j]=min(dp[now][j+1],dp[now][j]);
        g[now][0]=dp[now][0];
        for(int j=1;j<=d+1;j++){
            g[now][j]=g[now][j]+g[y][j-1];
        }
        for(int j=1;j<=d+1;j++){
            g[now][j]=min(g[now][j],g[now][j-1]);
        }
    }
    for(int j=d;j>=0;j--){
        dp[now][j]=min(dp[now][j+1],dp[now][j]);
    }
    for(int j=1;j<=d+1;j++){
        g[now][j]=min(g[now][j],g[now][j-1]);
    }
    return ;
}
signed main(){
    memset(dp,0x3f,sizeof(dp));
	n=read(),d=read();
    for(int i=1;i<=n;i++)a[i]=read();
    int m=read();
    for(int i=1;i<=m;i++){
        vis[read()]=1;
    }
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1,0);
    int ans=inf;
    for(int i=0;i<=d;i++)ans=min(ans,dp[1][i]);
    cout<<ans<<endl;
	return 0;
}
