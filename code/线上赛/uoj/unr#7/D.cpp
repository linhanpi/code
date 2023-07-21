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
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
int n,m;
int a[N],b[N],c[N];
priority_queue<pii,vector<pii>,greater<pii>>q;
int xia[N][20],st[N][20],bz[N][20],lg[N];
int chast(int l,int r){
	int len=lg[r-l+1];
	return a[st[l][len]]>=a[st[r-(1<<len)+1][len]]?a[st[l][len]]:a[st[r-(1<<len)+1][len]];
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
    for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	if(n<=2000){
		while(m--){
			while(q.size())q.pop();
			int l=read(),r=read(),k=read();
			int ans=0;
            for(int i=l;i<=l+k-1;i++){
				q.push({b[i],c[i]});
				ans+=c[i];
			}
            for(int i=l+k;i<=r;i++){
				pii tmp=q.top();
				if(a[i]>=tmp.first){
					q.pop();
					ans-=tmp.second;
					ans+=c[i];
					q.push({b[i],c[i]});
				}
			}
            cout<<ans<<endl;
		}
		return 0;
	}
    for(int i=1;i<=n;i++){
		bz[i][0]=i+1;
		st[i][0]=i;
	}
    for(int j=1;j<=19;j++){
        for(int i=1;i<=n;i++){
			bz[i][j]=bz[bz[i][j-1]][j-1];
			st[i][j]=a[st[i][j-1]]>=a[st[bz[i][j-1]][j-1]]?st[i][j-1]:st[bz[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		int l=i+1,r=n;
		while(l<r){
			int mid=l+r>>1;
			if(chast(i+1,mid)>=b[i])r=mid;
			else l=mid+1;
		}
		if(chast(i+1,l)>=b[i])xia[i][0]=l;
		else xia[i][0]=n+1;
	}
    for(int j=1;j<=19;j++){
		for(int i=1;i<=n;i++){
			xia[i][j]=xia[xia[i][j-1]][j-1];
		} 
	}
	while(m--){
		int l=read(),r=read(),k=read();
		int i=l;
        for(int k=19;~k;k--){
			if(xia[i][k]<=r&&xia[i][k]){
				i=xia[i][k];
			}
		}
        cout<<c[i]<<endl;
	}
	return 0;
}
