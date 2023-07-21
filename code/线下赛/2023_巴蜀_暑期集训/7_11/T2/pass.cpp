#include<bits/stdc++.h>
#pragma GCC optimize(3)
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
const int N=20;
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
char s[N],ch[N],cnt;
int a[N];
bool vis[N];
void dfs(int now){
    bool flag=1;
    if(a[1]==a[now-1])flag=0;
    for(int i=1;i<=now-1;i++){
        if(ch[a[i]]!=ch[a[now-i]]){
            flag=0;
            break;
        }
    }
    if(flag){
        for(int i=1;i<=now;i++){
            vis[a[i]]=1;
        }
    }
    if(now==16)return;
    if(a[now-1]-1>0){
        a[now]=a[now-1]-1;
        dfs(now+1);
    }
    if(a[now-1]+1<=cnt){
        a[now]=a[now-1]+1;
        dfs(now+1);
    }
    return ;
}
signed main(){
    freopen("pass.in","r",stdin);
    freopen("pass.out","w",stdout);
    int n=read();
    scanf("%s",s+1);
    int q=read();
    while(q--){
        memset(vis,0,sizeof(vis));
        int l=read(),r=read();
        cnt=r-l+1;
        for(int i=1;i<=cnt;i++){
            ch[i]=s[l+i-1];
        }
        for(int i=1;i<=cnt;i++){
            a[1]=i;
            dfs(2);
        }
        bool flag=1;
        for(int i=1;i<=cnt;i++){
            if(!vis[i])flag=0;
        }
        cout<<flag;
    }
	return 0;
}
