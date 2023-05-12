#include<bits/stdc++.h>
#define int unsigned long long//信仰
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
const int N=30;
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
int l[N];
char s[N];
int qian[N],hou[N],d[N];
unordered_map <int,int> a[N],b[N][N],c[N];
signed main(){
	int n=read(),m=read();
    l[0]=1;
    for(int i=1;i<=25;i++)l[i]=l[i-1]*base;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        int len=strlen(s+1);
        memset(qian,0,sizeof(qian));
        memset(hou,0,sizeof(hou));
        memset(d,0,sizeof(d));
        for(int j=1;j<=len;j++){
            qian[j]=qian[j-1]*base+s[j];
        }
        for(int j=len;j>=1;j--){
            hou[j]=hou[j+1]+s[j]*l[len-j];
        }
        ++a[len][qian[len]];
        for(int j=1;j<=len;j++){
            d[j]=qian[j-1]*l[len-j]+hou[j+1];
            ++b[len-1][j][d[j]];
        }
        sort(d+1,d+len+1);
        int cnt=unique(d+1,d+len+1)-d-1;
        for(int j=1;j<=cnt;j++)++c[len-1][d[j]];
    }
    for(int i=1;i<=m;i++){
        scanf("%s",s+1);
        int len=strlen(s+1);
        memset(qian,0,sizeof(qian));
        memset(hou,0,sizeof(hou));
        memset(d,0,sizeof(d));
        for(int j=1;j<=len;j++){
            qian[j]=qian[j-1]*base+s[j];
        }
        for(int j=len;j>=1;j--){
            hou[j]=hou[j+1]+s[j]*l[len-j];
        }
        if(a[len][qian[len]]){
            puts("-1");
            continue;
        }
        int ans=0;
        for(int j=1;j<=len;j++){
            d[j]=qian[j-1]*l[len-j]+hou[j+1];
        }
        for(int j=1;j<=len;j++){
            ans+=b[len-1][j][d[j]];
        }
        sort(d+1,d+len+1);
        int cnt=unique(d+1,d+len+1)-d-1;
        for(int j=1;j<=cnt;j++)ans+=a[len-1][d[j]];
        ans+=c[len][qian[len]];
        cout<<ans<<endl;
    }
	return 0;
}
