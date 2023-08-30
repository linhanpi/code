#include<bits/stdc++.h>
#define int long long
const int MOD=998244353;
const int inv=(MOD+1)/2;
const int M=10000005;
int read(){
	int x=0,f=1;char c;
	while((c=getchar())<'0' || c>'9') {if(c=='-') f=-1;}
	while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,ans,f[M],g[M];
signed main(){
	//freopen("matrix.in","r",stdin);
	//freopen("matrix.out","w",stdout);
	n=read();
	f[2]=g[2]=1;
	for(int i=3;i<=n;i++){
		g[i]=((i-1)*f[i-2]+(i-1)*(i-2)%MOD*g[i-1])%MOD;
		f[i]=(i-1)*i/2%MOD*g[i]%MOD;
	}
	for(int i=2;i<=n;i++) ans=(ans+f[i])%MOD;
	printf("%lld\n",(ans+MOD)%MOD);
	return 0;
}