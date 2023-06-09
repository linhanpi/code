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
inline bool dengyu(double x,double y){return abs(x-y)<=eps;}
inline bool dayu(double x,double y){return x-y>=eps;}
inline bool xiaoyu(double x,double y){return y-x>=eps;}
struct bian{
    int qi,dao,quan;
    bool id;
}e[N];
bool operator <(const bian &x,const bian &y){
    return x.quan<y.quan;
}
int n,m,mw,k;
int f[N];
int get(int x){
    if(x==f[x])return x;
    return f[x]=get(f[x]);
}
inline bool add(int x){
    if(get(e[x].qi)==get(e[x].dao))return 0;
    f[f[e[x].qi]]=f[e[x].dao];
    return 1;
}
bool ck(int mid){
    for(int i=1;i<=n;i++)f[i]=i;
    int ans=0;
    int i=1,j=mw+1;
    while(i<=mw&&j<=m){
        if(e[i].quan-mid<=e[j].quan)ans+=add(i),i++;
        else add(j),j++;
    }
    while(i<=mw)ans+=add(i),i++;
    // cout<<mid<<" "<<ans<<endl;
    return ans<=k;
}
signed main(){
	n=read(),mw=0,m=read(),k=read();
    for(int i=1;i<=m;i++){
        e[i].qi=read()+1,e[i].dao=read()+1,e[i].quan=read(),e[i].id=read();
        if(!e[i].id)swap(e[++mw],e[i]);
    }
    sort(e+1,e+mw+1);
    sort(e+mw+1,e+m+1);
    int l=-100,r=100;
    while(l<r){
        int mid=(l+r)>>1;
        if(ck(mid))l=mid+1;
        else r=mid;
    }
    for(int i=1;i<=n;i++)f[i]=i;
    int ans=0;
    int i=1,j=mw+1;
    while(i<=mw&&j<=m){
        if(e[i].quan-l<=e[j].quan)ans+=(e[i].quan-l)*add(i),i++;
        else ans+=e[j].quan*add(j),j++;
    }
    while(i<=mw)ans+=(e[i].quan-l)*add(i),i++;
    while(j<=m)ans+=e[j].quan*add(j),j++;
    cout<<ans+k*l<<endl;
	return 0;
}