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
const int N=2e1+5;
const int M=1e2+5;
const int bzt=14;
const int inf=0x3f3f3f3f3f3f3f3f;
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
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
int d[N][N][2],dp[1<<bzt][N][N],f[1<<bzt];
signed main(){
	int T=read();
    while(T--){
        memset(d,0x3f,sizeof(d));
        memset(dp,0x3f,sizeof(dp));
        memset(f,0x3f,sizeof(f));
        int n=read(),m=read();
        for(int i=1;i<=m;i++){
            int x=read()-1,y=read()-1,z=read();
            if(z<d[x][y][0]){
                d[x][y][1]=d[x][y][0];
                d[x][y][0]=z;
            }
            else if(z<d[x][y][1]){
                d[x][y][1]=z;
            }
            swap(x,y);
            if(z<d[x][y][0]){
                d[x][y][1]=d[x][y][0];
                d[x][y][0]=z;
            }
            else if(z<d[x][y][1]){
                d[x][y][1]=z;
            }
        }
        for(int i=0;i<n;i++)f[1<<i]=0;
        for(int s=1;s<(1<<n);s++){
            for(int x=0;x<n;x++){
                if((s>>x)&1)continue;
                for(int y=0;y<n;y++){
                    if(!((s>>y)&1))continue;
                    if(d[x][y][1]==inf)continue;
                    f[s|(1<<x)]=min(f[s|(1<<x)],f[s]+d[x][y][0]+d[x][y][1]);
                }
            }
            for(int x=0;x<n;x++){
                if((s>>x)&1)continue;
                for(int y=0;y<n;y++){
                    if(!((s>>y)&1))continue;
                    for(int z=0;z<n;z++){
                        if(!((s>>z)&1))continue;
                        if(d[x][z][0]==inf)continue;
                        if(y!=z)dp[s][x][y]=min(dp[s][x][y],f[s]+d[z][x][0]);
                        else dp[s|(1<<x)][x][y]=min(dp[s|(1<<x)][x][y],f[s]+d[z][x][0]);
                    }
                }
            }
            for(int x=0;x<n;x++){
                for(int y=0;y<n;y++){
                    if(!((s>>y)&1)||x==y)continue;
                    if(dp[s][x][y]==inf)continue;
                    for(int z=0;z<n;z++){
                        if(((s>>z)&1)||x==z)continue;
                        if(d[x][z][0]==inf)continue;
                        dp[s|(1<<x)][z][y]=min(dp[s|(1<<x)][z][y],dp[s][x][y]+d[x][z][0]);
                    }
                }
            }
            for(int x=0;x<n;x++){
                if((s>>x)&1)continue;
                for(int y=0;y<n;y++){
                    if(!(s>>y)&1)continue;
                    f[s|(1<<x)]=min(f[s|(1<<x)],dp[s][x][y]+d[x][y][0]);
                }
            }
        }
        if(f[(1<<n)-1]==inf){
            puts("impossible");
            continue;
        }
        cout<<f[(1<<n)-1]<<endl;
    }
	return 0;
}
