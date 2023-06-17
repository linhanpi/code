#include<cstdio>
#include<algorithm>
#include<ctime>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
const int N=1.1e6+10,mod=998244353,inv3=(mod+1)/3;
inline int Mod(int a){return a<mod?a:a-mod;}
ll fastpow(ll a,int b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) s=s*a%mod;
	return s;
}
void dft(int*a,int lim)
{
	ll x,y,w,wn;
	for(int i=lim>>1;i;i>>=1)
	{
		wn=fastpow(3,(mod-1)/i/2);
		for(int j=0;j<lim;j+=(i<<1))
		{
			w=1;
			for(int k=0;k<i;k++,w=w*wn%mod)
			{
				x=a[j+k],y=a[i+j+k];
				a[j+k]=Mod(x+y);
				a[i+j+k]=(x-y+mod)*w%mod;
			}
		}
	}
}
void idft(int*a,int lim)
{
	ll x,y,w,wn;
	for(int i=1;i<lim;i<<=1)
	{
		wn=fastpow(inv3,(mod-1)/i/2);
		for(int j=0;j<lim;j+=(i<<1))
		{
			w=1;
			for(int k=0;k<i;k++,w=w*wn%mod)
			{
				x=a[j+k],y=a[i+j+k]*w%mod;
				a[j+k]=Mod(x+y);
				a[i+j+k]=Mod(x-y+mod);
			}
		}
	}
	x=fastpow(lim,mod-2);
	for(int i=0;i<lim;i++) a[i]=a[i]*x%mod;
}
ll fac[N],ifac[N],f[N],s[N];
int h[N],g[N],n,m,A,B,C,D;
void solve(int l,int r)
{
	if(l==r)
	{
		if(l==1) f[1]=D;
		else f[l]=(s[l-1]*A+(B+1ll*(l-1)*C%mod)*f[l-1])%mod;
		return;
	}
	solve(l,mid);
	int lim=1;
	if(l==1)
	{
		while(lim<=2*mid) lim<<=1;
		for(int i=0;i<lim;i++) h[i]=0;
		for(int i=l;i<=mid;i++) h[i]=f[i]*ifac[i]%mod;
		dft(h,lim);
		for(int i=0;i<lim;i++) h[i]=1ll*h[i]*h[i]%mod;
		idft(h,lim);
		for(int i=l;i<r;i++) s[i]=(s[i]+h[i]*fac[i])%mod;
	}
	else
	{
		while(lim<=r-l+1) lim<<=1;
		for(int i=0;i<lim;i++) h[i]=g[i]=0;
		for(int i=l;i<=mid;i++) h[i-l]=f[i]*ifac[i]%mod;
		for(int i=l+1;i<=r;i++) g[i-l]=f[i-l]*ifac[i-l]%mod;
		dft(h,lim),dft(g,lim);
		for(int i=0;i<lim;i++) g[i]=1ll*g[i]*h[i]%mod;
		idft(g,lim);
		for(int i=l;i<r;i++) s[i]=(s[i]+g[i-l]*fac[i]*2)%mod;
	}
	solve(mid+1,r);
}
namespace poly{
	ll inv3=(mod+1)/3,inv;
	ll a[N],b[N],c[N],d[N],e[N],g[N],h[N];
	int r[N],n,m;
	void ntt(ll*a,int lim,int type)
	{
		ll w,wn,x,y;
		for(int i=1;i<lim;i++)
			if(i<r[i]) swap(a[i],a[r[i]]);
		for(int i=1;i<lim;i*=2)
		{
			wn=fastpow(type?3:inv3,(mod-1)/i/2);
			for(int j=0;j<lim;j+=(i*2))
			{
				w=1;
				for(int k=0;k<i;k++,w=w*wn%mod)
				{
					x=a[j+k];
					y=a[j+k+i]*w%mod;
					a[j+k]=(x+y)%mod;
					a[j+k+i]=(x-y+mod)%mod;
				}
			}
		}
		if(type) return;
		inv=fastpow(lim,mod-2);
		for(int i=0;i<lim;i++)
			a[i]=a[i]*inv%mod;
	}
	void init(int &n)
	{
		int l=0,lim=1;
		while(lim<n) lim<<=1,l++;
		for(int i=0;i<lim;i++)
			r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		n=lim;
	}
	int len;
	void getinv(ll*a,int n)
	{
		b[0]=fastpow(a[0],mod-2);
		for(int i=2;i<=n*2;i<<=1)
		{
			len=i<<1;
			init(len);
			ntt(b,len,1);
			for(int j=0;j<i;j++) c[j]=a[j];
			ntt(c,len,1);
			for(int j=0;j<len;j++) b[j]=b[j]*(2-c[j]*b[j]%mod+mod)%mod;
			ntt(b,len,0);
			for(int j=i;j<len;j++) b[j]=0;
		}
		for(int i=0;i<=n;i++) a[i]=b[i];
		for(int i=0;i<=len;i++) b[i]=c[i]=0;
	}
	void ln(ll*f,int n)
	{
		for(int i=0;i<=n;i++) a[i]=f[i];
		getinv(a,n);
		init(len);
		for(int i=0;i<n;i++) c[i]=f[i+1]*(i+1)%mod;
		ntt(c,len,1);
		ntt(a,len,1);
		for(int i=0;i<len;i++) a[i]=c[i]*a[i]%mod;
		ntt(a,len,0);
		for(int i=1;i<=n;i++) f[i]=a[i-1]*fastpow(i,mod-2)%mod;
		f[0]=0;
		for(int i=0;i<=len;i++) a[i]=b[i]=c[i]=0;
	}
	void exp(ll*f,int n)
	{
		for(int i=0;i<=(1<<19);i++) a[i]=b[i]=c[i]=d[i]=e[i]=g[i]=h[i]=0;
		g[0]=1;
		for(int i=2;i<=n*2;i<<=1)
		{
			for(int j=0;j<i;j++) d[j]=g[j],e[j]=f[j];
			ln(d,i-1);
			len=i<<1;
			init(len);
			ntt(d,len,1);
			ntt(g,len,1);
			ntt(e,len,1);
			for(int j=0;j<len;j++) g[j]=g[j]*(1-d[j]+e[j]+mod)%mod;
			ntt(g,len,0);
			for(int j=i;j<len;j++) g[j]=0;
		}
		for(int i=0;i<=n;i++) f[i]=g[i];
	}
	void mul(ll *a,ll *b,int n)
	{
		int len=2*n+1;
		init(len);
		for(int i=0;i<len;i++) h[i]=b[i];
		ntt(a,len,1);
		ntt(h,len,1);
		for(int i=0;i<len;i++) a[i]=a[i]*h[i]%mod;
		ntt(a,len,0);
		for(int i=n+1;i<len;i++) a[i]=0;
	}
}
ll F[N],G[N],S[N],ans,inv;
int main()
{
	freopen("frogs.in","r",stdin);
	freopen("frogs.out","w",stdout);
	scanf("%d%d%d%d%d%d",&n,&m,&A,&B,&C,&D);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n]=fastpow(fac[n],mod-2);
	for(int i=n-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
	int k=1;
	while(k<n) k<<=1;
	solve(1,k);
	k=f[1],inv=fastpow(f[1],mod-2);
	for(int i=1;i<=n;i++)
		F[i-1]=inv*f[i]%mod*ifac[i]%mod,G[i]=f[i-1]*A%mod;
	for(int i=2;i<=n;i++) G[i]=(G[i]+G[i-1]*(i-1)%mod*C)%mod;
	for(int i=1;i<=n;i++) G[i]=G[i]*ifac[i]%mod;
	poly::exp(G,n);
	poly::ln(F,n-1);
	for(int i=0;i<n;i++) F[i]=F[i]*m%mod;
	poly::exp(F,n-1);
	k=fastpow(k,m);
	for(int i=0;i<=n-m;i++) S[i+m]=F[i]*k%mod;
	for(int i=0;i<=n;i++) ans=(ans+S[i]*G[n-i])%mod;
	printf("%lld\n",ans*fac[n]%mod*ifac[m]%mod);
}
