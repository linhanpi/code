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
int p[N],tot,vis[N],miu[N],jc[N];
inline void ycl(){
    miu[1]=1;
    jc[0]=1;
    for(int i=2;i<=N-5;i++){
        if(!vis[i])p[++tot]=i,miu[i]=-1,vis[i]=tot,jc[tot]=jc[tot-1]*i%mod3;
        for(int j=1;j<=tot&&i*p[j]<=N-5;j++){
            vis[i*p[j]]=j;
            if(i%p[j]==0){
                break;
            }
            miu[i*p[j]]=-miu[i];
        }
    }
    return ;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
char a[105];
signed main(){
    ycl();
	int T=read();
    while(T--){
        int n=read();
        scanf("%s",a+1);
        int len=strlen(a+1);
        int k=0;
        for(int i=1;i<=len;i++){
            k=(k*10+a[i]-'0')%phi2;
        }
        // cout<<k<<endl;
        k+=phi2;
        // cout<<k<<endl;
        int ans=1;
        int i;
        for(i=1;i<=tot&&p[i]*p[i]<=n;i++){
            int now=p[i];
            int res=0;
            int ci,l,r;
            for(ci=0,l=0,r=0;now<=n;ci++,now*=p[i]){
                l=r,r=qmi(n-n/now,k,mod2);
                res=(res+(r-l+mod2)*ci%mod2)%mod2;
            }
            l=r,r=qmi(n,k,mod2);
            res=(res+(r-l+mod2)*ci%mod2)%mod2;
            ans=ans*qmi(p[i],res,mod3)%mod3;
        }
        // cout<<ans<<endl;
        for(int j=1;i<=tot&&p[i]<=n;i=j+1){
            j=n/(n/p[i]);
            while(p[vis[j]]!=j)--j;
            j=vis[j];
            int res=(qmi(n,k,mod2)-qmi(n-(n/p[i]),k,mod2)+mod2)%mod2;
            ans=ans*qmi(jc[j]*qmi(jc[i-1],mod3-2,mod3)%mod3,res,mod3)%mod3;
            // cout<<i<<" "<<j<<" "<<res<<" "<<ans<<endl;
        }
        cout<<ans<<endl;
    }
    return 0;
}
/*
ababbab
aba
1
*/