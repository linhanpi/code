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
const int N=2e6+5;
const int M=(1<<12);
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
int mod=20100403;
inline int qmi(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int jc[N];
int vis[N];
int p[N],tong[N],mp[N],tot;
inline void ycl(){
	for(register int i=2;i<=N-5;++i){
		if(!vis[i])p[++tot]=i,mp[i]=tot;
		for(register int j=1;j<=tot&&i*p[j]<=N-5;++j){
			vis[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		}
	}
	return ;
}
// inline int C(int n,int m){return jc[m]*ni[n]%mod*ni[m-n]%mod;}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
signed main(){
	ycl();
	int n=read();
	mod=read();
	for(register int i=2;i<=2*n;++i){
		if(i==n+1)continue;
		if(!vis[i]){
			if(i<=n)tong[mp[i]]--;
			else tong[mp[i]]++;
			continue;
		}
		int tep=i;
		for(register int j=1;p[j]*p[j]<=tep;++j){
			while(tep%p[j]==0){
				if(i<=n)--tong[j];
				else ++tong[j];
				tep/=p[j];
			}
		}
		if(i<=n)--tong[mp[tep]];
		else ++tong[mp[tep]];
	}
	int ans=1;
	for(register int j=1;j<=tot&&p[j]<=2*n;++j){
		// cout<<p[j]<<" "<<tong[j]<<endl;
		ans=ans*qmi(p[j],tong[j],mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
/*
ababbab
aba
1
*/