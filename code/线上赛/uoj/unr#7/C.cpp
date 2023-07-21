#include<bits/stdc++.h>
// #define int long long//信仰
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
const int N=50+5;
const int M=1e2+5;
const int bzt=18;
const int inf=0x3f3f3f3f;
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
int a0[N],b0[N],c0[N],d0[N],e0[N],a1[N],b1[N],c1[N],d1[N],e1[N];
int dp[55][55][8005],vis[55][55][8005],noww;
bool fwu[6],tj[6];
int tong[6][55],cn[55],tong1[6][55][55];
inline void ql(int i,int j,int k){
    (vis[i][j][k]!=noww)?(vis[i][j][k]=noww,dp[i][j][k]=inf):0;
    return ;
}
signed main(){
	int n=read();
    fwu[1]=fwu[2]=fwu[3]=fwu[4]=fwu[5]=1;
    for(int i=1;i<=n;i++){
        a0[i]=read(),b0[i]=read(),c0[i]=read(),d0[i]=read(),e0[i]=read(),a1[i]=read(),b1[i]=read(),c1[i]=read(),d1[i]=read(),e1[i]=read();
        tong[1][i]=tong[1][i-1]+a0[i];
        tong[2][i]=tong[2][i-1]+b0[i];
        tong[3][i]=tong[3][i-1]+c0[i];
        tong[4][i]=tong[4][i-1]+d0[i];
        tong[5][i]=tong[5][i-1]+e0[i];
        if(a0[i])fwu[1]=0;
        if(b0[i])fwu[2]=0;
        if(c0[i])fwu[3]=0;
        if(d0[i])fwu[4]=0;
        if(e0[i])fwu[5]=0;
    }
    for(int j=2;j<=n+1;j++){
        for(int i=1;i<j;i++){
            for(int k=1;k<j;k++){
                if(k==i)continue;
                tong1[1][i][j]+=a1[k];
                tong1[2][i][j]+=b1[k];
                tong1[3][i][j]+=c1[k];
                tong1[4][i][j]+=d1[k];
                tong1[5][i][j]+=e1[k];
            }
        }
    }
    int ans=inf;
    for(int st=0;st<(1<<5)-1;st++){
        int tep=st,cnt=0;
        memset(tj,0,sizeof(tj));
        memset(cn,0,sizeof(cn));
        bool flag=0;
        while(tep){
            ++cnt;
            if(tep&1){
                if(fwu[cnt])flag=1;
                tj[cnt]=1;
            }
            tep>>=1;
        }
        if(flag||!tj[1])continue;
        for(int i=1;i<=n+1;i++){
            for(int j=1;j<=5;j++){
                if(tj[j])cn[i]+=tong[j][i-1];
            }
        }
        cn[n+2]=cn[n+1];
        noww=st;
        ql(1,2,0);
        dp[1][2][0]=0;
        for(int j=2;j<=n+1;j++){
            for(int i=1;i<j;i++){
                for(int k=0;k<=cn[j];k++){
                    ql(i,j,k);
                    if(dp[i][j][k]==inf)continue;
                    int re=0,rre=0;
                    if(tj[1])re+=max(0,a0[i]-tong1[1][i][j]);
                    else rre+=max(0,a0[i]-tong1[1][i][j]);
                    if(tj[2])re+=max(0,b0[i]-tong1[2][i][j]);
                    else rre+=max(0,b0[i]-tong1[2][i][j]);
                    if(tj[3])re+=max(0,c0[i]-tong1[3][i][j]);
                    else rre+=max(0,c0[i]-tong1[3][i][j]);
                    if(tj[4])re+=max(0,d0[i]-tong1[4][i][j]);
                    else rre+=max(0,d0[i]-tong1[4][i][j]);
                    if(tj[5])re+=max(0,e0[i]-tong1[5][i][j]);
                    else rre+=max(0,e0[i]-tong1[5][i][j]);
                    ql(j,j+1,k+re);
                    dp[j][j+1][k+re]=min(dp[j][j+1][k+re],dp[i][j][k]+rre);
                    if(j==n+1)continue;
                    re=0,rre=0;
                    if(tj[1])re+=max(0,a0[j]-tong1[1][i][j]);
                    else rre+=max(0,a0[j]-tong1[1][i][j]);
                    if(tj[2])re+=max(0,b0[j]-tong1[2][i][j]);
                    else rre+=max(0,b0[j]-tong1[2][i][j]);
                    if(tj[3])re+=max(0,c0[j]-tong1[3][i][j]);
                    else rre+=max(0,c0[j]-tong1[3][i][j]);
                    if(tj[4])re+=max(0,d0[j]-tong1[4][i][j]);
                    else rre+=max(0,d0[j]-tong1[4][i][j]);
                    if(tj[5])re+=max(0,e0[j]-tong1[5][i][j]);
                    else rre+=max(0,e0[j]-tong1[5][i][j]);
                    ql(i,j+1,k+re);
                    dp[i][j+1][k+re]=min(dp[i][j+1][k+re],dp[i][j][k]+rre);
                }
            }
        }
        int res=inf;
        for(int i=0;i<=cn[n+1];i++){
            ql(n+1,n+2,i);
            res=min(res,max(i,dp[n+1][n+2][i]));
        }
        ans=min(ans,res);
    }
    ans+=n;
    cout<<ans<<endl;
	return 0;
}
