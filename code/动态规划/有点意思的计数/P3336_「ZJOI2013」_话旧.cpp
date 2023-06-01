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
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=19940417;
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
inline int qmi(int x,int y,int mod){if(y<0)return 0;int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
struct node{
    int x,y;
}no[N];
bool operator <(const node &x,const node &y){return x.x<y.x;}
bool operator ==(const node &x,const node &y){return x.x==y.x&&x.y==y.y;}
int x[N],y[N];
int dp[N][2];
signed main(){
	int n=read(),k=read();
    for(int i=1;i<=k;i++)no[i].x=read(),no[i].y=read();
    no[++k].x=0,no[k].y=0;
    no[++k].x=n,no[k].y=0;
    sort(no+1,no+k+1);
    k=unique(no+1,no+k+1)-no;
    for(int i=1;i<=k;i++){
        x[i]=no[i].x,y[i]=no[i].y;
        if(x[i]==n)k=i;
    }
    bool wu=0;
    for(int i=2;i<=k;i++)if(((x[i]+y[i])&1)!=((x[i-1]+y[i-1])&1))wu=1;
    dp[1][1]=1;
    for(int i=1,cnt;i<k;i++){
        if(dp[i][0]){
            cnt=((x[i+1]-y[i+1])-(x[i]-y[i]))/2-y[i];
            if(y[i+1]&&(x[i+1]-y[i+1])==(x[i]-y[i]))dp[i+1][0]=mjia(dp[i+1][0],dp[i][0]);
            else if(y[i+1])dp[i+1][0]=mjia(dp[i+1][0],mcheng(dp[i][0],qmi(2,cnt,mod)));
            cnt=((x[i+1]+y[i+1])-(x[i]-y[i]))/2-y[i]-y[i+1];
            if((x[i+1]-y[i+1])!=(x[i]-y[i]))dp[i+1][1]=mjia(dp[i+1][1],mcheng(dp[i][0],max(1ll,qmi(2,cnt,mod))));
        }
        if(dp[i][1]){
            cnt=((x[i+1]-y[i+1])-(x[i]+y[i]))/2-1;
            if(y[i+1]&&(x[i+1]-y[i+1])==(x[i]+y[i]))dp[i+1][0]=mjia(dp[i+1][0],dp[i][1]);
            else if(y[i+1])dp[i+1][0]=mjia(dp[i+1][0],mcheng(dp[i][1],qmi(2,cnt,mod)));
            cnt=((x[i+1]+y[i+1])-(x[i]+y[i]))/2-y[i+1]-1;
            if((x[i+1]+y[i+1])==(x[i]+y[i]))dp[i+1][1]=mjia(dp[i+1][1],dp[i][1]);
            else dp[i+1][1]=mjia(dp[i+1][1],mcheng(dp[i][1],qmi(2,cnt,mod)));
        }
    }
    cout<<dp[k][1]<<" ";
    int ans=0;
    for(int i=1;i<k;i++){
        if(dp[i][0]||(dp[i][1]&&y[i]==0)){
            ans=max(ans,(((x[i+1]+y[i+1])-(x[i]-y[i]))/2));
        }
    }
    cout<<ans<<endl;
	return 0;
}
/*
10 3
2 2
6 2
7 3
*/