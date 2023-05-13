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
const int M=2e2+5;
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
int cnt[N],c[N][26],fail[N],res[N];
int tot;
string s[155],t;
void insert(int x){
	int len=s[x].size();
	int now=0;
	for(int i=0;i<len;i++){
		int ne=s[x][i]-'a';
		if(!c[now][ne])c[now][ne]=++tot;
		now=c[now][ne];
	}
	cnt[now]=x;
	return ;
}
void bd(){
	queue <int> q;
	for(int i=0;i<26;i++){
		if(c[0][i])fail[c[0][i]]=0,q.push(c[0][i]);
	}
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(c[now][i])fail[c[now][i]]=c[fail[now]][i],q.push(c[now][i]);
			else c[now][i]=c[fail[now]][i];
		}
	}
	return ;
}
int cha(string t){
	int len=t.size();
	int now=0,ans=0;
	for(int i=0;i<len;i++){
		now=c[now][t[i]-'a'];
		for(int p=now;p;p=fail[p])if(cnt[p]!=0)res[cnt[p]]++,ans=max(res[cnt[p]],ans);
	}
	return ans;
}
signed main(){
	while(1){
		int n=read();
		if(n==0)return 0;
		memset(c,0,sizeof(c));
		memset(fail,0,sizeof(fail));
		memset(res,0,sizeof(res));
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++){
			cin>>s[i];
			insert(i);
		}
		bd();
		cin>>t;
		int ans=cha(t);
		cout<<ans<<endl;
		for(int i=1;i<=n;i++){
			if(res[i]==ans)cout<<s[i]<<endl;
		}
	}
    return 0;
}