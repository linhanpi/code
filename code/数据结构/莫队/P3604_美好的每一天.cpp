/*
 * @Author: watering_penguin 
 * @Date: 2023-02-09 09:24:10 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-09 11:48:39
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
const int N=6e4+5;
const int M=(1<<26)+5;
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
struct node{
    int l,r,i;
}no[N];
int kuaichang;
bool operator <(const node &x,const node &y){
    if(x.l/kuaichang==y.l/kuaichang){
        return ((x.l/kuaichang)&1)?x.r>y.r:x.r<y.r;
    }
    return x.l<y.l;
}
char a[N];
int sum[N],tong[M],ans,res[N];
void jia(int x){
    ans+=tong[sum[x]];
    for(int i=0;i<26;i++){
        ans+=tong[sum[x]^(1<<i)];
    }
    tong[sum[x]]++;
    return ;
}
void jian(int x){
    tong[sum[x]]--;
    ans-=tong[sum[x]];
    for(int i=0;i<26;i++){
        ans-=tong[sum[x]^(1<<i)];
    }
    return ;
}
signed main(){
    int n=read(),m=read();
    kuaichang=sqrt(m);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]^(1<<(a[i]-'a'));
    }
    for(int i=1;i<=m;i++){
        no[i].l=read()-1,no[i].r=read(),no[i].i=i;
    }
    sort(no+1,no+m+1);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l>no[i].l)jia(--l);
        while(r<no[i].r)jia(++r);
        while(l<no[i].l)jian(l++);
        while(r>no[i].r)jian(r--);
        res[no[i].i]=ans;
    }
    for(int i=1;i<=m;i++){
        cout<<res[i]<<endl;
    }
    return 0;
}