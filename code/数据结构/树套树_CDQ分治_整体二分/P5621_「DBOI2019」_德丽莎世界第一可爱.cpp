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
struct node{
    int a,b,c,d,i,op;
    int dp,val;
}Q[N],tmp[N];
bool operator == (const node &x,const node &y){
    return x.a==y.a&&x.b==y.b&&x.c==y.c&&x.d==y.d;
}
bool cmp1(node a,node b){
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
    if(a.c!=b.c) return a.c<b.c;
    return a.d<b.d;
}
bool cmp2(node a,node b){
    if(a.b!=b.b) return a.b<b.b;
    if(a.c!=b.c) return a.c<b.c;
    if(a.d!=b.d) return a.d<b.d;
    return a.a<b.a;
}
bool cmp3(node a,node b){
    if(a.c!=b.c) return a.c<b.c;
    if(a.d!=b.d) return a.d<b.d;
    if(a.a!=b.a) return a.a<b.a;
    return a.b<b.b;
}
int c[N];
int n,len;
inline void add(int x,int y){
    for(int i=x;i<=n;i+=lowbit(i)){
        c[i]=max(c[i],y);
    }
    return ;
}
inline int ask(int x){
    int res=-inf;
    for(int i=x;i;i-=lowbit(i)){
        res=max(res,c[i]);
    }
    return res;
}
inline void cl(int x){
    for(int i=x;i<=n;i+=lowbit(i)){
        c[i]=0;
    }
    return ;
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
            if(Q[j].op)add(Q[j].d,Q[j].dp);
            ++j;
        }
        if(!Q[i].op)Q[i].dp=max(Q[i].dp,ask(Q[i].d)+Q[i].val);
    }
    for(int i=l;i<j;i++)if(Q[i].op)cl(Q[i].d);
    for(int i=l;i<=r;i++)tmp[pos2[Q[i].i]]=Q[i];
    for(int i=l;i<=r;i++)Q[i]=tmp[i];
    cdq2(mid+1,r);
    return ;
}
void cdq1(int l,int r){
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
    n=read();
    for(int i=1;i<=n;i++){
        Q[i].a=read(),Q[i].b=read(),Q[i].c=read(),Q[i].d=read(),Q[i].val=read();
        d[i]=Q[i].d;
    }
    sort(d+1,d+n+1);
    len=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++)Q[i].d=lower_bound(d+1,d+len+1,Q[i].d)-d;
    sort(Q+1,Q+n+1,cmp1);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(Q[i]==Q[i-1]){
            Q[cnt].val+=max(0ll,Q[i].val);
        }
        else{
            Q[++cnt]=Q[i];
        }
    }
    for(int i=1;i<=n;i++){
        Q[i].dp=Q[i].val,Q[i].i=i,pos1[i]=i;
    }
    cdq1(1,n);
    int ans=-inf;
    for(int i=1;i<=n;i++){
        ans=max(ans,Q[i].dp);
    }

    cout<<ans<<endl;
    return 0;
}