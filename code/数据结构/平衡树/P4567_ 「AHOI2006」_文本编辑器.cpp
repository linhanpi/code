/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:49:31 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:49:31 
 */
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
const int N=3e6+5;
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
struct FHQ_treap{
    int a,b;
    FHQ_treap(int a_=0,int b_=0){
        a=a_,b=b_;
    }
};
int root,tot;
int son[N][2],si[N],rk[N],lazy[N];
char val[N];
void pu(int now){
	si[now]=si[son[now][0]]+si[son[now][1]]+1;
	return ;
}
void pd(int now){
	if(lazy[now]){
		swap(son[now][0],son[now][1]);
		lazy[son[now][0]]^=1,lazy[son[now][1]]^=1;
		lazy[now]=0;
	}
	return ;
}
int bt(){
	++tot;
	lazy[tot]=son[tot][0]=son[tot][1]=0;
	si[tot]=1,rk[tot]=rand();
	return tot;
}
int hb(int now1,int now2){
	if(!now1||!now2)return now1+now2;
	if(rk[now1]<rk[now2]){
		pd(now1);
		son[now1][1]=hb(son[now1][1],now2);
		pu(now1);
		return now1;
	}
	else{
		pd(now2);
		son[now2][0]=hb(now1,son[now2][0]);
		pu(now2);
		return now2;
	}
}
FHQ_treap fl(int now,int k){
	if(!now){
		return FHQ_treap(0,0);
	}
	pd(now);
	if(si[son[now][0]]+1<k){
		FHQ_treap t=fl(son[now][1],k-si[son[now][0]]-1);
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
string a;
int bd(int l,int r){
	if(l==r){
		int p=bt();
		val[p]=a[l];
		return p;
	}
	int mid=(l+r)>>1;
	return hb(bd(l,mid),bd(mid+1,r));
}
void add(char x,int k){
	FHQ_treap t=fl(root,k);
	int p=bt();
	val[p]=x;
	root=hb(hb(t.a,p),t.b);
	return ;
}
void insert(int x,int k){
	int p=bd(0,k-1);
	FHQ_treap t=fl(root,x);
	root=hb(hb(t.a,p),t.b);
	return ;
}
int chak(int k){
	FHQ_treap t=fl(root,k);
	int res=si[t.a]+1;
	root=hb(t.a,t.b);
	return res;
}
char kth(int k){
	int now=root;
	while(now){
		pd(now);
		if(si[son[now][0]]+1==k)return val[now];
		if(si[son[now][0]]+1<=k){
			k-=si[son[now][0]]+1;
			now=son[now][1];
		}
		else{
			now=son[now][0];
		}
	}
	return 0;
}
int qq(int x){
	return kth(chak(x)-1);
}
int hj(int x){
	return kth(chak(x+1));
}
void shan(int x,int k){
	FHQ_treap t1=fl(root,x);
	FHQ_treap t2=fl(t1.b,k+1);
	root=hb(t1.a,t2.b);
	return ;
}
void rotate(int x,int k){
	FHQ_treap t1=fl(root,x);
	FHQ_treap t2=fl(t1.b,k+1);
	lazy[t2.a]^=1;
	root=hb(t1.a,hb(t2.a,t2.b));
	return ;
}
signed main(){
	srand(1145141919);
    int n=read();
	char op[10];
	int p=0;
	int now=0;
	for(int i=1;i<=n;i++){
		scanf("%s",op);
		if(op[0]=='M')p=read();
		if(op[0]=='I'){
			int k=read();
			getline(cin,a);
			// for(int j=1;j<=k;j++){
			// 	a[j]=getchar();
			// 	add(a[j],p+j);
			// }
			now+=k;
			insert(p+1,k);
			for(int j=1;j<=k;j++){
				a[j]='\0';
			}
		}
		if(op[0]=='D'){
			int k=read();
			now-=k;
			shan(p+1,k);
		}
		if(op[0]=='R'){
			int k=read();
			rotate(p+1,k);
		}
		if(op[0]=='G'){
			char ch=kth(p+1);
			putchar(ch);
			if(ch!='\n')puts("");
		}
		if(op[0]=='P')p--;
		if(op[0]=='N')p++;
		// cout<<"begin-----------------------------------"<<endl;
		// cout<<"p "<<p<<endl;
		// for(int j=1;j<=now;j++){
		// 	cout<<kth(j);
		// }
		// cout<<"\nend-------------------------------------"<<endl;
	}
    return 0;
}