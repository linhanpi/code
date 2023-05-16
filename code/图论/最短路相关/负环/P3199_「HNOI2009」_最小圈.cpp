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
const int N=3e3+5;
const int M=1e2+5;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const double eps=1e-10;
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
    int dao;double quan;
};
vector <node> v[N];
bool vis[N];
double dist[N];
bool flag;
void ck(int now,double mid){
    vis[now]=1;
    for(node t:v[now]){
        int y=t.dao;
        if(dist[y]>dist[now]+t.quan-mid){
            if(vis[y]||flag){
                flag=1;
                break;
            }
            dist[y]=dist[now]+t.quan-mid;
            ck(y,mid);
        }
    }
    vis[now]=0;
    return ;
}
signed main(){
	int n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a=read(),b=read();
        double w;
        cin>>w;
        v[a].push_back({b,w});
    }
    double l=-1e6,r=1e6;
    while(r-l>eps){
        double mid=(l+r)/2;
        memset(dist,0,sizeof(dist));
        memset(vis,0,sizeof(vis));
        flag=0;
        for(int i=1;i<=n;i++){
            ck(i,mid);
            if(flag)break;
        }
        if(flag)r=mid;
        else l=mid;
    }
    cout<<fixed<<setprecision(8)<<l<<endl;
	return 0;
}
