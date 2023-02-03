/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:51:36 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:51:36 
 */
#include<bits/stdc++.h>
//#define int long long
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
const int N=5e4+5;
const int M=26;
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;
const double eps=1e-6;
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
struct st{
	int ji[31],l,r,cnt;
	st(){
		memset(ji,0,sizeof(ji));
		l=r=0;
	}
	void jia(int x){
        if(cnt==31)return ;
		if(!x)return ;
		for(int i=30;~i;i--){
			if(x&(1<<i)){
				if(ji[i])x^=ji[i];
				else{
					ji[i]=x;
                    cnt++;
					return ;
				}
				if(!x)return ;
			}
		}
		return ;
	}
	int maxji(int x){
		for(int i=30;~i;i--){
			if((x^ji[i])>x)x^=ji[i];
		}
		return x;
	}
	#define l(p) tree[p].l
	#define r(p) tree[p].r
}tree[N*4];
void hb(st x,st y,st &z){
	memcpy(z.ji,x.ji,sizeof(z.ji));
    z.cnt=x.cnt;
	for(int i=30;~i;i--){
		z.jia(y.ji[i]);
	}
	return ;
}
void hb2(st x,st &y){
	for(int i=30;~i;i--){
		y.jia(x.ji[i]);
	}
	return ;
}
void pu(int p){
	hb(tree[lson],tree[rson],tree[p]);
	return ;
}
void bt(int p,int l,int r){
	l(p)=l,r(p)=r;
	if(l==r){
		return ;
	}
	int mid=(l+r)>>1;
	bt(lson,l,mid);
	bt(rson,mid+1,r);
	return ;
}
void cg(int p,int pos,int x){
    // tree[p].jia(x);
	if(l(p)==r(p)){
        // memset(tree[p].ji,0,sizeof(tree[p].ji));
        tree[p].jia(x);
        return ;
    }
	int mid=(l(p)+r(p))>>1;
	if(pos<=mid)cg(lson,pos,x);
	else cg(rson,pos,x);
	pu(p);
	return ;
}
st ans;
void ask(int p,int L,int R){
	if(L<=l(p)&&r(p)<=R){
		hb2(tree[p],ans);
		return ;
	}
	int mid=(l(p)+r(p))>>1;
	if(L<=mid)ask(lson,L,R);
	if(R>mid)ask(rson,L,R);
	return ;
}
signed main(){
    int Q=read(),n=read();
    // for(int i=1;i<=n;i++)a[i]=read();
    bt(1,1,n);
//    for(int i=0;i<=30;i++){
//    	cout<<"i "<<i<<" "<<tree[1].ji[i]<<endl;
//	}
    while(Q--){
    	int opt=read(),k=read(),v=read();
    	if(opt==1){
    		cg(1,k,v);
		}
		else{
			memset(ans.ji,0,sizeof(ans.ji));
            ans.cnt=0;
			ask(1,k,v);
			write(ans.maxji(0));
			puts("");
		}
		// for(int i=25;i<=30;i++){
   		//     cout<<"i "<<i<<" "<<tree[1].ji[i]<<endl;
		// }
        // for(int i=25;i<=30;i++){
   		//     cout<<" 2222 "<<"i "<<i<<" "<<tree[3].ji[i]<<endl;
		// }
	}
	return 0;
}
/*
*/