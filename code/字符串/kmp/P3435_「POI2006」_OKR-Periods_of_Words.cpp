#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
inline int read() {
	int s=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)) {
		s=(s<<1)+(s<<3)+ch-'0';
		ch=getchar();
	}
	return s*w;
}
inline void write(int x) {
	if(x<0) {
		putchar('-');
		x=(~x+1);
	}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=1e6+5;
const double eps=1e-10;
const double yi=1.0;
const double inf=1e16;
const int mod=998244353;
int ne[N],f[N];
signed main(){
	string a;
	int n=read();
	cin>>a;
	a='+'+a;
	for(int i=2,j=0;i<=n;i++){
		while(j>0&&a[i]!=a[j+1])j=ne[j];
		j+=(a[i]==a[j+1]);
		ne[i]=j;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int j=i;
		while(ne[j])j=ne[j];
		if(ne[i]!=0)ne[i]=j;
		ans+=i-j;
	}
	cout<<ans<<endl;
	return 0;
}