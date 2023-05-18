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
const int zf=9;
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
int tong[N],sa[N],rk[N],tp[N];
int n,m=10,k,len;
void jspai(){
    for(int i=0;i<=m;i++)tong[i]=0;
    for(int i=1;i<=n;i++)tong[rk[i]]++;
    for(int i=1;i<=m;i++)tong[i]+=tong[i-1];
    for(int i=n;i>=1;i--)sa[tong[rk[tp[i]]]--]=tp[i];
    return ;
}
bool ck(int mid){
    for(int i=1;i<=len;i++){
        int sum=0;
        for(int j=1;j<=k;j++){
            int p=(i+sum-1)%n+1;
            if(rk[p]<=mid)sum+=len;
            else sum+=len-1;
        }
        if(sum>=n)return 1;
    }
    return 0;
}
char s[N];
signed main(){
	n=read(),k=read(),len=(n-1)/k+1;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)s[i+n]=s[i];
    n<<=1;
    for(int i=1;i<=n;i++)rk[i]=s[i]-'0',tp[i]=i;
    jspai();
    for(int w=1,p=0;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;i++)tp[++p]=n-w+i;
        for(int i=1;i<=n;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
        jspai();
        swap(tp,rk);
        rk[sa[1]]=p=1;
        for(int i=2;i<=n;i++){
            rk[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
        }
    }
    int l=1,r=n;n>>=1;
    while(l<r){
        int mid=(l+r)>>1;
        if(ck(mid))r=mid;
        else l=mid+1;
    }
    for(int i=0;i<len;i++)cout<<s[sa[l]+i];
	return 0;
}
