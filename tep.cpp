#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,ans,t,sg[N],vis[N],a[N];
inline void work(int ans)
{
	int tot=0,ii=-1,jj,kk;
	for(int i=n;i>=1;i--)
		for(int j=i-1;j>=1;j--)
			for(int k=j;k>=1;k--)
				if((ans^sg[i]^sg[j]^sg[k])==0)
				{
					tot++;
					if(ii==-1) ii=n-i,jj=n-j,kk=n-k;
				}
	printf("%d %d %d\n%d\n",ii,jj,kk,tot);
}
int main()
{
	sg[1]=0;//预处理
	for(int i=2;i<=25;i++)
		for(int j=1;j<=i;j++)
			for(int k=j;k<i;k++)//暴力枚举i,j,k
			{
				vis[sg[j]^sg[k]]=i;//SG函数的转移
				for(sg[i]=0;vis[sg[i]]==i;sg[i]++);
			}
	for(scanf("%d",&t),ans=0;t--;ans=0)
	{
		scanf("%d",&n);
		for(int i=n;i>=1;i--) scanf("%d",a+i);
		for(int i=n;i>=1;i--) if(a[i]&1) ans^=sg[i];//这里是一个优化，每个数可以直接变成对二取模后的值。
		if(!ans) puts("-1 -1 -1\n0");else work(ans);
	}
	return 0;
}