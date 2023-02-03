/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:52:54 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:52:54 
 */
#include<bits/stdc++.h>
#define int long long
//#define double long double
//#define pii pair <int,int>
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
const int N=1e5+5;
const int M=21;
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
int n,k,l,r;
int a[N],tong[N]={1},dp[N][M];
int ceng,w;
inline void md(int L,int R){
    while(l>L)w+=tong[a[--l]]++;
    while(l<L)w-=--tong[a[l++]];
    while(r>R)w-=--tong[a[r--]];
    while(r<R)w+=tong[a[++r]]++;
    return ;
}
void fz(int L,int R,int pl,int pr){
    int mid=(L+R)>>1,pos;
    dp[mid][ceng]=inf;
    for(int i=max(1ll,pl);i<=min(mid,pr);i++){
        md(i,mid);
        int res=dp[i-1][ceng-1]+w;
        if(res<dp[mid][ceng])dp[mid][ceng]=res,pos=i;
    }
    if(L==R)return ;
    fz(L,mid,pl,pos);
    fz(mid+1,R,pos,pr);
    return ;
}
signed main(){
    // memset(dp,0x3f,sizeof(dp));
    // cout<<dp[0][0]<<endl;
    dp[0][0]=0;
	n=read(),k=read();
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