#include<bits/stdc++.h>
#define int long long
// #define ll long long
// #define double long double
//#define pii pair <int,int>
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
const int N=1e5+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod=(1<<30);
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
int fa[N],cnt[N],val[N],son[N][2],si[N],root;
inline bool getson(int x){
    return son[fa[x]][1]==x;
}
inline void pu(int x){
    si[x]=cnt[x]+si[son[x][0]]+si[son[x][1]];
    return ;
}
void rotate(int x){
    int fath=fa[x],gfath=fa[fath],gs=getson(x);
    son[fath][gs]=son[x][gs^1]; //now.~gsson -> fa.gxson 
    fa[son[fath][gs]]=fath;
    son[x][gs^1]=fath;          //
    fa[fath]=x;
    fa[x]=gfath;
    if(gfath){
        son[gfath][son[gfath][1]==fath]=x;
    }
    pu(fath);
    pu(x);
    return ;
}
signed main(){
    
	return 0;
}
/*
*/