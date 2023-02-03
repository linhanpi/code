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
const int N=1e6+5;
const int M=(1<<12);
const int mo=7000007;
const int inf=1e9+7;
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
int a[N],ji[N];
int ans=0;
void add(int x){
    int res=x;
    bool flag=0;
    for(int i=60;i>=0;i--){
        if(x&(1ll<<i)){
            if(ji[i])x^=ji[i];
            else{
                ji[i]=x;
                flag=1;
                break;
            }
        }
    }
    if(!flag)ans+=res;
    return ;
}
signed main(){
    int n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    sort(a+1,a+n+1);
    for(int i=n;i>=1;i--){
        add(a[i]);
    }
    cout<<ans<<endl;
    return 0;
}
/*
ababbab
aba
1
*/