#include<bits/stdc++.h>
#define int long long
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
const int N=5e5+5;
const int M=6e4+5;
const int mo=7000007;
const int inf=1e16+9;
const int base=131;
const int mod=998244353;
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
		else if(y==cmx[i])csh[i]=(csh[i]+z)%mod;
	}
	return ;
}
inline void cha(int x,int &mx,int &cn,int val){
	for(int i=x;i;i-=lowbit(i)){
		if(cmx[i]+val>mx)mx=cmx[i]+val,cn=csh[i];
		else if(cmx[i]+val==mx)cn=(cn+csh[i])%mod;
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
	int a,b,c,d,val,dpmx,dpsh,i,op;
}Q[N],tmp[N];
bool operator ==(const node &x,const node &y){
	return (x.a==y.a)&&(x.b==y.b)&&(x.c==y.c)&&(x.d==y.d);
}
bool cmp1(const node &x,const node &y){
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	if(x.c!=y.c)return x.c<y.c;
	return x.d<y.d;
}
bool cmp2(const node &x,const node &y){
	if(x.b!=y.b)return x.b<y.b;
	if(x.c!=y.c)return x.c<y.c;
	if(x.d!=y.d)return x.d<y.d;
	return x.a<y.a;
}
bool cmp3(const node &x,const node &y){
	if(x.c!=y.c)return x.c<y.c;
	if(x.d!=y.d)return x.d<y.d;
	if(x.a!=y.a)return x.a<y.a;
	return x.b<y.b;
}
int pos1[N],pos2[N];
void cdq2(int l,int r){
	if(l==r)return ;
	int mid=(l+r)>>1;
	cdq2(l,mid);
	sort(Q+l,Q+mid+1,cmp3);
	sort(Q+mid+1,Q+r+1,cmp3);
	int i=mid+1,j=l;
	for(;i<=r;i++){
		while(j<=mid&&Q[j].c<=Q[i].c){
			if(Q[j].op)gai(Q[j].d,Q[j].dpmx,Q[j].dpsh);
			++j;
		}
		if(!Q[i].op)cha(Q[i].d,Q[i].dpmx,Q[i].dpsh,Q[i].val);
	}
	for(int i=l;i<j;i++)if(Q[i].op)cl(Q[i].d);
	for(int i=l;i<=r;i++)tmp[pos2[Q[i].i]]=Q[i];
	for(int i=l;i<=r;i++)Q[i]=tmp[i];
	cdq2(mid+1,r);
	return ;
}
void cdq1(int l,int r){
	// cout<<"l r "<<l<<" "<<r<<endl;
	if(l==r)return ;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	for(int i=l;i<=mid;i++)Q[i].op=1;
	for(int i=mid+1;i<=r;i++)Q[i].op=0;
	sort(Q+l,Q+r+1,cmp2);
	for(int i=l;i<=r;i++)pos2[Q[i].i]=i;
	cdq2(l,r);
	for(int i=l;i<=r;i++)tmp[pos1[Q[i].i]]=Q[i];
	for(int i=l;i<=r;i++)Q[i]=tmp[i];
	cdq1(mid+1,r);
	return ;
}
int d[N];
signed main(){
    n=read(),m=read();
	for(int i=1;i<=n;i++){
		Q[i].a=read(),Q[i].b=read(),Q[i].c=read(),Q[i].d=read(),Q[i].val=read();
		d[i]=Q[i].d;
	}
	sort(d+1,d+n+1);
	int len=unique(d+1,d+n+1)-d-1;
	for(int i=1;i<=n;i++)Q[i].d=lower_bound(d+1,d+len+1,Q[i].d)-d;
	int cnt=0;
	sort(Q+1,Q+n+1,cmp1);
	for(int i=1;i<=n;i++){
		if(Q[i]==Q[i-1]){
			Q[cnt].val+=max(0ll,Q[i].val);
		}
		else{
			Q[++cnt]=Q[i];
		}
	}
	for(int i=1;i<=cnt;i++){
		Q[i].dpmx=Q[i].val,Q[i].i=i,pos1[i]=i,Q[i].dpsh=1;
	}
	cdq1(1,cnt);
	int ans=-inf,res=0;
	for(int i=1;i<=cnt;i++){
		if(Q[i].dpmx>ans){
			ans=Q[i].dpmx;
			res=Q[i].dpsh;
		}
		else if(Q[i].dpmx==ans){
			res=(res+Q[i].dpsh)%mod;
		}
	}
	cout<<ans<<endl;
	cout<<res<<endl;
    return 0;
}