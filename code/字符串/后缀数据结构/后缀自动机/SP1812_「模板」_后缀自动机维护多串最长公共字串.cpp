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
	int t[26],f,len;
	#define t(p,c) sam[p].t[c]
	#define f(p) sam[p].f
	#define len(p) sam[p].len
}sam[N];
int last,tot;
void insert(int c){
	int p=last,np=++tot;last=np;
	len(np)=len(p)+1;
	for(;p&&!t(p,c);p=f(p))t(p,c)=np;
	if(!p)f(np)=1;
	else{
		int v=t(p,c);
		if(len(v)==len(p)+1)f(np)=v;
		else{
			int nv=++tot;
			sam[nv]=sam[v];
			len(nv)=len(p)+1;
			for(;p&&t(p,c)==v;p=f(p))t(p,c)=nv;
			f(np)=f(v)=nv;
		}
	}
}
string s1,s;
int minlen[N];
void cha(string t){
	int p=1,plen=0;
	for(int i=0;i<t.size();i++){
		int c=t[i]-'a';
		if(!t(p,c)){
			for(;p!=1&&!t(p,c);p=f(p));
			plen=len(p);
		}
		if(t(p,c)){
			p=t(p,c);
			plen++;
		}
		minlen[i]=min(minlen[i],plen);
	}
	return ;
}
signed main(){
	int T=read();
	while(T--){
		int n=read()-1;
		memset(minlen,0x3f,sizeof(minlen));
		cin>>s1;
		while(n--){
			cin>>s;
			last=tot=1;
			for(int i=0;i<s.size();i++)insert(s[i]-'a');
			cha(s1);
			for(int i=1;i<=tot;i++){
				memset(sam[i].t,0,sizeof(sam[i].t));
				len(i)=f(i)=0;
			}
		}
		int ans=0;
		for(int i=0;i<s1.size();i++){
			ans=max(ans,minlen[i]);
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
