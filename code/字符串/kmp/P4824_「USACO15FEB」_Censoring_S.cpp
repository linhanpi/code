/*
 * @Author: watering_penguin 
 * @Date: 2023-03-02 15:41:42 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-11 14:33:10
 */
#include<bits/stdc++.h>
// #define int long long//信仰
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
char s1[N],s2[N];
int sta[N];
int nee[N],ne[N];
int top;
signed main(){
	scanf("%s",s1+1);
    scanf("%s",s2+1);
    int n=strlen(s1+1),m=strlen(s2+1);
    for(int i=2,j=0;i<=m;i++){
        while(j&&s2[j+1]!=s2[i])j=ne[j];
        j+=(s2[j+1]==s2[i]);
        ne[i]=j;
    }
    nee[0]=0;
    for(int i=1,j=0;i<=n;i++){
        while(j&&s1[i]!=s2[j+1])j=ne[j];
        j+=(s2[j+1]==s1[i]);
        nee[i]=j;sta[++top]=i;
        if(j==m)top-=m,j=nee[sta[top]];
    }
    for(int i=1;i<=top;i++){
        cout<<s1[sta[i]];
    }
    return 0;
}
