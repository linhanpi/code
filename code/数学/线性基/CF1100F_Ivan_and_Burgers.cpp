#include<bits/stdc++.h>
// #define int long long
//#define double long double
//#define pii pair <int,int>
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
const int M=(1<<12);
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;
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
	int ji[61],pos[61];
	node(){
		memset(ji,0,sizeof(ji));
		memset(pos,0,sizeof(pos));
	}
	void add(int x,int po){
		for(int i=30;i>=0;i--){
			if(x&(1<<i)){
				if(pos[i]<po){
					swap(ji[i],x);
					swap(pos[i],po);
				}
				x^=ji[i];
			}
		}
		return ;
	}
	int maxji(int l){
		int ans=0;
		for(int i=30;i>=0;i--){
			if(pos[i]>=l){
				if((ans^ji[i])>ans)ans^=ji[i];
			}
		}
		return ans;
	}
}ji[N];
signed main(){
	int n=read();
	for(int i=1;i<=n;i++){
		ji[i]=ji[i-1];
		a[i]=read();
		ji[i].add(a[i],i);
	}
	// for(int i=0;i<=5;i++){
	// 	cout<<"i "<<i<<" "<<ji[3].ji[i]<<" "<<ji[3].pos[i]<<endl;
	// }
	int q=read();
	while(q--){
		int l=read(),r=read();
		cout<<ji[r].maxji(l)<<endl;
	}
	return 0;
}
/*
ababbab
aba
1
*/