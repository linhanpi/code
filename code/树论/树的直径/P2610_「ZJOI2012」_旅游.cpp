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
map <pii,int> mp;
vector <int> v[N];
int dp[N][2];
int ans;
void dfs(int now,int fa){
    for(int y:v[now]){
        if(y==fa)continue;
        dfs(y,now);
        if(dp[now][0]<=dp[y][0]+1){
            dp[now][1]=dp[now][0];
            dp[now][0]=dp[y][0]+1;
        }
        else if(dp[now][1]<dp[y][0]+1){
            dp[now][1]=dp[y][0]+1;
        }
    }
    ans=max(ans,dp[now][0]+dp[now][1]);
    return ;
}
signed main(){
	int n=read();
    for(int i=1;i<=n-2;i++){
        int a=read(),b=read(),c=read();
        if(a>b)swap(a,b);
        if(b>c)swap(b,c);
        if(a>b)swap(a,b);
        if(mp.find({a,b})==mp.end())mp[{a,b}]=i;
        else{
            int p=mp[{a,b}];
            v[i].push_back(p);
            v[p].push_back(i);
        }
        if(mp.find({a,c})==mp.end())mp[{a,c}]=i;
        else{
            int p=mp[{a,c}];
            v[i].push_back(p);
            v[p].push_back(i);
        }
        if(mp.find({b,c})==mp.end())mp[{b,c}]=i;
        else{
            int p=mp[{b,c}];
            v[i].push_back(p);
            v[p].push_back(i);
        }
    }
    dfs(1,0);
    cout<<ans+1<<endl;
	return 0;
}
