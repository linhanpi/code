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
const int N=2e4+5;
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
int n,m,st,ed,tot;
struct node{
    int dao,val,fan;
};
vector <node> v[N];
inline void jiabian(int a,int b,int w){
    v[a].push_back({b,w,(int)v[b].size()});
    v[b].push_back({a,0,(int)v[a].size()-1});
    return ;
}
int deep[N],gap[N],nowhu[N],d[N];
int maxflow;
void bfs(){
    memset(deep,-1,sizeof(deep));
    memset(gap,0,sizeof(gap));
    deep[ed]=0;
    gap[0]=1;
    queue <int> q;
    q.push(ed);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<(int)v[now].size();i++){
            int y=v[now][i].dao;
            if(~deep[y])continue;
            q.push(y);
            deep[y]=deep[now]+1;
            gap[deep[y]]++;
        }
    } 
    return ;
}
int dfs(int now,int flow){
    if(now==ed){
        maxflow+=flow;
        return flow;
    }
    int used=0;
    for(int i=nowhu[now];i<(int)v[now].size();i++){
        nowhu[now]=i;
        int y=v[now][i].dao;
        if(v[now][i].val&&deep[y]+1==deep[now]){
            int maxn=dfs(y,min(v[now][i].val,flow-used));
            if(maxn){
                v[now][i].val-=maxn;
                v[y][v[now][i].fan].val+=maxn;
                used+=maxn;
            }
            if(used==flow)return used;
        }
    }
    --gap[deep[now]];
    if(!gap[deep[now]])deep[st]=tot+1;
    deep[now]++;
    gap[deep[now]]++;
    return used;
}
void ISAP(){
    maxflow=0;
    bfs();
    while(deep[st]<tot)memset(nowhu,0,sizeof(nowhu)),dfs(st,inf);
    return ;
}
int A[N],B[N],bh[N],L[N];
signed main(){
    n=read(),m=read();
    tot=n;
    st=++tot,ed=++tot;
    for(int i=1;i<=m;i++){
        int a=read(),b=read(),l=read(),r=read();
        d[a]-=l,d[b]+=l;
        jiabian(a,b,r-l);
        bh[i]=v[a].size()-1;
        A[i]=a;
        B[i]=b;
        L[i]=l;
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        if(d[i]>0)jiabian(st,i,d[i]),sum+=d[i];
        else if(d[i]<0)jiabian(i,ed,-d[i]);
    }
    // cout<<1<<endl;
    ISAP();
    // cout<<2<<endl;
    // cout<<maxflow<<endl;
    if(maxflow!=sum){
        puts("NO");
        return 0;
    }
    puts("YES");
    for(int i=1;i<=m;i++){
        cout<<v[B[i]][v[A[i]][bh[i]].fan].val+L[i]<<endl;
    }
    return 0;
}
