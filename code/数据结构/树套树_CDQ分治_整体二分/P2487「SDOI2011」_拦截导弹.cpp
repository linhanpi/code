/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:49:26 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-25 14:14:33
 */
#include<bits/stdc++.h>
//#pragma GCC optimize(2)
 #define int __int128
// #define rint register int
// #define ll long long
 #define double long double
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
const int N=5e4+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
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
int cmx[N],csh[N];
int n,m;
inline void gai(int x,int y,int z){
	for(int i=x;i<=n;i+=lowbit(i)){
		if(y>cmx[i])cmx[i]=y,csh[i]=z;
		else if(y==cmx[i])csh[i]=(csh[i]+z);
	}
	return ;
}
inline void cha(int x,int &mx,int &cn,int val){
	for(int i=x;i;i-=lowbit(i)){
		if(cmx[i]+val>mx)mx=cmx[i]+val,cn=csh[i];
		else if(cmx[i]+val==mx)cn=(cn+csh[i]);
	}
	return ;
}
inline void cl(int x){
	for(int i=x;i<=n;i+=lowbit(i)){
		cmx[i]=csh[i]=0;
	}
	return ;
}
struct node{
	int a,b,i,ans,op,ansci;
}Q[N],tp[N];
bool cmp1(const node &x,const node &y){
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	if(x.ans!=y.ans)return x.ans<y.ans;
	return x.i<y.i;
}
bool cmp2(const node &x,const node &y){
	if(x.b!=y.b)return x.b<y.b;
	if(x.ans!=y.ans)return x.ans<y.ans;
	if(x.i!=y.i)return x.i<y.i;
	return x.a<y.a;
}
bool cmp(const node &x,const node &y){
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	return x.i<y.i;
}
bool cmpt(const node &x,const node &y){
	return x.i<y.i;
}
int pos1[N],pos2[N];
void cdq1(int l,int r){
	if(l==r)return ;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	sort(Q+l,Q+mid+1,cmp);
	sort(Q+mid+1,Q+r+1,cmp);
	int i=l,j=mid+1;
	for(;j<=r;j++){
		while(i<=mid&&Q[i].a<=Q[j].a)gai(Q[i].b,Q[i].ans,Q[i].ansci),i++;
		cha(Q[j].b,Q[j].ans,Q[j].ansci,1);
	}
	i--;
	for(;i>=l;i--)cl(Q[i].b);
	for(int i=l;i<=r;i++)tp[pos1[Q[i].i]]=Q[i];
	for(int i=l;i<=r;i++)Q[i]=tp[i];
	cdq1(mid+1,r);
	return ;
}
int d[N],len,res[N],rres[N];
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
    	int j=n-i+1;
		pos1[i]=i;
		Q[j].a=read(),Q[j].ansci=1,Q[j].ans=1,Q[j].b=read(),Q[j].i=j,d[++len]=Q[j].b;
	}
	sort(d+1,d+len+1);
	len=unique(d+1,d+len+1)-d-1;
	for(int i=1;i<=n;i++){
		Q[i].b=lower_bound(d+1,d+len+1,Q[i].b)-d;
	}
	cdq1(1,n);
	sort(Q+1,Q+n+1,cmpt);
	int ans=0,anss=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,Q[i].ans);
	}
    for(int i=1;i<=n;i++){
        if(Q[i].ans==ans)anss+=Q[i].ansci;
    }
	for(int i=1;i*2<=n;i++){
		swap(Q[i],Q[n-i+1]);
	}
	for(int i=1;i<=n;i++){
		Q[i].i=i;
		Q[i].a=-Q[i].a;
		Q[i].b=len-Q[i].b+1;
        rres[Q[i].i]=Q[i].ans;
        res[Q[i].i]=Q[i].ansci;
        Q[i].ans=1;
        Q[i].ansci=1;
    }
    sort(Q+1,Q+n+1,cmpt);
    cdq1(1,n);
	write(ans);
	puts("");
	for(int i=1;i<=n;i++){
		if(rres[Q[i].i]+Q[i].ans-1!=ans||Q[i].ansci*res[Q[i].i]==0)printf("0.00000 ");
		else printf("%.5Lf ",(double)Q[i].ansci*res[Q[i].i]/anss);
	}
    return 0;
}