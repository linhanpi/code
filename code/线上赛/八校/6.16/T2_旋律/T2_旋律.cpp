#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
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
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=2e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=998244353;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}
int sum,f[N],g[N],v[N],ni[N];
signed main(){
    freopen("melody.in","r",stdin);
    freopen("melody.out","w",stdout);
	int n=read();
    v[0]=1;
    int flag=1,last=0;
    for(int i=1;i<=n;i++){
        int now=read();
        if(last&&now!=last)flag=0;
        last=now;
        v[i]=now;v[i]=v[i]*v[i-1]%mod;
        ni[i]=qmi(v[i],mod-2,mod);
    }
    if(flag){
        g[1]=f[1]=v[1];
        for(int i=2;i<=n/2;i++){
            g[i]=v[i];
            sum=sum*v[1]%mod;
            if(!(i&1))sum=(sum+g[i/2])%mod;
            g[i]=(g[i]-sum+mod)%mod;
        }
        g[n]=v[n];
        for(int j=1;j<=n/2;j++){
            g[n]=(g[n]-g[j]*(v[n-j]*ni[j]%mod)%mod+mod)%mod;
        }
        cout<<g[n]<<endl;
        return 0;
    }
    g[1]=f[1]=v[1];
    sum=g[1];
    for(int i=2;i<=n/2;i++){
        g[i]=v[i];
        for(int j=1;j<=i/2;j++){
            g[i]=(g[i]-g[j]*(v[i-j]*ni[j]%mod)%mod+mod)%mod;
        }
    }
    g[n]=v[n];
    for(int j=1;j<=n/2;j++){
        g[n]=(g[n]-g[j]*(v[n-j]*ni[j]%mod)%mod+mod)%mod;
    }
    cout<<g[n]<<endl;
	return 0;
}