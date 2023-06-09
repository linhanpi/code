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
const int N=4e6+5;
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
int c[N];
int n;
inline void add(int x,int y){
    for(int i=x;i<=n;i+=lowbit(i))c[i]=(c[i]+y+mod)%mod;
    return ;
}
inline int cha(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i))res=(res+c[i]+mod)%mod;
    return res;
}
int p[N],tot,vis[N];
int miu[N],w[N],qian[N];
void ycl(){
    miu[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!vis[i])p[++tot]=i,miu[i]=mod-1;
        for(int j=1;j<=tot&&i*p[j]<=N-5;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                miu[i*p[j]]=0;
                break;
            }
            miu[i*p[j]]=(-miu[i]+mod)%mod;
        }
    }
    for(int i=1;i<=N-5;i++){
        w[i]=miu[i]*i%mod*i%mod;
    }
    return ;
}
int f[N],s[N];
signed main(){
    ycl();
    int ni2=qmi(2,mod-2,mod);
	int q=read();n=read();
    for(int i=1;i<=n;i++)f[i]=i*i%mod;
    for(int d=1;d<=n;d++){
        for(int T=d;T<=n;T+=d){
            s[T]=(s[T]+f[d]*w[T/d]%mod)%mod;
        }
    }
    for(int T=1;T<=n;T++){
        add(T,s[T]);
    }
    while(q--){
        int a=read(),b=read(),x=read(),k=read(),gc=mgcd(a,b);
        int tep=x%mod*gc%mod*gc%mod*qmi(a*b%mod,mod-2,mod)%mod;
        for(int T=gc;T<=n;T+=gc){
            add(T,(-f[gc]+tep+mod)%mod*w[T/gc]%mod);
        }
        f[gc]=tep;
        int res=0;
        for(int l=1,r;l<=k;l=r+1){
            r=k/(k/l);
            res=(res+((k/r)*((k/r)+1)%mod*ni2%mod)*((k/r)*((k/r)+1)%mod*ni2%mod)%mod%mod*(cha(r)-cha(l-1)+mod)%mod)%mod;
        }
        cout<<res<<endl;
    }
	return 0;
}
