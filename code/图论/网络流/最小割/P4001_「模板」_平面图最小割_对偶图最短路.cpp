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
const int M=6e4+5;
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
struct node{
    int dao,quan; 
};
vector <node> v[N];
int n,m,st,ed;
int haxi(int a,int b){
    return a*(m*2)+b;
}
void jiabian(int a,int b,int w){
    v[a].push_back({b,w});
    v[b].push_back({a,w});
    return;
}
int dist[N],in[N];
void spfa(){
    memset(dist,0x3f,sizeof(dist));
    queue <int> q;
    q.push(st);
    dist[st]=0;
    in[st]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        in[now]=0;
        for(int i=0;i<(int)v[now].size();i++){
            int y=v[now][i].dao,w=v[now][i].quan;
            if(dist[y]<=dist[now]+w)continue;
            dist[y]=dist[now]+w;
            if(!in[y])in[y]=1,q.push(y);
        }
    }
    return ;
}
signed main(){
    n=read(),m=read();
    if(n==1){
        int ans=inf;
        for(int i=1;i<m;i++){
            int a=read();
            ans=min(ans,a);
        }
        cout<<ans<<endl;
        return 0;
    }
    if(m==1){
        int ans=inf;
        for(int i=1;i<n;i++){
            int a=read();
            ans=min(ans,a);
        }
        cout<<ans<<endl;
        return 0;
    }
    st=haxi(0,0),ed=haxi(n+1,m+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int a=read();
            if(i==1)jiabian(haxi(i,j<<1),st,a);
            else if(i==n)jiabian(ed,haxi(i-1,(j<<1)-1),a);
            else jiabian(haxi(i-1,(j<<1)-1),haxi(i,j<<1),a);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int a=read();
            if(j==1)jiabian(haxi(i,(j<<1)-1),ed,a);
            else if(j==m)jiabian(st,haxi(i,(j-1)<<1),a);
            else jiabian(haxi(i,(j<<1)-1),haxi(i,(j-1)<<1),a);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            int a=read();
            jiabian(haxi(i,(j<<1)-1),haxi(i,j<<1),a);
        }
    }
    spfa();
    cout<<dist[ed]<<endl;
    return 0;
}
