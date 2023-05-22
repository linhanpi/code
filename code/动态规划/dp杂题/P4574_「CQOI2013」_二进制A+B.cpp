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
const int N=35;
const int M=1e2+5;
const int bzt=18;
const int inf=1e17+9;
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
int dp[N][N][N][N][2];
int re=0;
inline int fen(int x){
    int cnt=0;
    int res=0;
    while(x){
        if(x&1)cnt++;
        x>>=1;
        res++;
    }
    re=max(res,re);
    return cnt;
}
signed main(){
	int a=read(),b=read(),c=read();
    int ca=fen(a),cb=fen(b),cc=fen(c);
    // cout<<ca<<" "<<cb<<" "<<cc<<endl;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0][0][0][0]=0;
    for(int i=0;i<=30;i++){
        for(int ai=0;ai<=ca;ai++){
            for(int bi=0;bi<=cb;bi++){
                for(int ci=0;ci<=cc;ci++){
                    for(int jin=0;jin<=1;jin++){
                        if(dp[i][ai][bi][ci][jin]==0x3f3f3f3f3f3f3f3f)continue;
                        dp[i+1][ai][bi][ci+(jin==1)][0]=min(dp[i][ai][bi][ci][jin]+(jin==1)*(1<<i),dp[i+1][ai][bi][ci+(jin==1)][0]);
                        dp[i+1][ai+1][bi][ci+((jin==1)^1)][(jin==1)]=min(dp[i][ai][bi][ci][jin]+((jin==1)^1)*(1<<i),dp[i+1][ai+1][bi][ci+((jin==1)^1)][(jin==1)]);
                        dp[i+1][ai][bi+1][ci+((jin==1)^1)][(jin==1)]=min(dp[i][ai][bi][ci][jin]+((jin==1)^1)*(1<<i),dp[i+1][ai][bi+1][ci+((jin==1)^1)][(jin==1)]);
                        dp[i+1][ai+1][bi+1][ci+(jin==1)][1]=min(dp[i][ai][bi][ci][jin]+(jin==1)*(1<<i),dp[i+1][ai+1][bi+1][ci+(jin==1)][1]);
                    }
                }
            }
        }
    }
    if(dp[re][ca][cb][cc][0]==0x3f3f3f3f3f3f3f3f)puts("-1");
    else cout<<dp[re][ca][cb][cc][0]<<endl;
	return 0;
}
