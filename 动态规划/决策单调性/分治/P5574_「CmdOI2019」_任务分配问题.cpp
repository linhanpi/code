#include<bits/stdc++.h>
#define int long long
//#define double long double
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
const int N=25005;
const int M=26;
const int mo=7000007;
const int inf=1e16+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;

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
int n,k,l=1,r=0;
int dp[N][M],tong[N]={1},a[N];
int ceng,w;
int c[N];
inline void add(int x,int y){
    for(int i=x;i<=n;i+=lowbit(i)){
        c[i]+=y;
    }
    return ;
}
inline int ask(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res+=c[i];
    }
    return res;
}
void md(int L,int R){
    while(l>L)l--,w+=ask(a[l]),add(a[l],1);
    while(r<R)r++,add(a[r],1),w+=r-l+1-ask(a[r]);
    while(l<L)add(a[l],-1),w-=ask(a[l]),l++;
    while(r>R)w-=r-l+1-ask(a[r]),add(a[r],-1),r--;
    return ;
}
void fz(int L,int R,int pl,int pr){
    int mid=(L+R)>>1,pos;
    dp[mid][ceng]=inf;
    for(int i=max(1ll,pl);i<=min(mid,pr);i++){
        md(i,mid);
        // cout<<"i mid "<<i<<" "<<mid<<" "<<w<<endl;
        int res=dp[i-1][ceng-1]+(r-l+1)*(r-l)/2-w;
        if(res<dp[mid][ceng])dp[mid][ceng]=res,pos=i;
    }
    if(L==R)return ;
    fz(L,mid,pl,pos);
    fz(mid+1,R,pos,pr);
    return;
}
signed main(){
    n=read(),k=read();
    // memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
	for(int i=1;i<=n;i++){
        a[i]=read();
        dp[i][0]=inf;
    }
	for(ceng=1;ceng<=k;ceng++){
		fz(1,n,1,n);
	}
	cout<<dp[n][k]<<endl;
	return 0;
}
/*
ababbab
aba
1
*/