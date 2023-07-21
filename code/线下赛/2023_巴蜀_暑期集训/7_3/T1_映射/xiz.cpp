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
const ull base=19260817;
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
int a[N],b[N],lasta[N],lastb[N],ans[N],tot,rea[N],reb[N];
ull l[N];
signed main(){
    // freopen("xiz.in","r",stdin);
    // freopen("xiz.out","w",stdout);
    int T=read(),C=read();
    l[0]=1;
    for(int i=1;i<=N-5;i++)l[i]=l[i-1]*base;
    while(T--){
        tot=0;
        int n=read(),m=read();
        for(int i=1;i<=n;i++)a[i]=read();
        for(int i=1;i<=m;i++)b[i]=read();
        ull ha1=0,hb1=0;
        memset(lasta,0,sizeof(lasta));
        memset(lastb,0,sizeof(lastb));
        memset(rea,0,sizeof(rea));
        memset(reb,0,sizeof(reb));
        for(int i=1;i<=m;i++){
            if(lasta[a[i]]){
                ha1=ha1+l[lasta[a[i]]]*(i-lasta[a[i]]);
                rea[lasta[a[i]]]=(i-lasta[a[i]]);
            }
            if(lastb[b[i]]){
                hb1=hb1+l[lastb[b[i]]]*(i-lastb[b[i]]);
                reb[lastb[b[i]]]=(i-lastb[b[i]]);
            }
            // ha1*=base;
            // hb1*=base;
            lasta[a[i]]=i;
            lastb[b[i]]=i;
        }
        if(ha1==hb1)ans[++tot]=1;
        for(int i=m+1;i<=n;i++){
            ha1-=l[i-m]*rea[i-m];
            if(lasta[a[i]]&&lasta[a[i]]>i-m){
                ha1=ha1+l[lasta[a[i]]]*(i-lasta[a[i]]);
                rea[lasta[a[i]]]=(i-lasta[a[i]]);
            }
            // ha1*=base;
            hb1*=base;
            lasta[a[i]]=i;
            if(ha1==hb1)ans[++tot]=i-m+1;
        }
        cout<<tot<<endl;
        for(int i=1;i<=tot;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
	return 0;
}
/*
3 3
6 3
1 2 1 2 3 2
3 1 3
6 3
1 2 1 2 1 2
3 1 3
6 3
1 1 2 1 2 1
3 1 3
*/