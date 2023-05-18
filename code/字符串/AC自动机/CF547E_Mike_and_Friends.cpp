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
const int N=5e5+5;
const int M=1e2+5;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+9;
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
struct zdj{
    int t[26],f;
    #define t(p,c) acam[p].t[c]
    #define f(p) acam[p].f
    #define cnt(p) acam[p].cnt
}acam[N];
int tot;
int ed[N];
vector <int> you[N];
void insert(string s,int x){
    int p=0;
    for(int i=0;i<s.size();i++){
        int ne=s[i]-'a';
        if(!t(p,ne))t(p,ne)=++tot;
        p=t(p,ne);
        you[x].push_back(p);
    }
    ed[x]=p;
    return ;
}
vector <int> v[N];
void bd(){
    queue <int> q;
    for(int i=0;i<26;i++)if(t(0,i))f(t(0,i))=0,q.push(t(0,i));
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(t(now,i))f(t(now,i))=t(f(now),i),q.push(t(now,i));
            else t(now,i)=t(f(now),i);
        }
    }
    for(int i=1;i<=tot;i++){
        v[f(i)].push_back(i);
    }
    return ;
}
int dfn[N],si[N],num;
void dfs(int now){
    dfn[now]=++num;
    si[now]=1;
    for(int y:v[now]){
        dfs(y);
        si[now]+=si[y];
    }
    return ;
}
int c[N];
inline void add1(int x,int y){
    for(int i=x;i<=tot+1;i+=lowbit(i)){
        c[i]+=y;
    }
    return ;
}
inline void add(int l,int r,int k){
    add1(l,k),add1(r+1,-k);
    return ;
}
inline int ask1(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res+=c[i];
    }
    return res;
}
inline int ask(int l,int r){
    return ask1(r)-ask1(l-1);
}
struct node{
    int i,op,id;
};
vector <node> Q[N];
string s[N];
int ans[N];
signed main(){
	int n=read(),q=read();
    for(int i=1;i<=n;i++){
        cin>>s[i];
        insert(s[i],i);
    }
    bd();
    dfs(0);
    for(int i=1;i<=q;i++){
        int l=read(),r=read(),x=read();
        Q[l-1].push_back({x,-1,i});
        Q[r].push_back({x,1,i});
    }
    for(int i=1;i<=n;i++){
        for(int y:you[i])add1(dfn[y],1);
        for(node y:Q[i]){
            ans[y.id]+=y.op*ask(dfn[ed[y.i]],dfn[ed[y.i]]+si[ed[y.i]]-1);
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
	return 0;
}
