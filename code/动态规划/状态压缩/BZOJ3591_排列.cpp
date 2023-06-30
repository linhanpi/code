#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned long long
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
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}
int num[N],pre[N],l[N],dp[N*20],lis[N],cnt,val[N],ins;
signed main(){
	int n=read(),m=read();
	for(int i=1;i<=m;i++){
		num[i]=read()-1,pre[num[i]]=i-1;
		if(num[i]<num[i-1]){
			puts("0");
			return 0;
		}
	}
	l[0]=1;
	for(int i=1;i<=n;i++){
		l[i]=l[i-1]*3;
	}
	dp[0]=1;
	int ans=0;
	for(int st=0;st<l[n];st++){
		if(dp[st]){
			int yj=0;cnt=ins=0;
			int tep=st;
			for(int j=0;j<n;j++){
				val[j]=tep%3;tep/=3;
				if(val[j])yj++;
				if(val[j]==1)lis[cnt++]=j;
			}
			if(yj==n){
				ans+=dp[st];
				continue;
			}
			for(int j=0;j<n;j++){
                if(val[j])continue;
                if(pre[j]&&!val[num[pre[j]]])continue;
                while(lis[ins]<j&&ins<cnt)ins++;
                if(ins==m)continue;
                int nxt=st+l[j];
                if(ins<cnt)nxt+=l[lis[ins]];
                dp[nxt]+=dp[st];
            }
		}
	}
	cout<<ans<<endl;
	return 0;
}
