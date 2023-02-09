/*
 * @Author: watering_penguin 
 * @Date: 2023-02-07 11:23:17 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-07 11:43:10
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

signed main(){
    int T=read();
    while(T--){
        int l=read(),r=read();
        int minn=inf,ans;
        while(l<=r){
            int tep=l,cnt=0;
            while(tep%10==0){
                tep/=10;
                ++cnt;
            }
            int mw=tep%10,len=0;
            while(tep){
                tep/=10,++len;
            }
            if(minn>(mw==5?2*len-1:2*len))minn=(mw==5?2*len-1:2*len),ans=l;
            l+=qmi(10,cnt,inf);
        }
        cout<<ans<<endl;
    }
    return 0;
}