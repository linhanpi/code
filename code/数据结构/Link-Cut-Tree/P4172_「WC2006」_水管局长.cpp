/*
 * @Author: watering_penguin 
 * @Date: 2023-02-07 11:23:17 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-07 17:33:02
 */
#include<bits/stdc++.h>
#define int long long
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
const int N=1e6+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=51061;
const double eps=1e-6;
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
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
int f[N],son[N][2],si[N],val[N],maxn[N],sw[N];
struct node{
    int a,b,w;
}bian[N];
struct cha{
    int op,x,y,flag;
}Q[N];
bool operator <(const node &x,const node &y){
    return x.w<y.w;
}
bool nroot(int now){
    return son[f[now]][0]==now||son[f[now]][1]==now;
}
inline int maxer(int x,int y){
    return bian[x].w>bian[y].w?x:y;
}
inline void pu(int x){
    maxn[x]=val[x];
    maxn[x]=maxer(maxn[x],maxn[son[x][0]]);
    maxn[x]=maxer(maxn[x],maxn[son[x][1]]);
    return ;
}
void pdsw(int now){
    swap(son[now][0],son[now][1]);
    sw[now]^=1;
    return ;
}
void pd(int now){
    if(sw[now]){
        if(son[now][0])pdsw(son[now][0]);
        if(son[now][1])pdsw(son[now][1]);
        sw[now]=0;
    }
    return ;
}
void rotate(int now){
    int fa=f[now],gfa=f[fa],k=(son[fa][1]==now),w=son[now][k^1];
    if(nroot(fa))son[gfa][son[gfa][1]==fa]=now;
    son[now][k^1]=fa,son[fa][k]=w;
    if(w)f[w]=fa;
    f[now]=gfa,f[fa]=now;
    pu(fa);
    return ;
}
int st[N],top;
void splay(int now){
    int y=now;
    top=0;
    st[++top]=y;
    while(nroot(y))st[++top]=y=f[y];
    while(top)pd(st[top--]);
    while(nroot(now)){
        int fa=f[now],gfa=f[fa];
        if(nroot(fa)){
            rotate((son[fa][1]==now)^(son[gfa][1]==fa)?now:fa);
        }
        rotate(now);
    }
    pu(now);
    return ;
}
void acc(int x){
    for(int y=0;x;x=f[y=x]){
        splay(x),son[x][1]=y,pu(x);
    }
    return ;
}
void mr(int x){
    acc(x);splay(x);pdsw(x);
    return ;
}
void lian(int x,int y){
    mr(x);
    acc(y);
    splay(y);
    return ;
}
void link(int x,int y){
    lian(x,y);
    f[x]=y;
    pu(y);
    return ;
}
void cut(int x,int y){
    lian(x,y);
    f[x]=son[y][0]=0;
    pu(y);
    return ;
}
int fr(int x){
    acc(x);
    splay(x);
    pd(x);
    while(son[x][0]){
        pd(x);
        if(!son[x][0])break;
        x=son[x][0];
    }
    splay(x);
    return x;
}
void init(int x,int y){
    f[x]=son[x][0]=son[x][1]=sw[x]=0;
    maxn[x]=y,val[x]=y;
    return ;
}
map <pii,int> id;
bool vis[N];
int ans[N];
signed main(){
    int n=read(),m=read(),q=read();
    for(int i=1;i<=m;i++){
        bian[i].a=read(),bian[i].b=read(),bian[i].w=read();
        if(bian[i].a>bian[i].b)swap(bian[i].a,bian[i].b);
    }
    sort(bian,bian+m+1);
    for(int i=1;i<=m;i++)id[{bian[i].a,bian[i].b}]=i;
    for(int i=1;i<=q;i++){
        Q[i].op=read(),Q[i].x=read(),Q[i].y=read();
        if(Q[i].x>Q[i].y)swap(Q[i].x,Q[i].y);
        if(Q[i].op==2){
            int d=id[{Q[i].x,Q[i].y}];
            Q[i].flag=d;
            vis[d]=1;
        }
    }
    int cnt=0;
    bian[0].w=0;
    for(int i=1;i<=n+m;i++)init(i,i<=n?0:(i-n));
    for(int i=1;i<=m;i++){
        if(vis[i])continue;
        if(cnt==n-1)break;
        int x=bian[i].a,y=bian[i].b;
        if(fr(x)==fr(y))continue;
        link(x,i+n);link(y,i+n);
        // cout<<"x y "<<x<<" "<<y<<endl;
        cnt++;
    }
    for(int i=q;i>=1;i--){
        int x=Q[i].x,y=Q[i].y;
        if(Q[i].op==1){
            lian(x,y);
            ans[i]=bian[maxn[y]].w;
            // cout<<"maxn "<<x<<" "<<y<<" "<<maxn[y]<<" "<<val[maxn[y]]<<endl;
        }
        else{
            lian(x,y);
            // cout<<"x y "<<x<<" "<<y<<endl;
            int d=Q[i].flag,t=maxn[y];
            // cout<<"d t "<<d<<" "<<t<<" "<<val[y]<<" "<<endl;
            if(bian[d].w<bian[t].w){
                cut(bian[t].a,t+n),cut(bian[t].b,t+n);
                link(x,d+n),link(y,d+n);
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(Q[i].op==1)write(ans[i]),puts("");
    }
    return 0;
}