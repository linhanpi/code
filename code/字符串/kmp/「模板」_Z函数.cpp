#include<bits/stdc++.h>
// #define int long long//信仰
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
const int N=2e7+5;
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
char a[N],b[N];
int z[N],p[N];
signed main(){
	scanf("%s",b+1);
    scanf("%s",a+1);
    int n=strlen(a+1),m=strlen(b+1);
    z[1]=n;
    for(int i=2,l=0,r=0;i<=n;i++){
        z[i]=(r<i)?0:min(z[i-l+1],r-i+1);
        while(i+z[i]<=n&&a[i+z[i]]==a[z[i]+1])z[i]++;
        if(i+z[i]-1>r){
            l=i,r=i+z[i]-1;
        }
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans^=1ll*i*(z[i]+1);
    }
    cout<<ans<<endl;
    for(int i=1,l=0,r=0;i<=m;i++){
        p[i]=(r<i)?0:min(z[i-l+1],r-i+1);
        while(i+p[i]<=m&&b[i+p[i]]==a[p[i]+1])p[i]++;
        if(i+p[i]-1>r){
            l=i,r=i+p[i]-1;
        }
    }
    ans=0;
    for(int i=1;i<=m;i++){
        ans^=1ll*i*(p[i]+1);
    }
    cout<<ans<<endl;
	return 0;
}
