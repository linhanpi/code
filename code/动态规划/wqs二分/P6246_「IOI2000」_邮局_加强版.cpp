#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
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
const int inf=1e11+7;
const int base=131;
const int mod=1e11+7;
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
#define w(l,r) (sum[r]-sum[l+r+1>>1]+(((l+r+1>>1)<<1)-l-r)*x[l+r+1>>1]-sum[l+r+1>>1]+sum[l])
int x[N],sum[N];
// int w(int l,int r){
	// int pos=(l+r+1)>>1;
	// return (sum[r]-sum[pos])-x[pos]*1ll*(r-pos)+x[pos]*1ll*(pos-l)-(sum[pos]-sum[l]);
// }
struct dpdata{
    int res;
    int x;
}dp[N];
struct dldata{
    int pos,l,r;
}q[N];
int now,top;
int ef(int i){
    int l=q[top].l,r=q[top].r+1;
    while(l<r){
        int mid=(l+r)>>1;
        if(dp[i].res+w(i,mid)>=dp[q[top].pos].res+w(q[top].pos,mid))l=mid+1;
        else r=mid;
    }
    return l;
}
signed main(){
	int n=read(),k=read();
    for(int i=1;i<=n;i++)x[i]=read();
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+x[i];
    sum[n+1]=sum[n];
    int l=-1e9,r=1e9,ans=0;
    // cout<<(w(1,2))<<endl;
    while(l<r){
        top=0;
        int mid=(l+r+1)>>1;
        q[++top]={0,1,n};
        now=1;
        for(int i=1;i<=n;i++){
            dp[i].res=dp[q[now].pos].res+w(q[now].pos,i)-mid;
            dp[i].x=dp[q[now].pos].x+1;
            while(i<q[top].l&&dp[i].res+w(i,q[top].l)<dp[q[top].pos].res+w(q[top].pos,q[top].l))top--;
            int pos=ef(i);
            q[top].r=pos-1;
            if(pos<=n)q[++top]={i,pos,n};
            if(i>=q[now].r)now++;
        }
        if(dp[n].x<=k){
            l=mid;
            ans=dp[n].res+mid*k;
        }
        else{
            r=mid-1;
            // cout<<mid<<" "<<dp[n].res<<" "<<dp[n].x<<endl;
        }
    }
    // cout<<l<<endl;
    cout<<ans<<endl;
	return 0;
}
