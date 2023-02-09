/*
 * @Author: watering_penguin 
 * @Date: 2023-02-09 09:24:10 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-09 09:39:45
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
int a[N];
struct node{
    int l,r,i,op;
}no[N*4];
int cnt;
int kuaichang;
bool operator <(const node &x,const node &y){
    if(x.l/kuaichang==y.l/kuaichang){
        return ((x.l/kuaichang)&1)?x.r>y.r:x.r<y.r;
    }
    return x.l<y.l;
} 
int tong[N][2],ans;
void jia(int x,int k){
    ans+=tong[a[x]][k^1];
    tong[a[x]][k]++;
    return ;
}
void jian(int x,int k){
    ans-=tong[a[x]][k^1];
    tong[a[x]][k]--;
    return ;
}
int res[N];
signed main(){
    int n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    int q=read();
    kuaichang=sqrt(q);
    for(int i=1;i<=q;i++){
        int l1=read(),r1=read(),l2=read(),r2=read();
        no[++cnt]={l1-1,l2-1,i,1};
        no[++cnt]={r1,l2-1,i,-1};
        no[++cnt]={l1-1,r2,i,-1};
        no[++cnt]={r1,r2,i,1};
    }
    sort(no+1,no+cnt+1);
    int l=0,r=0;
    for(int i=1;i<=cnt;i++){
        while(l<no[i].l)jia(++l,0);
        while(l>no[i].l)jian(l--,0);
        while(r<no[i].r)jia(++r,1);
        while(r>no[i].r)jian(r--,1);
        res[no[i].i]+=no[i].op*ans;
    }
    for(int i=1;i<=q;i++){
        cout<<res[i]<<endl;
    }
    return 0;
}