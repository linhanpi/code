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
int tot;
int a[N],l,r;
bool cmp(int &x,int &y){
    return x>y;
}
void dfs(int now){
    if(now>r)return ;
    if(now)a[++tot]=now;
    dfs(now*10+6);
    dfs(now*10+8);
    return ;
}
bool ck(int a,int b){
    int A=a/mod,B=b/mod;
    if(A*B)return 1;
    return a*b>r;
}
int res;
void dfs2(int now,int lcm,int cnt){
    if(now>tot&&lcm!=1){
        if(cnt&1){
            res+=r/lcm-l/lcm;
        }
        else res-=r/lcm-l/lcm;
        return ;
    }
    if(now>tot)return ;
    dfs2(now+1,lcm,cnt);
    int d=a[now]/mgcd(lcm,a[now]);
    if(!ck(lcm,d))dfs2(now+1,lcm*d,cnt+1);
    return ;
}
bool vis[N];
int work(){
    dfs(0);
    // cout<<tot<<endl;
    sort(a+1,a+tot+1);
    for(int i=1;i<=tot;i++){
        for(int j=1;j<i;j++){
            if(a[i]%a[j]==0){
                vis[i]=1;
                break;
            }
        }
    }
    int sum=0;
    for(int i=1;i<=tot;i++){
        if(!vis[i]){
            if(a[i]<=r/2)a[++sum]=a[i];
            else res+=r/a[i]-l/a[i];
        }
    }
    // cout<<res<<endl;
    tot=sum;
    reverse(a+1,a+tot+1);
    dfs2(1,1,0);
    return res;
}
signed main(){
	l=read()-1,r=read();
    cout<<work()<<endl;
	return 0;
}
