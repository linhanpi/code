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
const int N=1e6+5;
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
int n,m;
int c[N];
void cg(int x,int y){
	for(int i=x;i<=2*m;i+=lowbit(i)){
		c[i]+=y;
	}
	return ;
}
int cha(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		res+=c[i];
	}
	return res;
}
int lll[N],rr[N],b[N];
struct cha{
	int op,l,r,id,v;
}Q[N],tl[N],tr[N];
int cnt;
vector <int> you[N];
int ans[N];
void ztef(int st,int en,int l,int r){
	// if(st>en)return ;
	if(l==r){
		for(int i=st;i<=en;i++){
			if(Q[i].op==1)ans[Q[i].id]=l;
		}
		return ;
	}
	int mid=(l+r)>>1;
	bool fl=0,fr=0;
	int L=0,R=0;
	for(int i=l;i<=mid;i++){
		cg(lll[i],b[i]);
		cg(rr[i]+1,-b[i]);
	}
	for(int i=st;i<=en;i++){
		int res=0;
		for(int y:you[Q[i].id]){
			res+=cha(y)+cha(y+m);
			if(res>Q[i].v)break;
		}
		if(res<Q[i].v){
			Q[i].v-=res;
			fr=1;
			tr[++R]=Q[i];
		}
		else{
			fl=1;
			tl[++L]=Q[i];
		}
	}
	for(int i=l;i<=mid;i++){
		cg(lll[i],-b[i]);
		cg(rr[i]+1,b[i]);
	}
	for(int i=1;i<=L;i++)Q[st+i-1]=tl[i];
	for(int i=L+1;i<=L+R;i++)Q[st+i-1]=tr[i-L];
	if(fl)ztef(st,st+L-1,l,mid);
	if(fr)ztef(st+L,en,mid+1,r);
	return ;
}
int a[N];
signed main(){
    n=read(),m=read();
	for(int i=1;i<=m;i++){
		int b=read();
		you[b].push_back(i);
	}
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	int k=read();
	for(int i=1;i<=k;i++){
		lll[i]=read(),rr[i]=read(),b[i]=read();
		if(lll[i]>rr[i])rr[i]+=m;
	}
	for(int i=1;i<=n;i++){
		Q[++cnt]={1,0,0,i,a[i]};
	}
	ztef(1,cnt,1,k+1);
	for(int i=1;i<=n;i++){
		if(ans[i]==k+1){
			puts("NIE");
			continue;
		}
		write(ans[i]);
		puts("");
	}
    return 0;
}