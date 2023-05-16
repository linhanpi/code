#include<bits/stdc++.h>
// #define int long long//信仰
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
const int M=1e5+5;
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
    int son[2],js,cnt,lazy;
    #define son(p,i) trie[p].son[i]
    #define js(p) trie[p].js
    #define cnt(p) trie[p].cnt
    #define lazy(p) trie[p].lazy
    #define ls(p) trie[p].son[0]
    #define rs(p) trie[p].son[1]
}trie[N*32];
int tot;
void pd(int now){
    if(!ls(now))ls(now)=++tot;
    if(!rs(now))rs(now)=++tot;
    if(lazy(now)==0)return ;
    if(!js(ls(now))){
        cnt(ls(now))+=lazy(now);
        lazy(ls(now))+=lazy(now);
    }
    if(!js(rs(now))){
        cnt(rs(now))+=lazy(now);
        lazy(rs(now))+=lazy(now);
    }
    lazy(now)=0;
    return ;
}
inline void gai(string s,int k){
    int now=0;
    for(int i=0;i<s.size();i++){
        pd(now);
        now=son(now,s[i]-'0');
    }
    js(now)+=k,lazy(now)++,cnt(now)++;
    return ;
}
inline int cha(string s){
    int now=0;
    for(int i=0;i<s.size();i++){
        pd(now);
        now=son(now,s[i]-'0');
    }
    return cnt(now);
}
char op[10];
int opt[N];
string str[N];
vector <int> jia[N],jian[N];
string ip[N];
int ans[N];
signed main(){
	int n=read(),q=read();
    for(int i=1;i<=n;i++){
        scanf("%s",op+1);cin>>str[i];
        if(op[1]=='A')opt[i]=1;
        else opt[i]=-1;
    }
    for(int i=1;i<=q;i++){
        cin>>ip[i];
        int l=read(),r=read();
        jian[l].push_back(i),jia[r].push_back(i);
    }
    for(int i=1;i<=n;i++){
        gai(str[i],opt[i]);
        for(int y:jian[i])ans[y]-=cha(ip[y]);
        for(int y:jia[i])ans[y]+=cha(ip[y]);
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
	return 0;
}