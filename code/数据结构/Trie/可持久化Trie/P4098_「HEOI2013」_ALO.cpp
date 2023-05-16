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
const int N=3e6+5;
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
int a[N];
bool cmp(const int &x,const int &y){
    return a[x]<a[y];
}
struct node{
    int son[2],cnt;
    #define son(p,i) trie[p].son[i]
    #define cnt(p) trie[p].cnt
}trie[N];
int tot;
int root[N];
int insert(int now,int x,int k){
    int p=++tot;
    trie[p]=trie[now];
    cnt(p)++;
    if(k==-1)return p;
    son(p,((x>>k)&1))=insert(son(p,(x>>k)&1),x,k-1);
    return p;
}
int cha(int q,int p,int k,int x){
    if(k==-1)return 0;
    int ch=((x>>k)&1)^1;
    if(cnt(son(p,ch))-cnt(son(q,ch)))return cha(son(q,ch),son(p,ch),k-1,x)|(1<<k);
    else return cha(son(q,ch^1),son(p,ch^1),k-1,x);
}
int qian[N],hou[N],p[N];
signed main(){
	int n=read();
    for(int i=1;i<=n;i++)qian[i]=i-1,hou[i]=i+1,p[i]=i;
    for(int i=1;i<=n;i++){
        a[i]=read();
        root[i]=insert(root[i-1],a[i],30);
    }
    int ans=0;
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++){
        int l=qian[p[i]],r=hou[p[i]];
        hou[l]=r,qian[r]=l;
        if(l)ans=max(ans,cha(root[qian[l]],root[r-1],30,a[p[i]]));
        if(r!=n+1)ans=max(ans,cha(root[l],root[hou[r]-1],30,a[p[i]]));
    }
    cout<<ans<<endl;
	return 0;
}
