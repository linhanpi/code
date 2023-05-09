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
void bd(char *s,int len,int *fail){
    int p=0;
    for(int i=2;i<=len;i++){
        while(p&&s[p+1]!=s[i])p=fail[p];
        if(s[p+1]==s[i])p++;
        fail[i]=p;
    }
    return ;
}
void pp(char *s,char *t,int len,int *fail,int *cx){
    int p=0;
    for(int i=1;i<=len;i++){
        while(p&&s[p+1]!=t[i])p=fail[p];
        if(s[p+1]==t[i])p++;
        cx[i]=p;
    }
    return ;
}
char s1[N],s2[N];
int f[N],cx[N],len1,len2;
signed main(){
	scanf("%s%s",s2+1,s1+1);
    len1=strlen(s1+1);
    len2=strlen(s2+1);
    bd(s1,len1,f);
    pp(s1,s2,len2,f,cx);
    for(int i=1;i<=len2;i++){
        if(cx[i]==len1)cout<<i-len1+1<<endl;
    }
    for(int i=1;i<=len1;i++){
        cout<<f[i]<<" ";
    }
    return 0;
}
