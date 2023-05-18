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
const int N=2e6+5;
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
    int t[26],f,cnt;
    #define t(p,i) acam[p].t[i]
    #define f(p) acam[p].f
    #define cnt(p) acam[p].cnt
}acam[N];
int tot;
void insert(char* s){
    int p=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        int ne=s[i]-'a';
        if(!t(p,ne))t(p,ne)=++tot;
        p=t(p,ne);
    }
    cnt(p)|=(1<<(len-1));
    return ;
}
void bd(){
    queue <int> q;
    for(int i=0;i<26;i++)if(t(0,i))q.push(t(0,i));
    while(!q.empty()){
        int now=q.front();
        q.pop();
        cnt(now)|=cnt(f(now));
        for(int i=0;i<26;i++){
            if(t(now,i))f(t(now,i))=t(f(now),i),q.push(t(now,i));
            else t(now,i)=t(f(now),i);
        }
    }
    return ;
}
int cha(char* t){
    int p=0;
    int len=strlen(t);
    int neng=1,ans=0;
    for(int i=0;i<len;i++){
        p=t(p,t[i]-'a');
        if(neng&cnt(p))neng<<=1,neng+=1,ans=i+1;
        else neng<<=1;
    }
    return ans;
}
char s[N];
signed main(){
	int n=read(),m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        insert(s);
    }
    bd();
    while(m--){
        scanf("%s",s);
        cout<<cha(s)<<endl;
    }
	return 0;
}
