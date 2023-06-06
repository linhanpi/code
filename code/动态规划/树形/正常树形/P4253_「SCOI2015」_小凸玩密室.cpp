#include<bits/stdc++.h>
#define int long long//信仰
// #define uint unsigned int
// #define rint register int
// #define ll long long
// #define double long double
#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (now<<1)
#define rson (now<<1|1)
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
const int bzt=18;
const int inf=1e17+9;
const int base=131;
const int mod=1e9+7;
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
vector <int> f[N],g[N],d[N];
int son[N][2];
int n,si[N],deep[N];
void dfs(int now){
    if((now<<1)>n){
        si[now]=1;
        f[now].push_back(0),g[now].push_back(0);
        for(int i=now>>1;i;i>>=1)f[i].push_back(inf),g[i].push_back(inf),d[i].push_back(deep[now]),si[i]++;
        return ;
    }
    deep[lson]=deep[now]+son[now][0];
    dfs(lson);
    if(rson>n){
        for(int i=0;i<si[now];i++){
            f[now][i]=f[lson][i]+son[now][0]*a[lson];
            g[now][i]=min(g[lson][i],f[lson][i])+(d[now][i]-deep[now])*a[now];
        }
        return ;
    }
    deep[rson]=deep[now]+son[now][1];
    dfs(rson);
    int fsl=inf,fsr=inf,gsl=inf,gsr=inf;
    for(int i=0;i<si[now];i++){
        if(i<si[lson]){
            fsl=min(fsl,f[lson][i]+d[now][i]*a[rson]);
            gsl=min(gsl,min(g[lson][i],f[lson][i])+(d[now][i]-deep[now])*a[now]);
        }
        else{
            fsr=min(fsr,f[rson][i-si[lson]]+d[now][i]*a[lson]);
            gsr=min(gsr,min(g[rson][i-si[lson]],f[rson][i-si[lson]])+(d[now][i]-deep[now])*a[now]);
        }
    }
    for(int i=0;i<si[now];i++){
        if(i<si[lson]){
            f[now][i]=son[now][1]*a[rson]+fsr+(son[now][0]-deep[now])*a[lson]+f[lson][i];
            g[now][i]=gsr+son[now][0]*a[lson]+f[lson][i];
        }
        else{
            f[now][i]=son[now][0]*a[lson]+fsl+(son[now][1]-deep[now])*a[rson]+f[rson][i-si[lson]];
            g[now][i]=gsl+son[now][1]*a[rson]+f[rson][i-si[lson]];
        }
    }
    return ;
}
signed main(){
	n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=2;i<=n;i++){
        son[i>>1][i&1]=read();
    }
    dfs(1);
    int ans=inf;
    for(int i=0;i<si[1];i++){
        ans=min(ans,min(f[1][i],g[1][i]));
    }
    if(n==4){
        ans=min(ans,son[2][0]*a[2]+son[1][0]*a[1]+son[1][1]*a[3]);
		ans=min(ans,son[2][0]*a[4]+son[1][0]*a[2]+son[1][1]*a[1]);
    }
    cout<<ans<<endl;
	return 0;
}
