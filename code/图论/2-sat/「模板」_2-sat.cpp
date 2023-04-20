/*
 * @Author: watering_penguin 
 * @Date: 2023-03-02 15:41:42 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-11 14:33:10
 */
#include<bits/stdc++.h>
#define int long long//信仰
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
const int N=2e6+5;
const int M=1e2+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
    x%=mod;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
inline int fang(int x) {return x*x;}
int n;
vector <int> v[N],scc[N];
int low[N],dfn[N],ins[N],c[N],sta[N];
int cnt,top,num;
void tarjan(int now){
    low[now]=dfn[now]=++num;
    sta[++top]=now;
    ins[now]=1;
    for(int y:v[now]){
        if(!dfn[y]){
            tarjan(y);
            low[now]=min(low[now],low[y]);
        }
        else if(ins[y])low[now]=min(low[now],low[y]);
    }
    if(dfn[now]==low[now]){
        ++cnt;int y;
        do{
            y=sta[top--];
            ins[y]=0;
            scc[cnt].push_back(y);
            c[y]=cnt;
        }while(y!=now);
    }
    return ;
}
signed main(){
	int n=read(),m=read();
    for(int i=1;i<=m;i++){
        int x=read(),a=read(),y=read(),b=read();
        v[x+n*a].push_back(y+n*(b^1));
        v[y+n*b].push_back(x+n*(a^1));
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i])tarjan(i);
    }
    for(int i=1;i<=n;i++){
        if(c[i]==c[i+n]){
            puts("IMPOSSIBLE");
            return 0;
        }
    }
    puts("POSSIBLE");
    for(int i=1;i<=n;i++){
        cout<<(c[i]<c[i+n])<<" ";
    }
    return 0;
}
