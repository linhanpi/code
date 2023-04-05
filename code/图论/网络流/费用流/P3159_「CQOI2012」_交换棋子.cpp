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
const int N=25;
const int M=2*25*25;
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
    int dao,liu,fei,fan;
};
vector <node> v[M];
void jiabian(int x,int y,int w,int f){
    v[x].push_back({y,w,f,(int)v[y].size()});
    v[y].push_back({x,0,-f,(int)v[x].size()-1});
    return ;
}
int dist[M],in[M],nowhu[M];
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
    while(spfa()){
        memset(nowhu,0,sizeof(nowhu));
        int now=0;
        while(now=dfs(st,inf))maxflow+=now;
    }
    return ;
}
int qi[N][N],zhong[N][N],ci[N][N],vis[N][N];
int haxi1(int x,int y){
    return (x-1)*m+y;
}
int haxi2(int x,int y){
    return n*m+(x-1)*m+y;
}
signed main(){
    n=read(),m=read();
    tot=2*n*m;
    st=++tot,ed=++tot;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char ch;cin>>ch;
            qi[i][j]=ch-'0';
        }
    }
    int cnt1=0,cnt2=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char ch;cin>>ch;
            zhong[i][j]=ch-'0';
            if(qi[i][j]!=zhong[i][j])vis[i][j]=1;
        }
    }
    // cout<<"114514\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char ch;cin>>ch;
            ci[i][j]=ch-'0';
            if(vis[i][j]){
                if(ci[i][j]&1)ci[i][j]=ci[i][j]/2+1;
                else ci[i][j]/=2;
            }
            else ci[i][j]/=2;
            jiabian(haxi1(i,j),haxi2(i,j),ci[i][j],0);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(vis[i][j]&&qi[i][j]==0){
                cnt1++;
                jiabian(st,haxi1(i,j),1,0);
            }
            if(vis[i][j]&&qi[i][j]==1){
                cnt2++;
                jiabian(haxi2(i,j),ed,1,0);
            }
        }
    }
    // cout<<cnt1<<" "<<cnt2<<endl;
    if(cnt1!=cnt2){
        puts("-1");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i!=1)jiabian(haxi2(i,j),haxi1(i-1,j),inf,1);
            if(i!=n)jiabian(haxi2(i,j),haxi1(i+1,j),inf,1);
            if(j!=1)jiabian(haxi2(i,j),haxi1(i,j-1),inf,1);
            if(j!=m)jiabian(haxi2(i,j),haxi1(i,j+1),inf,1);
            if(i!=1&&j!=1)jiabian(haxi2(i,j),haxi1(i-1,j-1),inf,1);
            if(i!=1&&j!=m)jiabian(haxi2(i,j),haxi1(i-1,j+1),inf,1);
            if(i!=n&&j!=1)jiabian(haxi2(i,j),haxi1(i+1,j-1),inf,1);
            if(i!=n&&j!=m)jiabian(haxi2(i,j),haxi1(i+1,j+1),inf,1);
        }
    }
    Dinic();
    if(maxflow!=cnt1){
        puts("-1");
        return 0;
    }
    cout<<minfei<<endl;
    return 0;
}
/*
3 3
110
000
001
000
110
100
222
222
222
*/