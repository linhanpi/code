/*
 * @Author: watering_penguin 
 * @Date: 2023-02-10 12:05:59 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-10 12:05:59 
 */
#include<bits/stdc++.h>
// #define int long long
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
const int N=3e2+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const double eps=1e-6;
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
int cei(int x,int y){return x%y==0?x/y:x/y+1;}
int a[N][N],b[M],v[2005],pos[M],tot,dp[2][N][2005];
signed main(){
    int n=read(),m=read(),lim=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]=read();
        }
    }
    for(int i=1;i<=lim;i++){
        b[i]=cei(lim,i);
        // cout<<b[i]<<endl;
    }
    for(int i=1;i<=lim;i++){
        if(b[i]!=b[i-1])v[++tot]=b[i],pos[b[i]]=tot;
    }
    dp[1][1][pos[cei(lim,a[1][1])]]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=tot;k++){
                if(i!=n){
                    dp[(i&1)^1][j][pos[cei(v[k],a[i+1][j])]]=(dp[(i&1)^1][j][pos[cei(v[k],a[i+1][j])]]+dp[i&1][j][k])%mod;
                }
                if(j!=m){
                    dp[i&1][j+1][pos[cei(v[k],a[i][j+1])]]=(dp[i&1][j+1][pos[cei(v[k],a[i][j+1])]]+dp[i&1][j][k])%mod;
                }
                if(i!=n||j!=m||k!=tot)dp[i&1][j][k]=0;
            }
        }
    }
    cout<<dp[n&1][m][tot]<<endl;
    return 0;
}