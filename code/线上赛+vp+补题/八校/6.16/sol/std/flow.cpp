#include<bits/stdc++.h>
#define pb push_back
#define cs const
#define poly vector<int>
#define fi first
#define se second
#define mkp make_pair
using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
cs int N = 4e4 + 50, K = 10;
cs int M = 1e7;
int n, k; char S[N][K][K];
int fi[M], nxt[M], to[M], w[M], ec=1;
void add(int x, int y, int z){
    nxt[++ec]=fi[x],fi[x]=ec,to[ec]=y,w[ec]=z;
    nxt[++ec]=fi[y],fi[y]=ec,to[ec]=x,w[ec]=0;
}
int idx(int x, int y, int t){ return x*(k<<1)+k*t+y; }
bool in[N][K];
int flow(int x, int y){
    int S=idx(x,y,0);
    queue<int> q; q.push(S);
    static int vis[M], TIME;
    ++TIME; vis[S]=TIME;
    static int frm[M],frms[M];
    int T=0;
    while(!q.empty()){
        int x=q.front(); q.pop();
        if(x%(k<<1)>=k&&x>T)T=x;
        for(int e=fi[x],v;e;e=nxt[e])
        if(w[e]&&vis[v=to[e]]!=TIME){
            if(v/(k<<1)<S/(k<<1))continue;
            vis[v]=TIME;frm[v]=x;frms[v]=e;q.push(v);
        }
    } if(!T)return 0; int u=T; while(u!=S){
        --w[frms[u]];++w[frms[u]^1];
        if(frm[u]/(k<<1)==u/(k<<1)){
            int t=u<frm[u]?u:frm[u];
            in[t/(k<<1)][t%(k<<1)]^=1;
        } u=frm[u];
    } return T/(k<<1)-S/(k<<1);
}
int main(){
  
    freopen("flow.in","r",stdin);
    freopen("flow.out","w",stdout);
    
    scanf("%d%d",&n,&k);
    for(int i=1; i<n; i++)
    for(int j=0; j<k; j++)
    scanf("%s",S[i][j]);
    for(int i=1; i<=n; i++)
    for(int j=0; j<k; j++)
    add(idx(i,j,0),idx(i,j,1),1);
    for(int i=1; i<n; i++)
    for(int j=0; j<k; j++)
    for(int l=0; l<k; l++)
    if(S[i][j][l]=='1')
    add(idx(i,j,1),idx(i+1,l,0),1);
    ll ans = 0, sm = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<k; j++)
        sm -= in[i][j];
        for(int j=0; j<k; j++)
        if(!in[i][j]) sm += flow(i,j);
        ans += sm;
    } cout << ans;
    return 0;
}
