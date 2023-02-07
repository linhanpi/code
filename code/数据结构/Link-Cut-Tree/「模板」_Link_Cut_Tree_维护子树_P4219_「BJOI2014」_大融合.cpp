/*
 * @Author: watering_penguin 
 * @Date: 2023-02-07 10:28:42 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-07 11:39:38
 */
#include<bits/stdc++.h>
#define int long long
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
int f[N],son[N][2],si[N],val[N],sum[N],sw[N],six[N];
void cl(int now){
    son[now][0]=son[now][1]=f[now]=si[now]=six[now]=val[now]=0;
    return ;
}
int nroot(int now){
    return son[f[now]][0]==now||son[f[now]][1]==now;
}
void pu(int now){
    cl(0);
    if(now)si[now]=si[son[now][0]]+si[son[now][1]]+six[now]+1;
    return ;
}
void pdsw(int now){
    swap(son[now][0],son[now][1]);
    sw[now]^=1;
    return ;
}
void pd(int now){
    if(sw[now]){
        pdsw(son[now][0]);
        pdsw(son[now][1]);
        sw[now]=0;
    }
    return ;
}
void rotate(int now){
    int fa=f[now],gfa=f[fa],k=son[fa][1]==now,w=son[now][k^1];
    if(nroot(fa))son[gfa][son[gfa][1]==fa]=now;
    son[fa][k]=w,son[now][k^1]=fa;
    if(w)f[w]=fa;
    f[now]=gfa,f[fa]=now;
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
        if(nroot(fa)){
            rotate((son[fa][1]==now)^(son[gfa][1]==fa)?now:fa);
        }
        rotate(now);
    }
    pu(now);
    return ;
}
void acc(int now){
    for(int y=0;now;now=f[y=now]){
        splay(now);
        six[now]+=si[son[now][1]]-si[y];
        son[now][1]=y;
        pu(now);
    }
    return ;
}
void mr(int now){
    acc(now);
    splay(now);
    pdsw(now);
    return ;
}
int fr(int now){
    acc(now);
    splay(now);
    pd(now);
    while(son[now][0]){
        pd(now);
        if(son[now][0])break;
        now=son[now][0];
    }
    splay(now);
    return now;
}
void lian(int x,int y){
    mr(x);
    acc(y);
    splay(y);
    return ;
}
void link(int x,int y){
    lian(x,y);
    f[x]=y;
    six[y]+=si[x];
    pu(y);
    return ;
}
signed main(){
    int n=read(),q=read();
    for(int i=1;i<=n;i++){
        si[i]=1;
    }
    while(q--){
        char ch;cin>>ch;
        if(ch=='A'){
            int x=read(),y=read();
            link(x,y);
        }
        else{
            int x=read(),y=read();
            lian(x,y);
            write(si[x]*(si[y]-si[x]));
            // write((six[x]+1)*(six[y]+1));
            puts("");
        }
    }
    return 0;
}