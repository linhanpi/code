/*
 * @Author: watering_penguin 
 * @Date: 2023-02-07 11:23:17 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-07 17:33:02
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
int a[N],b[N];
void ztef(int st,int en,int l,int r){
    if(l==r){
        for(int i=st;i<=en;i++)b[i]=l;
        return ;
    }
    if(st>en||l>r)return ;
    int mid=(l+r)>>1;
    int sum=0;
    for(int i=st;i<=en;i++)sum+=abs(mid-a[i]-1);
    int minn=sum,pos=st-1;
    for(int i=st;i<=en;i++){
        if(a[i]>=mid+1)sum++;
        else sum--;
        if(sum<minn){
            minn=sum;
            pos=i;
        }
    }
    ztef(st,pos,l,mid);
    ztef(pos+1,en,mid+1,r);
    return ;
}
signed main(){
    int n=read();
    for(int i=1;i<=n;i++)a[i]=read()-i;
    ztef(1,n,0,2e9);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=abs(a[i]-b[i]);
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        cout<<b[i]+i<<" ";
    }
    cout<<endl;
    return 0;
}