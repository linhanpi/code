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
const int N=1e6+5;
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
struct zdj{
    int t[26],f,len,cnt[2];
    #define t(p,i) pam[p].t[i]
    #define f(p) pam[p].f
    #define len(p) pam[p].len
    #define cnt(p,i) pam[p].cnt[i]
}pam[N];
char s[N];
int tot,last;
void insert(int k,int c,int chuan){
    // cout<<k<<" "<<c<<" "<<chuan<<endl;
    int p=last;
    for(;s[k-len(p)-1]!=c+'A';p=f(p));
    // cout<<k<<" "<<c<<" "<<chuan<<endl;
    if(!t(p,c)){
        int np=last=++tot,v=f(p);
        for(;s[k-len(v)-1]!=c+'A';v=f(v));
        if(!t(v,c))f(np)=2;
        else f(np)=t(v,c);
        t(p,c)=np;
        len(np)=len(p)+2;
        cnt(np,chuan)++;
    }
    else last=t(p,c),cnt(t(p,c),chuan)++;
    return ;
}
int ans=0;
void ycl(){
    tot=last=2;
    len(1)=-1,f(1)=f(2)=1;
    return ;
}
vector <int> v[N];
void dfs(int now){
    for(int y:v[now]){
        dfs(y);
        cnt(now,0)+=cnt(y,0);
        cnt(now,1)+=cnt(y,1);
    }
    if(now!=1&&now!=2)ans+=cnt(now,0)*cnt(now,1);
    return ;
}
signed main(){
    ycl();
	scanf("%s",s+1);
    s[0]='~';
    int n=strlen(s+1);
    // cout<<n<<endl;
    for(int i=1;i<=n;i++)insert(i,s[i]-'A',0);
    // cout<<n<<endl;
    last=2;
    scanf("%s",s+1);
    s[0]='~';
    n=strlen(s+1);
    for(int i=1;i<=n;i++)insert(i,s[i]-'A',1);
    for(int i=2;i<=tot;i++){
        v[f(i)].push_back(i);
    }
    dfs(1);
    cout<<ans<<endl;
	return 0;
}
