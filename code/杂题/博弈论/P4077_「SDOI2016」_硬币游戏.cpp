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
const int N=20+5;
const int M=3e4+5;
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
inline int mex(int k){for(int i=0;;i++)if(~k>>i&1)return i;}
int sg[N][30][30],lg2[M],lg3[M];
signed main(){
	for(int i=1;i<=M-5;i++){
        if(i%2==0)lg2[i]=lg2[i/2]+1;
        if(i%3==0)lg3[i]=lg3[i/3]+1;
    }
    for(int Q=1;Q<=20;Q++){
        for(int a=1,j=0;a<=M-5;a*=2,j++){
            for(int b=1,k=0;b<=M-5;b*=3,k++){
                int s=0;
                for(int p=1;p<=j;p++){
                    int t=0;
                    for(int q=1;p*q<=j&&q<=Q;q++){
                        t^=sg[Q][j-p*q][k],s|=1<<t;
                    }
                }
                for(int p=1;p<=k;p++){
                    int t=0;
                    for(int q=1;p*q<=k&&q<=Q;q++){
                        t^=sg[Q][j][k-p*q],s|=1<<t;
                    }
                }
                sg[Q][j][k]=mex(s);
            }
        }
    }
    int T=read();
    while(T--){
        int ans=0;
        int n=read(),k=read();
        for(int i=1;i<=n;i++){
            int a=read();
            if(!a)ans^=sg[k][lg2[i]][lg3[i]];
        }
        if(ans)puts("win");
        else puts("lose");
    }
	return 0;
}
