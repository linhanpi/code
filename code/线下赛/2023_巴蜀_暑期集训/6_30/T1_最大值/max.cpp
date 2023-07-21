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
const int N=1e6+5;
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
int p[45][15][5],f[45][(1<<10)-1][35],dp[45][(1<<10)+5][35],g[45];
int ct[(1<<10)+5];
signed main(){
    // freopen("max.in","r",stdin);
    // freopen("max.out","w",stdout);
	int n=read(),m=read(),C=read(),CMAX=m*C;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int c=0;c<=C;c++){
                p[j][i][c]=read();
            }
        }
    }
    for(int i=1;i<=(1<<m)-1;i++){
        int tep=i;
        while(tep){
            ct[i]+=(tep&1);
            tep>>=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int c=0;c<=C;c++){
                f[i][1<<(j-1)][c]=p[i][j][c];
            }
        }
        for(int st=1;st<=(1<<m)-1;st++){
            int k=lowbit(st);
            if(k==st)continue;
            for(int c=0;c<=C*ct[st];c++){
                for(int l=0;l<=min(c,C*ct[st^k]);l++){
                    if((c-l)>C*ct[k])continue;
                    f[i][st][c]=(f[i][st][c]+f[i][st^k][l]*f[i][k][c-l]%mod)%mod;
                }
            }
        }
        for(int st=1;st<=(1<<m)-1;st++){
            for(int c=1;c<=CMAX;c++){
                f[i][st][c]=(f[i][st][c]+f[i][st][c-1])%mod;
            }
        }
    }
    for(int c=0;c<=CMAX;c++)dp[0][(1<<m)-1][c]=1;
    for(int i=1;i<=n;i++){
        for(int st=0;st<=(1<<m)-1;st++){
            for(int k=st;k;k=(k-1)&st){
                for(int l=0;l<=CMAX;l++){
                    dp[i][st^k][l]=(dp[i][st^k][l]+dp[i-1][st][l]*f[i][k][l]%mod)%mod;
                }
            }
            for(int l=0;l<=CMAX;l++)dp[i][st][l]=(dp[i][st][l]+dp[i-1][st][l])%mod;
        }
    }
    int ans=0;
    for(int l=1;l<=CMAX;l++){
        ans=(ans+(dp[n][0][l]-dp[n][0][l-1]+mod)%mod*l%mod)%mod;
    }
    cout<<ans<<endl;
	return 0;
}
/*
大家好我是写不对代码的蠢蛋
*/