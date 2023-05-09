/*
 * @Author: watering_penguin 
 * @Date: 2023-03-02 15:41:42 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-11 14:33:10
 */
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
template<typename T>inline T red() {
	T x=0;
	bool f=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=true;
		c=getchar();
    }
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>inline void write(T x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=1e3+5;
const int M=1e2+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=1e4+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
    x%=mod;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
inline int fang(int x) {return x*x;}
int a[N][N],ans[N][N],h[N],sta[N],zs[N][N],zx[N][N],ys[N][N],yx[N][N],zsd[N][N],zxd[N][N];
int n,top;
void ddz(){
	memset(h,0,sizeof(h));
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j])h[j]++;
			else ans[i][j]=-1,h[j]=0;
		}
		top=0;
		sta[++top]=0;
		ans[i][0]=-1;
		for(int j=1;j<=n;j++){
			while(top&&h[sta[top]]>=h[j])top--;
			if(top&&a[i][j])ans[i][j]=ans[i][sta[top]]+(j-sta[top])*h[j];
			sta[++top]=j;
		}
		for(int j=1;j<=n;j++)ans[i][j]=max(ans[i][j],0ll);
	}
	return ;
}
void zyf(int c[N][N]){
	for(int i=1;i<=n;i++)for(int a=1,b=n;a<b;a++,b--)swap(c[i][a],c[i][b]);
	return ;
}
void sxf(int c[N][N]){
	for(int a=1,b=n;a<b;a++,b--)for(int j=1;j<=n;j++)swap(c[a][j],c[b][j]);
	return ;
}
void qzh(int c[N][N]){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			c[i][j]=((-c[i-1][j-1]+c[i][j]+c[i-1][j]+c[i][j-1])%mod+mod)%mod;
		}
	}
	return ;
}
void cp(int c1[N][N],int c2[N][N]){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			c1[i][j]=c2[i][j];
		}
	}
	return ;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char ch;cin>>ch;
			if(ch=='C')a[i][j]=1;
		}
	}
	ddz();cp(zsd,ans);cp(zs,ans);qzh(zs);
	zyf(a);ddz();cp(ys,ans);qzh(ys);zyf(ys);
	sxf(a);ddz();cp(yx,ans);qzh(yx);sxf(yx);zyf(yx);
	zyf(a);ddz();cp(zxd,ans);cp(zx,ans);qzh(zx);sxf(zxd);sxf(zx);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+(zx[1][i]-zx[1][i-1]+mod)%mod*yx[1][i+1]%mod)%mod;
		ans=(ans+(ys[i][1]-ys[i-1][1]+mod)%mod*yx[i+1][1]%mod)%mod;
		for(int j=1;j<=n;j++){
			ans=(ans-zsd[i][j]*yx[i+1][j+1]+mod)%mod;
			ans=(ans-zxd[i][j]*ys[i-1][j+1]+mod)%mod;
		}
	}
	cout<<ans<<endl;
    return 0;
}
