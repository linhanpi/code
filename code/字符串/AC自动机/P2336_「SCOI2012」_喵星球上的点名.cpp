#include<bits/stdc++.h>
#define int long long//信仰
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
template<typename T>inline T red() {
	T x=0;
	bool f=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=true;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>inline void write(T x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=2e5+5;
const int M=1e2+5;
const int inf=INT_MAX;
const int base=131;
const int mod=1e4+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
	x%=mod;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
inline int fang(int x) {return x*x;}
struct node{
    int fa,fail;
    map <int,int> c;
    #define fa(p) trie[p].fa
    #define fail(p) trie[p].fail
    #define c(p,i) trie[p].c[i]
    #define count(p,i) trie[p].c.count(i)
}trie[N];
int now,tot;
void insert(int c){
    int &v=c(now,c);
    if(!v)v=++tot,fa(v)=now;
    now=v;
    return ;
}
int gf(int now,int c){
    if(count(now,c))return c(now,c);
    if(!now)return now;
    return c(now,c)=gf(fail(now),c);
}
vector <int> v[N];
int fa[N];
void bd(){
    queue <int> q;
    for(auto it:trie[0].c)q.push(it.second);
    while(!q.empty()){
        int now=q.front();q.pop();
        for(auto it:trie[now].c){
            fail(it.second)=gf(fail(now),it.first);
            q.push(it.second);
        }
    }
    for(int i=1;i<=tot;i++){
        fa[i]=fail(i);
        v[fail(i)].push_back(i);
    }
    return ;
}
int c[N];
inline void gai1(int x,int y){
    for(int i=x;i<=tot+1;i+=lowbit(i)){
        c[i]+=y;
    }
    return ;
}
inline void gai(int l,int r,int y){
    gai1(l,y),gai1(r+1,-y);
    return ;
}
inline int cha1(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res+=c[i];
    }
    return res;
}
inline int cha(int l,int r){
    return cha1(r)-cha1(l-1);
}
vector <int> np[N],qp[N],nlca[N],qlca[N];
int ne[N],qe[N];
int son[N],si[N],deep[N],top[N],dfn[N],num;
bool cmp(const int &x,const int &y){
    return dfn[x]<dfn[y];
}
void dfs1(int now){
    int maxn=0;
    si[now]=1;
    for(int y:v[now]){
        if(y==fa[now])continue;
        deep[y]=deep[now]+1;
        dfs1(y);
        si[now]+=si[y];
        if(si[y]>maxn){
            maxn=si[y];
            son[now]=y;
        }
    }
    return ;
}
void dfs2(int now,int tp){
    dfn[now]=++num;
    top[now]=tp;
    if(!son[now])return ;
    dfs2(son[now],tp);
    for(int y:v[now]){
        if(y==fa[now]||y==son[now])continue;
        dfs2(y,y);
    }
    return ;
}
inline int lca(int x,int y){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    if(deep[x]<deep[y])swap(x,y);
    return y;
}
signed main(){
	int n=read(),m=read();
    for(int i=1;i<=n;i++){
        int l=read();
        now=0;
        for(int j=1;j<=l;j++){
            insert(read());
            np[i].push_back(now);
        }
        insert(-1);
        np[i].push_back(now);
        l=read();
        for(int j=1;j<=l;j++){
            insert(read());
            np[i].push_back(now);
        }
        ne[i]=now;
    }
    for(int i=1;i<=m;i++){
        int l=read();
        now=0;
        for(int j=1;j<=l;j++){
            insert(read());
            qp[i].push_back(now);
        }
        qe[i]=now;
    }
    bd();
    deep[0]=1;
    dfs1(0);
    dfs2(0,0);
    for(int i=1;i<=n;i++){
        sort(np[i].begin(),np[i].end(),cmp);
        for(int j=0;j<np[i].size()-1;j++){
            nlca[i].push_back(lca(np[i][j],np[i][j+1]));
        }
    }
    for(int i=1;i<=m;i++){
        sort(qp[i].begin(),qp[i].end(),cmp);
        for(int j=0;j<qp[i].size()-1;j++){
            qlca[i].push_back(lca(qp[i][j],qp[i][j+1]));
        }
    }
    for(int i=1;i<=n;i++){
        for(int y:np[i]){
            gai1(dfn[y],1);
        }
        for(int y:nlca[i])gai1(dfn[y],-1);
    }
    for(int i=1;i<=m;i++){
        cout<<cha(dfn[qe[i]],dfn[qe[i]]+si[qe[i]]-1)<<endl;
    }
    memset(c,0,sizeof(c));
    for(int i=1;i<=m;i++){
        gai(dfn[qe[i]],dfn[qe[i]]+si[qe[i]]-1,1);
    }
    for(int i=1;i<=n;i++){
        int res=0;
        for(int y:np[i]){
            res+=cha1(dfn[y]);
        }
        for(int y:nlca[i])res-=cha1(dfn[y]);
        cout<<res<<" ";
    }
    cout<<endl;
	return 0;
}
