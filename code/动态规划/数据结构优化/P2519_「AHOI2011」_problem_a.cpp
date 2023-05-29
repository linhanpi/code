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
struct node{
    int l,r,cnt;
}a[N],b[N];
bool cmp1(const node &x,const node &y){
    if(x.l!=y.l)return x.l<y.l;
    return x.r<y.r;
}
bool cmp2(const node &x,const node &y){
    if(x.r!=y.r)return x.r<y.r;
    return x.l<y.l;
}
bool operator <(const node &x,const node &y){
    return x.r<y.r;
}
int dp[N];
signed main(){
	int n=read();
    for(int i=1;i<=n;i++){
        a[i].l=read()+1,a[i].r=n-read();
    }
    sort(a+1,a+n+1,cmp1);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(a[i].l<=a[i].r)b[++cnt]=a[i];
    }
    int tot=0;
    for(int i=1;i<=cnt;i++){
        if(i==1||b[i].l!=b[i-1].l||b[i].r!=b[i-1].r){
            a[++tot]=b[i],a[tot].cnt=1;
        }
        else a[tot].cnt=min(a[tot].cnt+1,a[tot].r-a[tot].l+1);
    }
    sort(a+1,a+tot+1,cmp2);
    dp[1]=a[1].cnt;
    for(int i=2;i<=tot;i++){
        int l=0,r=i-1;
        while(l<r){
            int mid=(l+r+1)>>1;
            if(a[mid].r<a[i].l)l=mid;
            else r=mid-1;
        }
        dp[i]=max(dp[i-1],dp[l]+a[i].cnt);
    }
    cout<<n-dp[tot]<<endl;
	return 0;
}
