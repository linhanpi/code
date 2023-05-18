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
const int N=1e5+5;
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
    int son[26],cnt;
    #define son(p,i) trie[p].son[i]
    #define cnt(p) trie[p].cnt
}trie[N*15];
int tot;
int root[N];
string s;
int insert(int now,int k){
    int p=++tot;
    trie[p]=trie[now];
    cnt(p)++;
    if(k==s.size())return p;
    son(p,s[k]-'a')=insert(son(p,s[k]-'a'),k+1);
    return p;
}
string t;
int cha(int q,int p,int lca,int k){
    if(k==t.size())return cnt(q)+cnt(p)-2*cnt(lca);
    int ch=t[k]-'a';
    return cha(son(q,ch),son(p,ch),son(lca,ch),k+1);
}
struct nod{
    int dao;string s;
};
vector <nod> v[N];
int fa[N],son[N],tp[N],si[N],dep[N];
void dfs1(int now){
	int maxn=0;
	si[now]=1;
	dep[now]=dep[fa[now]]+1;
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i].dao;
		if(y==fa[now])continue;
        s=v[now][i].s;
        root[y]=insert(root[now],0);
		fa[y]=now;
		dfs1(y);
		si[now]+=si[y];
		if(si[y]>maxn){
			maxn=si[y];
			son[now]=y;
		}
	}
	return ;
}
void dfs2(int now,int top){
	tp[now]=top;
	if(!son[now])return ;
	dfs2(son[now],top);
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i].dao;
		if(y==fa[now]||y==son[now])continue;
		dfs2(y,y);
	}
	return ;
}
inline int cha(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])swap(x,y);
		x=fa[tp[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	return y;
}
signed main(){
	int n=read();
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        string s;cin>>s;
        v[a].push_back({b,s});
        v[b].push_back({a,s});
    }
    dfs1(1);
    dfs2(1,1);
    int q=read();
    while(q--){
        int a=read(),b=read();cin>>t;
        int lca=cha(a,b);
        cout<<cha(root[a],root[b],root[lca],0)<<endl;
    }
	return 0;
}
