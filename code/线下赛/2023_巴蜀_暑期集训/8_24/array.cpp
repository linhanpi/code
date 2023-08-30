#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned long long
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
const int N=8e3+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
int c[N][N],jc[N],mi2[N],ni[N];
int n,p;
int f[N][N],g[N][N];
inline void ycl(){
    c[0][0]=1;
    for(int i=1;i<=N-5;i++){
        c[i][0]=1;
        for(int j=1;j<=N-5;j++){
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
        }
    }
    jc[0]=ni[0]=mi2[0]=1;
    for(int i=1;i<=N-5;i++){
        mi2[i]=mi2[i-1]*2%p;
        jc[i]=jc[i-1]*i%p;
        ni[i]=qmi(jc[i],p-2,p);
    }
    return ;
}
int qian[N];
signed main(){
    freopen("array.in","r",stdin);
	// freopen("array.out","w",stdout);
	n=read(),p=read();
    ycl();
    f[1][1]=1;
    qian[1]=1*ni[0];
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            cout<<"qian "<<j-1<<" "<<qian[j-1]<<endl;
            f[i][j]=qian[j-1]*jc[i-2]%p;
        }
        for(int j=1;j<=i;j++){
            qian[j]=(qian[j]+f[i][j]*ni[i-1]%p)%p;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            cout<<"i j "<<i<<" "<<j<<" "<<f[i][j]<<endl;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            ans=(ans+f[i][j]*c[n][i]%p*jc[n-i]%p*mi2[j-1]%p*(j-1)%p)%p;
        }
    }
    cout<<ans<<endl;
	return 0;
}
/*

(i-2)!/(k-1)!

*/