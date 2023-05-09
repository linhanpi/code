#include<bits/stdc++.h>
using namespace std;
int ne[1000005];
int ans[1000005];
char a[1000005];
int main(){
	int T;cin>>T;
	while(T--){
		memset(ne,0,sizeof(ne));
		scanf("%s",a);
		int n=strlen(a);
		ans[0]=0;
		ans[1]=1;
		for(int i=1,j=0;i<n;i++){
			while(j&&(a[i]!=a[j]))j=ne[j];
			j+=(a[i]==a[j]);
			ne[i+1]=j;
			ans[i+1]=ans[j]+1;
		}
		long long cnt=1;
		for(int i=1,j=0;i<n;i++){
			while(j&&(a[i]!=a[j]))j=ne[j];
			j+=(a[i]==a[j]);
			while((j*2)>(i+1))j=ne[j];
			cnt=(cnt*(long long)(ans[j]+1))%(long long)(1e9+7);
		}
		cout<<cnt<<endl;
	}
    return 0;
}