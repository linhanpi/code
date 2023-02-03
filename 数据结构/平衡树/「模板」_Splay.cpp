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
int fa[N],cnt[N],val[N],son[N][2],si[N],root,tot;
inline bool getson(int x){
    return son[fa[x]][1]==x;
}
inline void pu(int x){
    si[x]=cnt[x]+si[son[x][0]]+si[son[x][1]];
    return ;
}
inline int bt(){
	tot++;
	son[tot][0]=son[tot][1]=fa[tot]=0;
	si[tot]=cnt[tot]=1;
	return tot;
}
void rotate(int x){
    int fath=fa[x],gfath=fa[fath],gs=getson(x);
    son[fath][gs]=son[x][gs^1]; //now.~gsson -> fa.gxson 
    fa[son[fath][gs]]=fath;
    son[x][gs^1]=fath;          //fa -> now.~gsson
    fa[fath]=x;
    fa[x]=gfath;				//granfa -> now.fa
    if(gfath)son[gfath][son[gfath][1]==fath]=x;
    pu(fath);
    pu(x);
    return ;
}
inline void splay(int x){
	for(int fath;fath=fa[x];rotate(x)){
		if(fa[fath]){
			rotate((getson(x)==getson(fath)?fath:x));
		}
	}
	root=x;
}
inline void insert(int x){
	if(!root){
		int now=bt();
		root=now;
		val[now]=x;
		return ;
	}
	int now=root,fath=0;
	while(1){
		if(x==val[now]){
			cnt[now]++;
			pu(now);
			pu(fath);
			splay(now);
			break;
		}
		fath=now;
		now=son[now][val[now]<x];
		if(!now){
			now=bt();
			fa[now]=fath;
			son[fath][val[fath]<x]=now;
			val[now]=x;
			pu(fath);
			splay(now);
			break;
		}
	}
	return ;
}
inline int kth(int x){
	int now=root;
	while(1){
		if(son[now][0]&&x<=si[son[now][0]])now=son[now][0];
		else{
			int tmp=(son[now][0]?si[son[now][0]]:0)+cnt[now];
			if(x<=tmp)
		}

	}
}
signed main(){
    
	return 0;
}
/*
*/