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
int sg[N],vis[N],a[N];
signed main(){
	sg[1]=0;
    for(int i=2;i<=21;i++){
        for(int j=1;j<=i;j++){
            for(int k=j;k<i;k++){
                vis[sg[j]^sg[k]]=i;
            }
        }
        for(sg[i]=0;vis[sg[i]]==i;sg[i]++);
    }
    int T=read();
    while(T--){
        int n=read();
        for(int i=n;i;i--){
            a[i]=read();
        }
        int ans=0;
        for(int i=n;i;i--){
            if(a[i]&1)ans^=sg[i];
        }
        if(!ans)puts("-1 -1 -1\n0");
        else{
            int res=0,flag=1;
            for(int i=n;i;i--){
                if(!a[i])continue;
                for(int j=i-1;j;j--){
                    if(!a[j])continue;
                    for(int k=j;k;k--){
                        if(!a[k])continue;
                        if(a[k]==1&&j==k)continue;
                        if((ans^sg[i]^sg[j]^sg[k])==0){
                            res++;
                            if(flag){
                                cout<<n-i<<" "<<n-j<<" "<<n-k<<endl;
                                flag=0;
                            }
                        }
                    }
                }
            }
            cout<<res<<endl;
        }
    }
	return 0;
}
