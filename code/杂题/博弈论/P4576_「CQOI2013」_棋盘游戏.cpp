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
const int N=25+5;
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
int f[2][65][N][N][N][N];
int n;
int dfs(int x,int y,int r1,int c1,int r2,int c2){
	int ans;
	if(y>3*n)return inf;
	if(f[x][y][r1][c1][r2][c2])return f[x][y][r1][c1][r2][c2];
	if(r1==r2&&c1==c2)return x?inf:0;
	if(!x){
		ans=0;
		if(r1>1)ans=max(ans,dfs(1,y+1,r1-1,c1,r2,c2));
        if(r1<n)ans=max(ans,dfs(1,y+1,r1+1,c1,r2,c2));
        if(c1>1)ans=max(ans,dfs(1,y+1,r1,c1-1,r2,c2));
        if(c1<n)ans=max(ans,dfs(1,y+1,r1,c1+1,r2,c2));
	}
	else{
		ans=inf;
		if(r2>1)ans=min(ans,dfs(0,y+1,r1,c1,r2-1,c2));
        if(r2>2)ans=min(ans,dfs(0,y+1,r1,c1,r2-2,c2));
        if(r2<n)ans=min(ans,dfs(0,y+1,r1,c1,r2+1,c2));
        if(r2<n-1)ans=min(ans,dfs(0,y+1,r1,c1,r2+2,c2));
        if(c2>1)ans=min(ans,dfs(0,y+1,r1,c1,r2,c2-1));
        if(c2>2)ans=min(ans,dfs(0,y+1,r1,c1,r2,c2-2));
        if(c2<n)ans=min(ans,dfs(0,y+1,r1,c1,r2,c2+1));
        if(c2<n-1)ans=min(ans,dfs(0,y+1,r1,c1,r2,c2+2));
	}
	return f[x][y][r1][c1][r2][c2]=ans+1;
}
signed main(){
	n=read();
	int r1=read(),c1=read(),r2=read(),c2=read();
	if(abs(r1-r2)+abs(c1-c2)<=1)puts("WHITE 1");
	else{
		cout<<"BLACK "<<dfs(0,1,r1,c1,r2,c2)<<endl;
	}
	return 0;
}
