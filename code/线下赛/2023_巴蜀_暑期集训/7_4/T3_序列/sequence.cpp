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
const int M=10+5;
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
int c[20][20];
void ycl(){
    for(int i=0;i<=15;i++){
        c[0][i]=1;
        for(int j=1;j<=i;j++){
            c[j][i]=(c[j-1][i-1]+c[j][i-1])%mod;
        }
    }
    for(int i=0;i<=15;i++){
        for(int j=3;j<=i;j+=3){
            c[0][i]=(c[0][i]+c[j][i])%mod;
        }
        for(int j=4;j<=i;j+=3){
            c[1][i]=(c[1][i]+c[j][i])%mod;
        }
        for(int j=5;j<=i;j+=3){
            c[2][i]=(c[2][i]+c[j][i])%mod;
        }
    }
    return ;
}
int l[M],r[M];
int dp[2][(1<<10)+5];
vector <int> you[(1<<10)+5];
int cnt[(1<<10)+5];
bool ke[2][35][M],kk[M];
signed main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    ycl();
    int n=read();
    for(int i=1;i<(1<<n);i++){
        int tep=i;
        int tot=0;
        while(tep){
            if(tep&1){
                you[i].push_back(tot);
                cnt[i]++;
            }
            ++tot;
            tep>>=1;
        }
    }
    int ccnt=0;
    for(int i=1;i<=n;i++){
        l[i]=read()-1,r[i]=read();
    }
    for(int k=0;k<=30;k++){
        for(int i=1;i<=n;i++){
            if(l[i]&(1<<k))ke[0][k][i]=1;
            if(r[i]&(1<<k))ke[1][k][i]=1;
        }
    }
    int ans=0;
    for(int rcst=0;rcst<(1<<n);rcst++){
        memset(kk,0,sizeof(kk));
        int tep=rcst,tot=0,cn=0;
        bool flag=0;
        while(tep){
            if(tep&1){
                if(l[tot+1]==0){
                    flag=1;
                    break;
                }
                kk[tot+1]=1;
                ++cn;
            }
            ++tot;
            tep>>=1;
        }
        if(flag)continue;
        memset(dp,0,sizeof(dp));
        dp[1][(1<<n)-1]=1;
        for(int k=30;~k;k--){
            memset(dp[k&1],0,sizeof(dp[k&1]));
            for(int st=0;st<(1<<n);st++){
                if(!dp[(k&1)^1][st])continue;
                int kf=n-cnt[st];
                int ST=0;
                for(int i=1;i<=n;i++){
                    if((st&(1<<(i-1)))&&ke[!kk[i]][k][i])ST+=(1<<(i-1));
                }
                for(int K=ST;K;K=(K-1)&ST){
                    if(kf>=(3-cnt[K]%3)%3){
                        dp[k&1][st^(ST^K)]=(dp[k&1][st^(ST^K)]+dp[(k&1)^1][st]*c[(3-cnt[K]%3)%3][kf]%mod)%mod;
                    }
                }
                dp[k&1][st^ST]=(dp[k&1][st^ST]+dp[(k&1)^1][st]*c[0][kf]%mod)%mod;
            }
        }
        
    }
    cout<<ans<<endl;
    return 0;
}