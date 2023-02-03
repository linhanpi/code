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
struct FHQ_treap{
    int a,b;
    FHQ_treap(int a_=0,int b_=0){
        a=a_,b=b_;
    }
};
int son[N][2],val[N],rk[N],si[N],root,tot;
inline void pu(int now){
    si[now]=si[son[now][1]]+si[son[now][0]]+1;
}
FHQ_treap fl(int now,int k){
    if(!now){
        return FHQ_treap(0,0);
    }
    if(val[now]<k){
        FHQ_treap t=fl(son[now][1],k);
        son[now][1]=t.a;
        pu(now);
        return FHQ_treap(now,t.b);
    }
    else{
        FHQ_treap t=fl(son[now][0],k);
        son[now][0]=t.b;
        pu(now);
        return FHQ_treap(t.a,now);
    }
}
int hb(int now1,int now2){
    if(!now1||!now2){
        return now1+now2;
    }
    if(rk[now1]<rk[now2]){
        son[now1][1]=hb(son[now1][1],now2);
        pu(now1);
        return now1;
    }
    else{
        son[now2][0]=hb(now1,son[now2][0]);
        pu(now2);
        return now2;
    }
}
void add(int k){
    val[++tot]=k;
    rk[tot]=rand();
    si[tot]=1;
    FHQ_treap t=fl(root,k);
    root=hb(hb(t.a,tot),t.b);
    return ;
}
void shan(int k){
    FHQ_treap t1=fl(root,k);
    FHQ_treap t2=fl(t1.b,k+1);
    t2.a=hb(son[t2.a][0],son[t2.a][1]);
    root=hb(t1.a,hb(t2.a,t2.b));
    return ;
}
int chak(int k){
    FHQ_treap t=fl(root,k);
    int res=si[t.a]+1;
    root=hb(t.a,t.b);
    return res;
}
int kth(int k){
    int pos=root;
    while(pos){
        if(k==si[son[pos][0]]+1)return val[pos];
        if(k<=si[son[pos][0]])pos=son[pos][0];
        else{
            k-=si[son[pos][0]]+1;
            pos=son[pos][1];
        }
    }
    return 0;
}
int qq(int k){
    return kth(chak(k)-1);
}
int hj(int k){
    return kth(chak(k+1));
}
signed main(){
    srand(1145141919);
    int m=read();
    int last=0;
    // for(int i=1;i<=n;i++){
    //     int a=read();
    //     add(a);
    // }
    int ans=0;
    for(int i=1;i<=m;i++){
        int op=read(),x=read();
        if(op==1)add(x);
        if(op==2)shan(x);
        if(op==3)write(chak(x)),puts("");
        if(op==4)write(kth(x)),puts("");
        if(op==5)write(qq(x)),puts("");
        if(op==6)write(hj(x)),puts("");
    }
	return 0;
}
/*
*/