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
    signed dao,quan;
};
vector <node> v[N];
bool in[N];
int dist[N];
void spfa(int s){
    queue <int> q;
    memset(dist,0x3f,sizeof(dist));
    q.push(s);
    dist[s]=0;
    in[s]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        in[now]=0;
        for(node t:v[now]){
            int y=t.dao;
            if(dist[y]>dist[now]+t.quan){
                dist[y]=dist[now]+t.quan;
                if(!in[y])q.push(y),in[y]=1;
            }
        }
    }
    return ;
}
signed main(){
	int n=read(),l=read(),r=read();
    int x=read();
    for(int i=2;i<=n;i++){
        int a=read();
        for(int j=0;j<x;j++){
            if((j+a)%x!=j)v[j].push_back({(signed)((j+a)%x),(signed)a});
        }
    }
    spfa(0);
    int ans=0;
    for(int i=0;i<x;i++){
        if(r>=dist[i])ans+=((r-dist[i])/x+1);
        if(l-1>=dist[i])ans-=((l-dist[i]-1)/x+1);
    }
    cout<<ans<<endl;
	return 0;
}