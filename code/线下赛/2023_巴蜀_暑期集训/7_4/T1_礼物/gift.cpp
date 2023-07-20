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
const int N=3e5+5;
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
int n,m,q;
int c[N];
vector <int> v[N];
int fa[N],si[N],tp[N],son[N],dfn[N],ys[N],deep[N];
int num;
inline bool cmp(const int &x,const int &y){
    return dfn[x]<dfn[y];
}
void dfs1(int now){
    si[now]=1;
    deep[now]=deep[fa[now]]+1;
    for(int y:v[now]){
        fa[y]=now;
        dfs1(y);
        si[now]+=si[y];
        if(si[y]>si[son[now]]){
            son[now]=y;
        }
    }
    return ;
}
void dfs2(int now,int top){
    dfn[now]=++num;
    ys[num]=now;
    tp[now]=top;
    if(!son[now])return ;
    dfs2(son[now],top);
    for(int y:v[now]){
        if(y==son[now]||y==fa[now])continue;
        dfs2(y,y);
    }
    return ;
}
struct node{
    bitset <2005> b;
    #define b(p) tree[p].b
}tree[N<<2];
inline void pu(int p){
    b(p)=b(lson)|b(rson);
    return ;
}
void bt(int p,int l,int r){
    if(l==r){
        b(p)[c[ys[l]]]=1;
        return ;
    }
    int mid=(l+r)>>1;
    bt(lson,l,mid);
    bt(rson,mid+1,r);
    pu(p);
    return ;
}
bitset <2005> ans;
void cha(int p,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        ans|=b(p);
        return ;
    }
    int mid=(l+r)>>1;
    if(ql<=mid)cha(lson,l,mid,ql,qr);
    if(mid<qr)cha(rson,mid+1,r,ql,qr);
    return ;
}
inline int lca(int a,int b){
    while(tp[a]!=tp[b]){
        if(deep[tp[a]]<deep[tp[b]])swap(a,b);
        a=fa[tp[a]];
    }
    if(deep[a]>deep[b])swap(a,b);
    return a;
}
bitset <2005> an[10];
inline void chab(int a,int lc){
    ans.reset();
    if(dfn[a]<dfn[lc])return ;
    while(tp[a]!=tp[lc]){
        cha(1,1,n,dfn[tp[a]],dfn[a]);
        a=fa[tp[a]];
    }
    cha(1,1,n,dfn[lc],dfn[a]);
    return ;
}
int d[N];
signed main(){
    freopen("gift.in","r",stdin);
    freopen("gift.out","w",stdout);
	n=read(),m=read(),q=read();
    for(int i=2;i<=n;i++){
        v[read()].push_back(i);
    }
    for(int i=1;i<=n;i++){
        c[i]=read();
    }
    dfs1(1);
    dfs2(1,1);
    bt(1,1,n);
    while(q--){
        int k=read();
        for(int i=1;i<=k;i++)d[i]=read();
        // for(int i=1;i<=k;i++){
        //     an[i].reset();
        // }
        int lc=lca(d[1],d[2]);
		for(int i=3;i<=k;++i){
            lc=lca(lc,d[i]);
        }
        for(int i=1;i<=k;i++){
            chab(d[i],lc);
            an[i]=ans;
        }
        bool flag=0;
        int re=inf;
        for(int st=1;st<(1<<k);st++){
            bitset <2005> res;
            // res.reset();
            int tep=st,tot=0,cn=0;
            while(tep){
                if(tep&1){
                    res|=an[tot+1];
                    cn++;
                }
                tep>>=1;
                tot++;
            }
            if(res.count()<cn){
                flag=1;
                break;
            }
            re=min(re,(int)res.count()/cn);
        }
        if(flag){
            puts("0");
            continue;
        }
        write(re*k);
        puts("");
    }
	return 0;
}
/*
5 3 4
1 2 2 1 
2 3 1 3 1 
2 3 4 
3 5 2 2 
4 3 4 2 5 
2 2 2 
*/
/*
5 3 4
1 2 2 1 
2 3 1 3 1 
2 3 4 

*/