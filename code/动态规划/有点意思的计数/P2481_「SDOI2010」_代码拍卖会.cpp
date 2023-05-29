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
const int N=5e2+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=999911659;
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
int ni[10];
inline void ycl(){
    ni[0]=ni[1]=1;
    for(int i=2;i<=8;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    return;
}
inline int C(int x,int y){
    int res=1;
    for(int i=x-y+1;i<=x;i++)res=res*i%mod;
    for(int i=1;i<=y;i++)res=res*ni[i]%mod;
    return res;
}
int vis[N],g[N],f[N][10][N];
signed main(){
    ycl();
	int n=read(),p=read();
    memset(vis,-1,sizeof(vis));
    vis[0]=0;
    int pos=0,now=0;
    for(int i=1;i<=n;i++){
        now=(now*10+1)%p;
        if(vis[now]==-1){
            vis[now]=i,g[now]++;
        }
        else{
            pos=i;
            break;
        }
    }
    // cout<<pos<<endl;
    int ding=now;
    if(pos){
        int len=pos-vis[now],res=n-(pos-1),cnt=res/len,maxn=res%len;
        for(int i=pos;i<=pos+len-1;i++){
            if((i-pos+1)%len==maxn)ding=now;
            g[now]=(g[now]+cnt+(i-pos+1<=maxn))%mod;
            now=(now*10+1)%p;
        }
    }
    f[0][0][0]=1;
    for(int i=0;i<p;i++){
        for(int j=0;j<=8;j++){
            for(int k=0;k<p;k++){
                for(int l=0;l<=8-j;l++){
                    f[i+1][j+l][(k+l*i)%p]=(f[i+1][j+l][(k+l*i)%p]+f[i][j][k]*C(g[i]+l-1,l)%mod)%mod;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=8;i++){
        ans=(ans+f[p][i][p==1?0:p-ding])%mod;
    }
    cout<<ans<<endl;
	return 0;
}
