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
    int t[2],f,cnt;
    #define t(p,c) acam[p].t[c]
    #define f(p) acam[p].f
    #define cnt(p) acam[p].cnt
}acam[N];
int tot;
void insert(string s){
    int p=0;
    for(int i=0;i<s.size();i++){
        int ne=s[i]-'0';
        if(!t(p,ne))t(p,ne)=++tot;
        p=t(p,ne);
    }
    cnt(p)++;
    return ;
}
void bd(){
    queue <int> q;
    for(int i=0;i<2;i++)if(t(0,i))f(t(0,i))=0,q.push(t(0,i));
    while(!q.empty()){
        int now=q.front();
        q.pop();
        cnt(now)+=cnt(f(now));
        for(int i=0;i<2;i++){
            if(t(now,i))f(t(now,i))=t(f(now),i),q.push(t(now,i));
            else t(now,i)=t(f(now),i);
        }
    }
    return ;
}
bool vis[N];
bool flag=0;
void dfs(int now){
	vis[now]=1;
	for(int i=0;i<2;i++){
		if(vis[t(now,i)]){puts("TAK");exit(0);}
		else if(cnt(t(now,i)))continue;
		else dfs(t(now,i));
	}
	vis[now]=0;
	return ;
}
signed main(){
	int n=read();
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		insert(s);
	}
	bd();
	dfs(0);
	puts("NIE");
	return 0;
}
