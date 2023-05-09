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
const int N=1e6+5;
const int M=25+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
// const int mod=1e9+7;
int mod=1e4+7;
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
char a[M];
int ne[M];
int g[M][M];
struct node{
	int a[25][25];
	node(){
		memset(a,0,sizeof(a));
	}
}A,B;
node operator *(const node &x,const node &y){
	node c;
	for(int i=0;i<=20;i++){
		for(int j=0;j<=20;j++){
			for(int k=0;k<=20;k++){
				c.a[i][j]=(c.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
			}
		}
	}
	return c;
}
signed main(){
	int n=read(),m=read();mod=read();
    scanf("%s",a+1);
    for(int i=2,j=0;i<=m;i++){
        while(j&&a[j+1]!=a[i])j=ne[j];
        if(a[j+1]==a[i])j++;
        ne[i]=j;
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<=9;j++){
            int p=i;
            while(p&&a[p+1]-'0'!=j)p=ne[p];
            if(a[p+1]-'0'==j)p++;
            if(p<m)B.a[i][p]++;
            // cout<<"i "<<i<<" "<<j<<" "<<p<<endl;
        }
    }
    A.a[0][0]=1;
    while(n){
        if(n&1)A=A*B;
        B=B*B;
        n>>=1;
    }
    int ans=0;
    for(int i=0;i<m;i++){
        ans=(ans+A.a[0][i])%mod;
    }
    cout<<ans<<endl;
    return 0;
}
