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
const int mod=20100403;
inline int qmi(int x,int y,int mod){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int jc[N],ni[N];
inline void ycl(){
    jc[0]=jc[1]=1;
    ni[0]=ni[1]=1;
    for(int i=2;i<=N-5;i++){
        jc[i]=jc[i-1]*i%mod;
        ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    }
    for(int i=2;i<=N-5;i++){
        ni[i]=ni[i-1]*ni[i]%mod;
    }
    return ;
}
inline int C(int n,int m){return jc[m]*ni[n]%mod*ni[m-n]%mod;}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
signed main(){
    ycl();
    int n=read(),m=read();
    cout<<(C(m,n+m)-C(m-1,n+m)+mod)%mod<<endl;
    return 0;
}
/*
ababbab
aba
1
*/