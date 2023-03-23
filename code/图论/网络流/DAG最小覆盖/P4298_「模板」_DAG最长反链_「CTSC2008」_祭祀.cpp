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
const int N=205;
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
int deep[N],gap[N],nowhu[N];
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
bool ke[N][N];
void cl(){
    for(int i=1;i<=tot;i++)v[i].clear();
    tot=0;
    return ;
}
int ma[N];
bool vis[N],res[N];
int la[N];
signed main(){
    int n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a=read(),b=read();
        ke[a][b]=1;
    }
    for(int i=1;i<=n;i++)ke[i][i]=1;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                ke[i][j]|=ke[i][k]&&ke[k][j];
            }
        }
    }
    for(int i=1;i<=n;i++)ke[i][i]=0;
    tot=2*n;
    st=++tot,ed=++tot;
    int ans=n;
    for(int i=1;i<=n;i++){
        jiabian(st,i,1);
        jiabian(i+n,ed,1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ke[i][j])jiabian(i,j+n,1);
        }
    }
    ISAP();
    ans=n-maxflow;
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        for(int j=0;j<(int)v[i+n].size();j++){
            int y=v[i+n][j].dao;
            if(y==ed)continue;
            if(v[i+n][j].val)ma[i]=y,vis[y]=1;
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(!vis[i])la[++cnt]=i;
    }
    memset(vis,0,sizeof(vis));
    bool flag=1;
    while(flag){
        flag=0;
        for(int i=1;i<=ans;i++){
            for(int j=1;j<=n;j++){
                if(ke[la[i]][j])vis[j]=1;
            }
        }
        for(int i=1;i<=ans;i++){
            if(vis[la[i]]){
                flag=1;
                while(vis[la[i]])la[i]=ma[la[i]];
            }
        }
    }
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=ans;i++){
        vis[la[i]]=1;
    }
    for(int i=1;i<=n;i++){
        cout<<vis[i];
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        cl();
        memset(vis,0,sizeof(vis));
        tot=2*n;
        vis[i]=1;
        for(int j=1;j<=n;j++){
            if(ke[i][j]||ke[j][i])vis[j]=1;
        }
        cnt=0;
        st=++tot,ed=++tot;
        for(int k=1;k<=n;k++){
            if(vis[k])continue;
            cnt++;
            jiabian(st,k,1);
            jiabian(k+n,ed,1);
            for(int j=1;j<=n;j++){
                if(vis[j])continue;
                if(ke[k][j])jiabian(k,j+n,1);
            }
        }
        ISAP();
        if(cnt-maxflow==ans-1)res[i]=1;
    }
    for(int i=1;i<=n;i++){
        cout<<res[i];
    }
    cout<<endl;
    return 0;
}
