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
const int N=2e5+5;
const int M=26;
const int mo=7000007;
const int inf=1e18+7;
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
	int dao,quan;
};
vector <node> v[N];
bool loop[N];
bool vis[N];
bool huan,zhuan;
int dp[N][2];
int minn=inf,maxn;
int root;
int lo[N],tot;
int maxlian[N];
int duan;
int qian[N];
int ans[N];
int hz;
int maxpre[N],maxhou[N],mapre[N],mahou[N];
int c[N],d[N],e[N];
void zz(int now,int fa){

}
void dfs1(int now,int fa){
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i].dao;
		if(y==fa)continue;
        if(loop[y])continue;
		dfs1(y,now);
		dp[now][1]=max(dp[now][1],dp[now][0]+dp[y][0]+v[now][i].quan);
		dp[now][0]=max(dp[now][0],dp[y][0]+v[now][i].quan);
	}
	maxn=max(max(dp[now][0],dp[now][1]),maxn);
	return ;
}
void dfs(int now,int fa){
	vis[now]=1;
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i].dao;
		if(y==fa)continue;
		if(vis[y]){
            loop[now]=loop[y]=1;
            qian[1]=0;
            qian[2]=v[now][i].quan;
            lo[++tot]=y,lo[++tot]=now;
			zhuan=huan=1;
			return ;
		}
		dfs(y,now);
		if(zhuan){
			if(loop[now])duan=v[now][i].quan,hz,zhuan=0;
			else{
                loop[now]=1;
                lo[++tot]=now;
                qian[tot]=qian[tot-1]+v[now][i].quan;
                hz=qian[tot];
			}
		}
		if(huan)return ;
	}
	return ;
}
signed main(){
    int n=read();
    for(int i=1;i<=n;i++){
    	int a=read(),b=read(),w=read();
    	v[a].push_back({b,w});
    	v[b].push_back({a,w});
	}
	dfs(1,0);
    for(int i=1;i<=tot;i++){
        // memset(dp,0,sizeof(dp));
        dfs1(lo[i],0);
        // cout<<"i "<<i<<" maxn "<<maxn<<endl;
        maxlian[i]=dp[lo[i]][0];
        maxpre[i]=maxhou[i]=-inf;
    }
    maxpre[0]=maxhou[tot+1]=mapre[0]=mahou[tot+1]=-inf;
    for(int i=1;i<=tot;i++){
        mapre[i]=max(mapre[i-1],maxlian[i]+qian[i]);
        maxpre[i]=max(maxpre[i-1],maxlian[i]-qian[i]);
    }
    for(int i=tot;i;i--){
        mahou[i]=max(mahou[i+1],maxlian[i]+hz-qian[i]);
        maxhou[i]=max(maxhou[i+1],maxlian[i]-hz+qian[i]);
    }
    for(int i=1;i<=tot;i++){
        c[i]=max(c[i-1],maxpre[i-1]+qian[i]+maxlian[i]);
        d[i]=max(d[i+1],maxhou[i+1]+hz-qian[i]+maxlian[i]);
        e[i]=duan+mapre[i]+mahou[i+1];
    }
    // cout<<"duan "<<duan<<endl;
    // for(int i=1;i<=tot;i++){
    //     cout<<"i "<<i<<" "<<lo[i]<<" "<<qian[i]<<" "<<hz-qian[i]<<" "<<maxlian[i]<<" "<<c[i]<<" "<<d[i]<<" "<<e[i]<<" "<<maxpre[i]<<" "<<maxhou[i]<<" "<<mapre[i]<<" "<<mahou[i]<<endl;
    // }
    for(int i=1;i<tot;i++){
        minn=min(minn,max(c[i],max(d[i+1],e[i])));
    }
	// minn=min(minn,c[tot]);
    minn=max(maxn,minn);
	// if(minn==7649618277)cout<<maxn<<" "<<minn<<endl;
    // cout<<fixed<<setprecision(1)<<1.0*minn/2<<endl;
	cout<<minn<<endl;
	return 0;
}
/*
*/