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
const int N=4e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e18;
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
int k[N],b[N];
struct lcxds{
    struct data{
        int maxn;
        #define maxn(p) tree[p].maxn
    }tree[N<<2];
    double zhi(int x,int id){return k[id]*x+b[id];}
    int getmx(int a,int c,int x){
        double b=zhi(x,a),d=zhi(x,c);
        return b<d?a:c;
    }
    void quanxg(int p,int l,int r,int id){
        int mid=(l+r)>>1;
        if(zhi(mid,id)<zhi(mid,maxn(p)))swap(id,maxn(p));
        if(zhi(l,id)<zhi(l,maxn(p)))quanxg(lson,l,mid,id);
        if(zhi(r,id)<zhi(r,maxn(p)))quanxg(rson,mid+1,r,id);
        return ;
    }
    int cha(int p,int l,int r,int pos){
        if(l==r)return maxn(p);
        int mid=(l+r)>>1;
        if(pos<=mid)return getmx(maxn(p),cha(lson,l,mid,pos),pos);
        else return getmx(maxn(p),cha(rson,mid+1,r,pos),pos);
    }
}lcs;
int h[N],w[N],sum[N],dp[N];
#define k(i) (h[i])
#define x(i) (2*h[i])
#define y(i) (dp[i]+h[i]*h[i]-sum[i])
signed main(){
	int n=read();
    for(int i=1;i<=n;i++)h[i]=read();
    for(int i=1;i<=n;i++)w[i]=read(),sum[i]=sum[i-1]+w[i];
    b[0]=inf;
    k[1]=-x(1),b[1]=y(1);
    lcs.quanxg(1,-1e6,1e6,1);
    for(int i=2;i<=n;i++){
        int j=lcs.cha(1,-1e6,1e6,k(i));
        dp[i]=lcs.zhi(k(i),j)+sum[i-1]+h[i]*h[i];
        k[i]=-x(i),b[i]=y(i);
        lcs.quanxg(1,-1e6,1e6,i);
    }
    cout<<dp[n]<<endl;
	return 0;
}
