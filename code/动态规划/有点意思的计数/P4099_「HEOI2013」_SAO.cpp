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
const int N=1e3+5;
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
inline int mjia(int &x,int &y){return (x+y)%mod;}
inline int mjian(int &x,int &y){return (x-y+mod)%mod;}
inline int mcheng(int &x,int &y){return (x*y)%mod;}
int c[N][N],ni[N];
void ycl(){
    c[0][0]=1;
    for(int i=1;i<=N-5;i++){
        c[0][i]=1;
        for(int j=1;j<=i;j++){
            c[j][i]=(c[j-1][i-1]+c[j][i-1])%mod;
        }
    }
    ni[0]=ni[1]=1;
    for(int i=2;i<=N-5;i++){
        ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    }
    return ;
}
struct node{
    int dao,quan;
};
vector <node> v[N];
int dp[N][N],si[N],g[N];
void dfs(int now,int fa){
    si[now]=1;
    dp[now][1]=1;
    for(node it:v[now]){
        int y=it.dao;
        if(y==fa)continue;
        dfs(y,now);
        if(!it.quan){
            for(int i=1;i<=si[now];i++){
                for(int j=1;j<=si[y];j++){
                    int t=dp[now][i]*dp[y][j]%mod*c[si[y]][si[now]+si[y]]%mod;
                    g[i+j]=mjia(g[i+j],t);
                }
            }
            si[now]+=si[y];
            for(int i=1;i<=si[now];i++)dp[now][i]=g[i],g[i]=0;
        }
        else{
            for(int i=1;i<=si[now];i++){
                for(int j=1;j<=si[y];j++){
                    int t=dp[now][i]*dp[y][j]%mod*c[si[y]][si[now]+si[y]]%mod;
                    g[i+j]=mjian(g[i+j],t);
                    g[i]=mjia(g[i],t);
                }
            }
            si[now]+=si[y];
            for(int i=1;i<=si[now];i++)dp[now][i]=g[i],g[i]=0;
        }
    }
    for(int i=1;i<=si[now];i++)dp[now][i]=dp[now][i]*ni[i]%mod;
    return ;
}
signed main(){
    ycl();
	int T=read();
    while(T--){
        int n=read();
        for(int i=1;i<=n;i++)v[i].clear();
        for(int i=1;i<n;i++){
            int a=read()+1;char ch;cin>>ch;int b=read()+1;
            if(ch=='>')swap(a,b);
            v[a].push_back({b,0});
            v[b].push_back({a,1});
        }
        dfs(1,0);
        int ans=0;
        for(int i=1;i<=n;i++)ans=(ans+dp[1][i])%mod;
        cout<<ans<<endl;
    }
	return 0;
}
