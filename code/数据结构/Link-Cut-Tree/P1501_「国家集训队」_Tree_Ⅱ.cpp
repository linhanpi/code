/*
 * @Author: watering_penguin 
 * @Date: 2023-02-07 08:37:37 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-07 10:24:50
 */
#include<bits/stdc++.h>
#define int unsigned int 
// #define uint unsigned int
// #define rint register int
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
const int inf=INT_MAX;
const int base=131;
const int mod=51061;
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
int f[N],son[N][2],si[N],val[N],sum[N],cheng[N],jia[N],sw[N];
inline bool nroot(int x){
    return son[f[x]][0]==x||son[f[x]][1]==x;
}
inline void pu(int now){
    sum[now]=(sum[son[now][0]]+sum[son[now][1]]+val[now])%mod;
    si[now]=(si[son[now][0]]+si[son[now][1]]+1);
}
inline void pdsw(int now){
    swap(son[now][0],son[now][1]);
    sw[now]^=1;
    return ;
}
inline void pdcheng(int now,int c){
    sum[now]=sum[now]*c%mod;
    val[now]=val[now]*c%mod;
    cheng[now]=cheng[now]*c%mod; 
    jia[now]=jia[now]*c%mod;
    return ;
}
inline void pdjia(int now,int c){
    sum[now]=(sum[now]+si[now]*c)%mod;
    val[now]=(val[now]+c)%mod;
    jia[now]=(jia[now]+c)%mod;
    return ;
}
void pd(int now){
    if(cheng[now]!=1)pdcheng(son[now][0],cheng[now]),pdcheng(son[now][1],cheng[now]),cheng[now]=1;
    if(jia[now])pdjia(son[now][0],jia[now]),pdjia(son[now][1],jia[now]),jia[now]=0;
    if(sw[now])pdsw(son[now][0]),pdsw(son[now][1]),sw[now]=0;
    return ;
}
void rotate(int now){
    int fa=f[now],gfa=f[fa],k=son[fa][1]==now,w=son[now][k^1];
    if(nroot(fa))son[gfa][son[gfa][1]==fa]=now;
    son[now][k^1]=fa,son[fa][k]=w;
    if(w)f[w]=fa;
    f[fa]=now,f[now]=gfa;
    pu(fa);
    return ;
}
int st[N],top;
void splay(int now){
    int y=now;
    top=0;
    st[++top]=y;
    while(nroot(y))st[++top]=y=f[y];
    while(top)pd(st[top--]);
    while(nroot(now)){
        int fa=f[now],gfa=f[fa];
        if(nroot(y))rotate((son[fa][1]==now)^(son[gfa][1]==fa)?now:fa);
        rotate(now);
    }
    pu(now);
    return ;
}
void acc(int x){
    for(int y=0;x;x=f[y=x]){
        splay(x),son[x][1]=y,pu(x);
    }
    return ;
}
void mr(int x){
    acc(x);
    splay(x);
    pdsw(x);
    return ;
}
void lian(int x,int y){
    mr(x);
    acc(y);
    splay(y);
    return ;
}
void link(int x,int y){
    mr(x);
    f[x]=y;
    return ;
}
void cut(int x,int y){
    lian(x,y);
    f[x]=son[y][0]=0;
    pu(y);
    return ;
}
int fr(int now){
    acc(now);
    splay(now);
    pd(now);
    while(son[now][0]){
        now=son[now][0];
        pd(now);
    }
    splay(now);
    return now;
}
signed main(){
    int n=read(),q=read();
    for(int i=1;i<=n;i++)val[i]=si[i]=cheng[i]=1;
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        link(a,b);
    }
    while(q--){
        char op;cin>>op;
        if(op=='+'){
            int a=read(),b=read(),c=read();
            lian(a,b);
            pdjia(b,c);
        }
        if(op=='-'){
            int a=read(),b=read();cut(a,b);
            a=read(),b=read(),link(a,b);
        }
        if(op=='*'){
            int a=read(),b=read(),c=read();
            lian(a,b);
            pdcheng(b,c);
        }
        if(op=='/'){
            int a=read(),b=read();
            lian(a,b);
            write(sum[b]);
            puts("");
        }
    }
    return 0;
}