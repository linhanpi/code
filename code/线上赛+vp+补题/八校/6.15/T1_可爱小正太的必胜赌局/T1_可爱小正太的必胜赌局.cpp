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
const int N=5e2+5;
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
vector <int> a[3],b[3];
int f[N*1000],g[3][N*1000];
int sum,num[3];
signed main(){
    freopen("shota.in","r",stdin);
    freopen("shota.out","w",stdout);
	int n=read();
    for(int i=1;i<=n;i++){
        char t;cin>>t;
        int tt=(t=='T')?0:((t=='A')?1:2);
        int aa=read(),bb=read();
        sum+=aa+bb;
        a[tt].push_back(bb),b[tt].push_back(aa+bb);
    }
    for(int i=0;i<(int)a[0].size();i++){
        num[0]+=b[0][i];
        for(int j=num[0]-b[0][i];~j;j--){
            f[j+b[0][i]]=max(f[j+b[0][i]],f[j]+a[0][i]);
        }
    }
    int len=a[0].size();
    g[0][0]=f[0];
    for(int i=1;i<=sum;i++){
        g[0][i]=max(g[0][i-1],f[i]);
    }
    memset(f,0,sizeof(f));
    for(int i=0;i<(int)a[1].size();i++){
        num[1]+=b[1][i];
        for(int j=num[1]-b[1][i];~j;j--){
            f[j+b[1][i]]=max(f[j+b[1][i]],f[j]+a[1][i]);
        }
    }
    len=a[1].size();
    g[1][0]=f[0];
    for(int i=1;i<=sum;i++){
        g[1][i]=max(g[1][i-1],f[i]);
    }
    memset(f,0,sizeof(f));
    for(int i=0;i<(int)a[2].size();i++){
        num[2]+=b[2][i];
        for(int j=num[2]-b[2][i];~j;j--){
            f[j+b[2][i]]=max(f[j+b[2][i]],f[j]+a[2][i]);
        }
    }
    len=a[2].size();
    g[2][0]=f[0];
    for(int i=1;i<=sum;i++){
        g[2][i]=max(g[2][i-1],f[i]);
    }
    int ans=0;
    for(int i=0;i<=sum;i++){
        ans=max(ans,g[0][i]+g[1][i]+g[2][i]-i);
    }
    cout<<ans<<endl;
	return 0;
}
