#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned long long
// #define uint unsigned int
// #define rint register int
// #define ll long long
// #define double long double
#define pii pair <int,int>
#define lowbit(x)(-x&x)
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define read()(red<int>())
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
// mt19937 rnd(time(0));
// #define ran_int(l,r)uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r)uniform_real_distribution<ld>(l,r)(rnd)
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
int num[19260817],p[25],n, ans;
inline void huan(int i,int j,int k){
    int len=1<<k,si=(i-1)*len,sj=(j-1)*len;
    for(int l=1;l<=len;l++){
        swap(num[si+l],num[sj+l]);
    }
    return ;
}
inline int check(int x){
    int len=1<<x;
    for(int i=1;i<=(1<<n-x);i+=2){
        if(num[i*len]+1!=num[i*len+1]){
            return 0;
        }
    }
    return 1;
}
inline void dfs(int x,int cnt){
    if(x&&!check(x-1))return;
    if(x==n){
        ans+=p[cnt];
        return;
    } 
    dfs(x+1,cnt);
    int ch[5],tot=0,len=1<<x;
    for(int i=1;i<=(1<<n-x);i+=2){
        if(num[i*len]+1!=num[i*len+1]){
            if(tot==4){
                return;
            }
            ch[++tot]=i;
            ch[++tot]=i+1;
        }
    }
    if(!tot)return;
    for(int i=1;i<=tot;i++){
        for(int j=i+1;j<=tot;j++){
            huan(ch[i],ch[j],x);
            dfs(x+1,cnt+1);
            huan(ch[i],ch[j],x);
        }
    }
}
signed main(){
    n=read();
    p[1]=1;
    for(int i=2;i<=12;i++){
        p[i]=p[i-1]*i;
    }
    for(int i=1;i<=(1<<n);i++){
        num[i]=read();
    }
    dfs(0,0);
    printf("%d\n",ans);
    return 0;
}
