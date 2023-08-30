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
int n;
int a[N];
int dp[N],shang[N];
vector <int> cun,fn;
signed main(){
	int n=read();
    bool flag=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]>0)flag=1;
    }
    if(!flag){
        int maxd=1;
        for(int i=1;i<=n;i++){
            if(a[i]>a[maxd])maxd=i;
        }
        cout<<a[maxd]<<endl;
        cout<<n-1<<endl;
        for(int i=1;i<maxd;i++){
            cout<<1<<endl;
        }
        for(int i=n;i>maxd;i--){
            cout<<i-maxd+1<<endl;
        }
        return 0;
    }
    for(int i=1;i<=n;i++){
        dp[i]=a[i];
        for(int j=i-2;j>=1;j-=2){
            if(dp[j]+a[i]>dp[i]){
                dp[i]=dp[j]+a[i];
                shang[i]=j;
            }
        }
    }
    int ans=0,now=0;
    for(int i=1;i<=n;i++){
        if(ans<dp[i]){
            ans=dp[i];
            now=i;
        }
    }
    cout<<ans<<endl;
    while(shang[now]){
        cun.push_back(now);
        now=shang[now];
    }
    cun.push_back(now);
    reverse(cun.begin(),cun.end());
    for(int i=1;i<cun[0];i++){
        fn.push_back(1);
    }
    int tot=cun[0]-1;
    for(int i=n;i>=cun[cun.size()-1]+1;i--){
        fn.push_back(i-tot);
    }
    for(int i=0;i<(int)cun.size()-1;i++){
        int cha=cun[i+1]-cun[i];
        if(cun[i+1]-cun[i]==2){
            fn.push_back(2);
            continue;
        }
        for(int j=cun[i]+1;j<cun[i+1]-1;j+=2){
            fn.push_back(3);
        }
        fn.push_back(2);
        tot+=cha;
    }
    cout<<fn.size()<<endl;
    for(int y:fn){
        cout<<y<<endl;
    }
	return 0;
}
