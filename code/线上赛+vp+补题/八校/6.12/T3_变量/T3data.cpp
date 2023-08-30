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
const int N=1e3+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e9+7;
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

signed main(){
    // freopen("variable.in","r",stdin);
    // freopen("variable.out","w",stdout);
    freopen("10.in","w",stdout);
	int T=10;
    cout<<T<<endl;
    while(T--){
        int n=500,W=ran_int(1,1e6),p=1000,q=1000;
        cout<<n<<" "<<W<<" "<<p<<" "<<q<<endl;
        for(int i=1;i<=p;i++){
            cout<<ran_int(1,n)<<" "<<ran_int(1,n)<<" "<<ran_int(1,n)<<" "<<ran_int(1,1000)<<" "<<ran_int(1,1000)<<" "<<ran_int(1,1000)<<" "<<ran_int(1,1000)<<" "<<ran_int(1,1000)<<" "<<ran_int(1,1000)<<endl;
        }
        for(int i=1;i<=q;i++){
            cout<<ran_int(1,n)<<" "<<ran_int(1,n)<<" "<<ran_int(0,2)<<endl;
        }
    }
    system("T3.exe < 10.in > 10.out");
	return 0;
}
