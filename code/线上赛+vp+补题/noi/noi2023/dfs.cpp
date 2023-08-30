#include<bits/stdc++.h>
#define int long long//信仰
#define ll long long
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
const int N=3e2+5;
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
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
vector <int> v[N];
struct nod{
    int dao,id;
};
vector <nod> tu[N];
struct node{
    int a,b,js,id;
}bian[N];
bool operator <(const node &x,const node &y){
    return x.js<y.js;
}
int ins[N];
int noww;
bool vis[N],ke[N][N];
void dfs(int now){
    // cout<<"now "<<now<<endl;
    for(nod it:tu[now]){
        int y=it.dao;
        if(vis[y]&&ins[y]){
            // cout<<noww<<" "<<it.id<<" "<<bian[it.id].a<<" "<<bian[it.id].b<<endl;
            ke[it.id][noww]=1;
        }
    }
    ins[now]=1;
    vis[now]=1;
    for(int y:v[now]){
        if(ins[y])continue;
        dfs(y);
    }
    ins[now]=0;
    return ;
}
int s[N];
int res[N];
int n,m,k;
inline bool in(int i,int j){
    for(int k=1;k<=n;k++){
        if(ke[i][k]&&(!ke[j][k]))return 0;
    }
    return 1;
}
inline bool xd(int i,int j){
    for(int k=1;k<=n;k++){
        if(ke[i][k]^ke[j][k])return 0;
    }
    return 1;
}
inline bool jc(int i,int j){
    int res=0;
    for(int k=1;k<=n;k++){
        res+=(ke[i][k]&&ke[j][k]);
    }
    return res;
}
signed main(){
    // freopen("dfs.in","r",stdin);
    // freopen("dfs.out","w",stdout);
    int c=read();
    n=read(),m=read(),k=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i=1;i<=m;i++){
        int a=read(),b=read();
        bian[i].a=a,bian[i].b=b;
        bian[i].id=i;
        tu[a].push_back({b,i}),tu[b].push_back({a,i});
    }
    for(int i=1;i<=k;i++){
        memset(vis,0,sizeof(vis));
        s[i]=read();
        noww=s[i];
        dfs(s[i]);
    }
    int ans=0;
    for(int st=1;st<(1<<k);st++){
        memset(vis,0,sizeof(vis));
        int tep=st;
        int cnt=0,tot=0;
        int cntt=0;
        while(tep){
            ++cnt;
            if(tep&1){
                ++cntt;
                for(int i=1;i<=n;i++){
                    if(!ke[i][s[cnt]]){
                        vis[i]=1;
                    }
                }
            }
            tep>>=1;
        }
        for(int i=1;i<=n;i++){
            if(!vis[i])++tot;
        }
        ans=(ans+((cntt&1)?(qmi(2,tot,mod)+mod-1):(mod+1-qmi(2,tot,mod))))%mod;
    }
    cout<<ans+1<<endl;
	return 0;
}
