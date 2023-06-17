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
const int N=1e6+5;
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
int n;
int fa[N],s[N],p[N],q[N],l[N],d[N],dp[N];
int si[N],ts[N],td[N],st[N<<4];
vector <int> v[N];
#define x(i) (s[i])
#define k(i) (p[i])
#define y(i) (dp[i])
struct shandata{
    int now,yuan;
}op[N<<4];
inline int get(int x){
    return lower_bound(d+1,d+n+1,x)-d;
}
ld xie(int i,int j){
    return (ld)(y(j)-y(i))/(x(j)-x(i));
}
void push(int x,int p){
    int top=si[x]+ts[x];
    while(ts[x]>1&&xie(st[top-2],st[top-1])>xie(st[top-1],p)){
        op[si[x]+td[x]++]={p,st[top-1]},ts[x]--,top--;
    }
    st[top++]=p,ts[x]++;
    return ;
}
void shan(int id,int p){
    ts[id]--;int b=si[id]+td[id];
    while(td[id]&&op[b-1].now==p)st[si[id]+ts[id]++]=op[b-1].yuan,td[id]--,b--;
}
int ef(int x,ld k){
    if(!ts[x])return -1;
    int l=si[x],r=si[x]+ts[x]-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(xie(st[mid],st[mid+1])<=k)l=mid+1;
        else r=mid;
    }
    return st[l];
}
void dfs(int now){
    if(now>1)dp[now]=inf;
    for(int i=n-get(s[now]-l[now])+1;i;i-=lowbit(i)){
        int pos=ef(i,k(now));
        if(pos!=-1)dp[now]=min(dp[now],dp[pos]+(s[now]-s[pos])*p[now]+q[now]);
    }
    for(int i=n-get(s[now])+1;i<=n;i+=lowbit(i))push(i,now);
    for(int y:v[now])dfs(y);
    for(int i=n-get(s[now])+1;i<=n;i+=lowbit(i))shan(i,now);
    return ;
}
signed main(){
	n=read();int t=read();
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=lowbit(j))si[j+1]++;
    }
    for(int i=3;i<=n;i++)si[i]+=si[i-1];
    for(int i=2;i<=n;i++){
        fa[i]=read(),s[i]=read(),p[i]=read(),q[i]=read(),l[i]=read();
        d[i]=s[i]+=s[fa[i]];
        v[fa[i]].push_back(i);
    }
    sort(d+1,d+n+1);
    dfs(1);
    for(int i=2;i<=n;i++)cout<<dp[i]<<endl;
	return 0;
}