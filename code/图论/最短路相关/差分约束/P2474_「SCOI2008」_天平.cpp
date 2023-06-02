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
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=1e3+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
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
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
int maxn[N][N],minn[N][N];
signed main(){
	int n=read(),A=read(),B=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char x;cin>>x;
			if(i==j||x=='=')maxn[i][j]=minn[i][j]=0;
			else if(x=='+')maxn[i][j]=2,minn[i][j]=1;
			else if(x=='-')maxn[i][j]=-1,minn[i][j]=-2;
			else if(x=='?')maxn[i][j]=2,minn[i][j]=-2;
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				maxn[i][j]=min(maxn[i][j],maxn[i][k]+maxn[k][j]);
				minn[i][j]=max(minn[i][j],minn[i][k]+minn[k][j]);
			}
		}
	}
	int lcnt=0,ecnt=0,rcnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(i==A||i==B)break;
			if(j==A||j==B)continue;
			if(minn[A][i]>maxn[j][B]||minn[A][j]>maxn[i][B])lcnt++;
			if(minn[A][i]==maxn[A][i]&&minn[A][i]==minn[j][B]&&minn[j][B]==maxn[j][B])ecnt++;
			else if(minn[B][i]==maxn[B][i]&&minn[B][i]==minn[j][A]&&minn[j][A]==maxn[j][A])ecnt++;
			if(maxn[A][i]<minn[j][B]||maxn[A][j]<minn[i][B])rcnt++;
		}
	}
	cout<<lcnt<<" "<<ecnt<<" "<<rcnt<<endl;
	return 0;
}
