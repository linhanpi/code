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
const int N=8e4+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=1e17+9;
const int base=131;
const int mod=1e17+7;
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
    int dao,liu,fei,fan;
};
vector <node> v[N];
void jiabian(int x,int y,int w,int f){
    v[x].push_back({y,w,f,(int)v[y].size()});
    v[y].push_back({x,0,-f,(int)v[x].size()-1});
    return ;
}
int dist[N],in[N],nowhu[N];
inline bool spfa(){
    for(int i=1;i<=tot;i++)dist[i]=inf;
    memset(in,0,sizeof(in));
    queue <int> q;
    q.push(st);
    dist[st]=0,in[st]=1;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        in[now]=0;
        for(int i=0;i<(int)v[now].size();i++){
            int y=v[now][i].dao;
            int liu=v[now][i].liu,fei=v[now][i].fei;
            if(dist[y]<=dist[now]+fei||!liu)continue;
            dist[y]=dist[now]+fei;
            if(!in[y])q.push(y),in[y]=1;
        }
    }
    return dist[ed]!=inf;
}
int maxflow,minfei;
int dfs(int now,int flow){
    if(now==ed)return flow;
    in[now]=1;
    int used=0;
    for(int i=nowhu[now];i<(int)v[now].size();i++){
        int y=v[now][i].dao;
        nowhu[now]=i;
        int liu=v[now][i].liu,fei=v[now][i].fei;
        if(in[y]||dist[y]!=dist[now]+fei||!liu)continue;
        int maxn=dfs(y,min(liu,flow-used));
        if(!maxn)dist[y]=inf;
        else minfei+=maxn*fei,v[now][i].liu-=maxn,v[y][v[now][i].fan].liu+=maxn,used+=maxn;
        if(used==flow)break;
    }
    in[now]=0;
    return used;
}
inline void Dinic(){
    maxflow=minfei=0;
    while(spfa()){
        memset(nowhu,0,sizeof(nowhu));
        maxflow+=dfs(st,inf);
    }
    return ;
}
int a[N],b[N],c[N],cnt[N];
bool ck(int mid){
    for(int i=1;i<=tot;i++)v[i].clear();
    tot=ed;
    int stt=++tot,edd=++tot;
    jiabian(st,stt,mid,0);
    jiabian(edd,ed,mid,0);
    for(int i=1;i<=n;i++){
        if(cnt[i]%2==1)jiabian(stt,i,b[i],0);
        else jiabian(i,edd,b[i],0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i]%a[j]==0&&cnt[i]==cnt[j]+1){
                if(cnt[i]%2==1)jiabian(i,j,inf,-c[i]*c[j]);
                else jiabian(j,i,inf,-c[i]*c[j]);
            }
        }
    }
    Dinic();
    // cout<<mid<<" "<<maxflow<<" "<<minfei<<endl;
    return minfei<=0;
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
		int l=a[i];
		for(int j=2;j<=l;j++){
            if(l%j==0)l=l/j,j--,cnt[i]++;
        }
	}
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++)c[i]=read();
    tot=n;
    st=++tot,ed=++tot;
    ck(1145141919);
    int l=0,r=maxflow,ans=0;
    // cout<<maxflow<<endl;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ck(mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans<<endl;
    return 0;
}
