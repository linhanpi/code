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
const int N=3e6+5;
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
int l[N],r[N];
int ans=0;
int a[N];
int n;
void dfs(int now){
    if(now==n+1){
        // cout<<"--------------------\n";
        bool flag=0;
        for(int i=1;i<=n;i++){
            // cout<<"i "<<i<<" "<<a[i]<<endl;
            int zuo=0,you=0;
            for(int j=i-1;j;j--){
                if(a[j]<=a[i])zuo++;
                else break;
            }
            for(int j=i+1;j<=n;j++){
                if(a[j]<a[i])you++;
                else break;
            }
            if(abs(zuo-you)>2){
                flag=1;
                break;
            }
        }
        if(flag)return ;
        ans++;
        return ;
    }
    for(int i=l[now];i<=r[now];i++){
        a[now]=i;
        dfs(now+1);
    }
    return ;
}
signed main(){
    freopen("robot.in","r",stdin);
    freopen("robot.out","w",stdout);
	n=read();
    for(int i=1;i<=n;i++){
        l[i]=read(),r[i]=read();
    }
    dfs(1);
    cout<<ans<<endl;
	return 0;
}
