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
const int N=1e2+5;
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
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
vector <int> v[N];
int c[N][13],dp[N][1<<13],val[1<<13],n,m;
void dfs(int now,int fath){
    for(int y:v[now]){
        if(y==fath)continue;
        dfs(y,now);
        for(int j=(1<<m)-1;j;j--){
            for(int k=j;k;k=(k-1)&j){
                dp[now][j]=max(dp[now][j],dp[now][j^k]+dp[y][k]);
            }
        }
    }
    for(int j=(1<<m)-1;j;j--){
        dp[now][j]+=val[j];
    }
    return ;
}
signed main(){
	n=read(),m=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++)c[i][j]=read();
        for(int j=1;j<(1<<m);j++){
            int lowid=(log(lowbit(j))+eps)/log(2);
            dp[i][j]=dp[i][j^lowbit(j)]-c[i][lowid];
        }
    }
    int t=read();
    for(int i=1;i<=t;i++){
        int v=read(),k=read(),s=0;
        for(int i=1;i<=k;i++){
            s|=(1<<(read()-1));
        }
        int tmp=((1<<m)-1)^s;
        val[s]+=v;
        for(int j=tmp;j;j=(j-1)&tmp){
            val[(s|j)]+=v;
        }
    }
    dfs(1,0);
    cout<<dp[1][(1<<m)-1]<<endl;
	return 0;
}
