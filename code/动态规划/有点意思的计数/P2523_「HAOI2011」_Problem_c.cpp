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
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=3e2+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
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
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y,int mod){return (x+y)%mod;}
inline int mjian(int x,int y,int mod){return (x-y+mod)%mod;}
inline int mcheng(int x,int y,int mod){return (x*y)%mod;}
inline int mchu(int x,int y,int mod){return x*qmi(y,mod-2,mod)%mod;}
int hou[N],s[N],c[N][N],dp[N][N];
signed main(){
	int T=read();
    while(T--){
        memset(hou,0,sizeof(hou));
        memset(s,0,sizeof(s));
        memset(c,0,sizeof(c));
        memset(dp,0,sizeof(dp));
        int n=read(),m=read(),p=read();
        c[0][0]=1;
        for(int i=1;i<=n;i++){
            c[i][0]=1;
            for(int j=1;j<=i;j++){
                c[i][j]=mjia(c[i-1][j-1],c[i-1][j],p);
            }
        }
        for(int i=1;i<=m;i++){
            int a=read(),b=read();
            hou[b]++;
        }
        bool flag=0;
        for(int i=n;i;i--){
            s[i]=s[i+1]+hou[i];
            if(s[i]>n-i+1){
                flag=1;
                break;
            }
        }
        if(flag){
            puts("NO");
            continue;
        }
        dp[n][0]=1;
        for(int i=n;i;i--){
            for(int j=0;j<=n;j++){
                if(dp[i][j]){
                    for(int k=hou[i];k<=n-i+1-j-s[i+1];k++){
                        dp[i-1][j+k-hou[i]]=mjia(dp[i-1][j+k-hou[i]],mcheng(dp[i][j],c[n-m-j][k-hou[i]],p),p);
                    }
                }
            }
        }
        cout<<"YES "<<dp[0][n-m]<<endl;
    }
	return 0;
}
