#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll t=60;
ll n,f[100][100],s[100][100],l,r;
int T,m;
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int i,j;
	ll k;
	f[1][0]=s[1][0]=1;
	for (i=1;i<=t;i++)
	for (j=max(i-1,1);j<=t;j++){
		f[i][j]=f[i][j-1]+f[i-1][j-1];
		s[i][j]=f[i][j]+s[i-1][j-1];
	}
	scanf("%d",&T);
	while(T--){
		scanf("%lld%d",&n,&m);
		if(!n){
			printf("1 %lld\n",(1ll<<(m-1))-1);
			continue;
		}
		if(m==1){
			printf("1 -1\n");
			continue;
		}
		l=0;
		k=n;
		for(i=m,j=t;i && k;i--){
			for(;j && s[i][j-1]>=k;j--);
			l+=1ll<<j;
	  		k-=f[i][j];
		}
		l=max(l,1ll);
		r=0;k=n;
		for(i=m,j=t+1;i;i--)
		for(j--;j>=0;j--)
		if(k>=f[i][j]){
			r+=1ll<<j;
			k-=f[i][j];
			break;
		}
		for(j--;j>=0;j--) r+=1ll<<j;
		printf("%lld %lld\n",l,r-l+1);
	}
	return 0;
}

