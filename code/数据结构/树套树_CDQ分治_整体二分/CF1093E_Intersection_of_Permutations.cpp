/*
 * @Author: watering_penguin 
 * @Date: 2023-02-18 14:55:00 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-18 15:51:58
 */
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
const int N=12e5+5;
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
int n,m,cnt,tot;
int c[N];
void add(int x,int y){
    for(int i=x+1;i<=n+1;i+=lowbit(i)){
        c[i]+=y;
    }
    return ;
}
int cha(int x){
    int res=0;
    for(int i=x+1;i;i-=lowbit(i)){
        res+=c[i];
    }
    return res;
}
int cx(int l,int r){
    return cha(r)-cha(l-1);
}
struct node{
    int op,l,r,c,i,k;
}Q[N];
int ans[N];
bool operator <(const node &x,const node &y){
    if(x.c!=y.c)return x.c<y.c;
    return x.r<y.r;
}
void cdq(int l,int r){
    if(l==r)return ;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    sort(Q+l,Q+mid+1);
    sort(Q+mid+1,Q+r+1);
    int i=l,j=mid+1;
    for(;j<=r;j++){
        while(i<=mid&&Q[i].c<=Q[j].c){
            if(Q[i].op)add(Q[i].l,Q[i].k);
            ++i;
        }
        if(!Q[j].op)ans[Q[j].i]+=cx(Q[j].l,Q[j].r)*Q[j].k;
    }
    for(int k=l;k<i;k++){
        if(Q[k].op)add(Q[k].l,-Q[k].k);
    }
    return ;
}
int a[N],pos[N],b[N];
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
    for(int i=1;i<=n;i++)b[i]=pos[read()],Q[++cnt]={1,i,i,b[i],0,1};
    for(int i=1;i<=m;i++){
        int op=read();
        if(op==1){
            int l1=read(),r1=read(),l2=read(),r2=read();
            Q[++cnt]={0,l2,r2,r1,++tot,1};
            Q[++cnt]={0,l2,r2,l1-1,tot,-1};
        }
        else{
            int x=read(),y=read();
            Q[++cnt]={1,x,x,b[x],0,-1};
            Q[++cnt]={1,y,y,b[y],0,-1};
            swap(b[x],b[y]);
            Q[++cnt]={1,x,x,b[x],0,1};
            Q[++cnt]={1,y,y,b[y],0,1};
        }
    }
    cdq(1,cnt);
    for(int i=1;i<=tot;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}