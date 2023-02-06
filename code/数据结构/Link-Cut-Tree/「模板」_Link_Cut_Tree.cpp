/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:49:26 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-06 17:07:51
 */
#include<bits/stdc++.h>
// #define int long long
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
const int N=3e5+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=INT_MAX;
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
int f[N],son[N][2],val[N],yhsum[N],fan[N];
inline bool srt(int now){
    return son[f[now]][0]==now||son[f[now]][1]==now;
}
inline void pu(int now){
    yhsum[now]=yhsum[son[now][0]]^yhsum[son[now][1]]^val[now];
}
inline void pdf(int now){
    int t=son[now][0];
    son[now][0]=son[now][1];
    son[now][1]=t;
    fan[now]^=1;
    return ;
}
inline void pd(int now){
    if(fan[now]){
        if(son[now][0])pdf(son[now][0]);
        if(son[now][1])pdf(son[now][1]);
        fan[now]=0;
    }
}
inline void rotate(int now){
    int fa=f[now],gfa=f[fa];
    int k=son[fa][1]==now,w=son[now][k^1];
    if(srt(fa))son[gfa][son[gfa][1]==fa]=now;
    son[now][k^1]=fa,son[fa][k]=w;
    if(w)f[w]=fa;
    f[fa]=now,f[now]=gfa;
    pu(fa);
    // pu(now);
    return ;
}
int st[N],top;
inline void splay(int now){
    int y=now;
    top=0;
    st[++top]=y;
    while(srt(y))st[++top]=y=f[y];
    while(top)pd(st[top--]);
    while(srt(now)){
        // cout<<"noww "<<now<<endl;
        int fa=f[now],gfa=f[fa];
        if(srt(fa)){
            rotate(((son[fa][0]==now)^(son[gfa][0]==fa))?now:fa);
        }
        rotate(now);
    }
    pu(now);
    return ;
}
inline void acc(int now){
    // cout<<"2"<<endl;
    for(int y=0;now;now=f[y=now]){
        // cout<<"now "<<now<<endl;
        splay(now),son[now][1]=y,pu(now);
    }
    // cout<<"2"<<endl;
    return ;
}
inline void makeroot(int now){
    // cout<<"1"<<endl;
    acc(now);splay(now);pdf(now);
    return ;
}
inline void lian(int x,int y){
    makeroot(x);acc(y);splay(y);
    return ;
}
inline int findroot(int now){
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
inline void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x)f[x]=y;
    return ;
}
inline void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&f[y]==x&&!son[y][0]){
        f[y]=son[x][1]=0;
        pu(x);
    }
    return ;
}
signed main(){
    int n=read(),q=read();
    // splay(0);
    for(int i=1;i<=n;i++)val[i]=read();
    while(q--){
        int pos=read(),x=read(),y=read();
        if(pos==0)lian(x,y),printf("%d\n",yhsum[y]);
        if(pos==1)link(x,y);
        if(pos==2)cut(x,y);
        if(pos==3)splay(x),val[x]=y;
    }
    return 0;
}