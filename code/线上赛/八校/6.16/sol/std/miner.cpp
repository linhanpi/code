#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
inline int read()
{
	int x=0,ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
const int B=100;
int n,m,k,a[5000005],b[5000005],vis[5000005],q[100005][2],qans[100005];
int f[5000005],g[5000005],sum[5000005];
//int cntf,cntg;
void updf(int i)
{
//	cntf++;
//	printf("updf:i=%d\n",i);
	for(int j=k;j>=1ll*a[i]*b[i];j--)
	{
		f[j]=max(f[j],f[j-a[i]*b[i]]+b[i]);
	//	printf("j=%d,f=%d\n",j,f[j]);
	}
}
void updg(int i)
{
	for(int j=k/B;j>=b[i];j--)
	{
		g[j]=min((long long)g[j],g[j-b[i]]+1ll*a[i]*b[i]);
	//	if(g[j]<1e9) printf("updg:j=%d,g=%d\n",j,g[j]);
	}
}
int main()
{
	freopen("miner.in","r",stdin);
	freopen("miner.out","w",stdout);
	memset(g,0x3f,sizeof(g));
	g[0]=0;
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=read();
	for(int i=1;i<=m;i++)
	{
		q[i][0]=read(),q[i][1]=read();
		if(q[i][0]==1) vis[q[i][1]]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]&&a[i]<=B)
			updf(i);
	int cntg=0;
	for(int i=1;i<=n;i++)
		if(!vis[i]&&a[i]>B)
		{
			if(sum[b[i]]+1ll*a[i]*b[i]<=k)
			{
				sum[b[i]]+=a[i]*b[i];
				updg(i);
				cntg++;
			}
		}
	for(int i=m;i>0;i--)
	{
		if(q[i][0]==1)
		{
			int u=q[i][1];
			if(a[u]<=B) updf(u);
			else updg(u);
			qans[i]=-1;
		}
		else
		{
			int mx=q[i][1]/B,ans=0;
			for(int j=0;j<=mx;j++)
				if(g[j]<=q[i][1])
				{
					ans=max(ans,j+f[q[i][1]-g[j]]);
				//	fprintf(stderr,"i=%d,j=%d,f=%d,%d\n",i,j,f[q[i][1]-g[j]],q[i][1]-g[j]);
				}
			//	else break;
			qans[i]=ans;
		}
	}
//	fprintf(stderr,"cntg=%d\n",cntg);
	for(int i=1;i<=m;i++)
		if(qans[i]!=-1) printf("%d\n",qans[i]);
	return 0; 
}
