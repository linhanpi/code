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
const int N=3e5+5;
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
int n,q;
struct zdj{
    int t[26],f;
    #define t(p,c) acam[p].t[c]
    #define f(p) acam[p].f
}acam[N];
int tot;
vector <int> you[N];
void insert(string s,int x){
    int p=0;
    for(int i=0;i<s.size();i++){
        int ne=s[i]-'a';
        if(!t(p,ne))t(p,ne)=++tot;
        p=t(p,ne);
    }
    you[p].push_back(x);
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
    for(int i=1;i<=tot;i++)v[f(i)].push_back(i);
    return ;
}
int maxn[N*4];
void gai(int p,int l,int r,int ql,int qr,int k,auto &op){
    if(ql>qr)return ;
    if(ql<=l&&r<=qr){
        op.push_back({p,maxn[p]});
        maxn[p]=max(maxn[p],k);
        return ;
    }
    int mid=(l+r)>>1;
    if(ql<=mid)gai(lson,l,mid,ql,qr,k,op);
    if(mid<qr)gai(rson,mid+1,r,ql,qr,k,op);
    return ;
}
int cha(int pos){
    int l=1,r=q,p=1,ans=maxn[p];
    while(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid)r=mid,p=lson;
        else l=mid+1,p=rson;
        ans=max(ans,maxn[p]);
    }
    return ans;
}
vector <pii> xiu[N];
vector <int> Q[N];
int ans[N];
void dfs(int now){
    vector <pii> op;
    for(int y:you[now]){
        xiu[y].push_back({q+1,0});
        gai(1,1,q,1,xiu[y].front().first-1,0,op);
        for(int i=0;i<xiu[y].size()-1;i++){
            gai(1,1,q,xiu[y][i].first,xiu[y][i+1].first-1,xiu[y][i].second,op);
        }
    }
    for(int y:Q[now])ans[y]=max(ans[y],cha(y));
    for(int y:v[now])dfs(y);
    reverse(op.begin(),op.end());
    for(pii it:op)maxn[it.first]=it.second;
    return ;
}
signed main(){
	n=read(),q=read();
    memset(ans,0x8f,sizeof(ans));
    memset(maxn,-1,sizeof(maxn));
    for(int i=1;i<=n;i++){
        string s;cin>>s;
        insert(s,i);
    }
    bd();
    for(int i=1;i<=q;i++){
        int op=read();
        if(op==1){
            int id=read(),x=read();
            xiu[id].push_back({i,x});
        }
        else{
            string s;cin>>s;
            ans[i]=-1;
            int p=0;
            for(char it:s)p=t(p,it-'a'),Q[p].push_back(i);
        }
    }
    dfs(0);
    for(int i=1;i<=q;i++){
        if(ans[i]>=-1)cout<<ans[i]<<endl;
    }
	return 0;
}
