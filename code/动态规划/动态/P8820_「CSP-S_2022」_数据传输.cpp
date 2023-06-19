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
const int N=2e5+5;
const int M=1e2+5;
const int bzt=18;
const int inf=0x3f3f3f3f3f3f3f3f;
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
int val[N],num[N],deep[N];
vector <int> v[N];
struct juzheng{
    int a[3][3];
    int r,c;
    juzheng(){
        memset(a,0x3f,sizeof(a));
        r=c=0;
    }
}G[N],bzz[N][20],bzn[N][20],I;
juzheng operator *(const juzheng &x,const juzheng &y){
    juzheng c;
    c.r=x.r,c.c=y.c;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                c.a[i][j]=min(c.a[i][j],x.a[i][k]+y.a[k][j]);
            }
        }
    }
    return c;
}
int fa[N][20];
void dfs(int now,int fath){
    fa[now][0]=fath;
    bzz[now][0]=bzn[now][0]=G[now];
    deep[now]=deep[fath]+1;
    for(int j=1;j<=18;j++){
        fa[now][j]=fa[fa[now][j-1]][j-1];
        bzz[now][j]=bzz[now][j-1]*bzz[fa[now][j-1]][j-1];
        bzn[now][j]=bzn[fa[now][j-1]][j-1]*bzn[now][j-1];
    }
    for(int y:v[now]){
        if(y==fa[now][0])continue;
        dfs(y,now);
    }
    return ;
}
juzheng lca(int x,int y){
    juzheng sx=I,sy=I;
    if(deep[y]>deep[x])sy=G[y],y=fa[y][0];
    for(int i=18;~i;i--){
        if(deep[fa[x][i]]>=deep[y]){
            sx=sx*bzz[x][i],x=fa[x][i];
        }
    }
    if(x==y)return sx*G[x]*sy;
    for(int i=18;~i;i--){
        if(fa[x][i]!=fa[y][i]){
            sx=sx*bzz[x][i];
            sy=bzn[y][i]*sy;
            x=fa[x][i],y=fa[y][i];
        }
    }
    return sx*G[x]*G[fa[x][0]]*G[y]*sy;
}
int n,Q,k;
inline int cha(int x,int y){
    if(x==y)return val[x];
    if(deep[x]<deep[y])swap(x,y);
    juzheng res=lca(fa[x][0],y);
    juzheng re=I;
    re.a[0][0]=val[x];
    res=re*res;
    return res.a[0][0];
}
signed main(){
	n=read(),Q=read(),k=read();
    for(int i=0;i<=2;i++){
        for(int j=0;j<=2;j++){
            I.a[i][j]=((i==j)?0:inf);
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        num[i]=inf;
        for(int y:v[i])num[i]=min(num[i],val[y]);
    }
    for(int i=1;i<=n;i++){
        if(k==1){
            G[i].a[0][0]=val[i];
            G[i].a[1][1]=G[i].a[2][2]=0;
        }
        if(k==2){
            G[i].a[0][0]=val[i];
            G[i].a[0][1]=G[i].a[2][2]=0;
            G[i].a[1][0]=val[i];
        }
        if(k==3){
            G[i].a[0][0]=val[i];
            G[i].a[0][1]=0;
            G[i].a[1][0]=val[i];
            G[i].a[1][1]=num[i];
            G[i].a[1][2]=0;
            G[i].a[2][0]=val[i];
        }
    }
    dfs(1,0);
    while(Q--){
        int x=read(),y=read();
        cout<<cha(x,y)<<endl;
    }
	return 0;
}
