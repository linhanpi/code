#include<bits/stdc++.h>
#define int long long
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
const int N=1e7+5;
const int M=(1<<12);
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
inline int qmi(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x;
        x=x*x;
        y>>=1;
    }
    return ans;
}
int p[N],tot,vis[N],miu[N];
inline void ycl(){
    miu[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!vis[i])p[++tot]=i,miu[i]=-1;
        for(int j=1;j<=tot&&i*p[j]<=N-5;j++){
            vis[i*p[j]]=p[j];
            if(i%p[j]==0){
                break;
            }
            miu[i*p[j]]=-miu[i];
        }
    }
    return ;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
int a[N];
signed main(){
    ycl();
	int T=read();
    while(T--){
        int n=read(),ans=0;
        for(int i=1;i*i<=n;i++){
            ans+=miu[i]*(n/(i*i));
        }
        cout<<ans<<endl;
    }
    return 0;
}
/*
ababbab
aba
1
*/