#include<bits/stdc++.h>
#define int long long//信仰
#define ll long long
#define ld long double
#define ull unsigned long long
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
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=3e4+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}
vector <int> v[N];
int f[N];
int n,m,k;
int fa[N],son[N],tp[N],si[N],dep[N];
void dfs1(int now){
	int maxn=0;
	si[now]=1;
	dep[now]=dep[fa[now]]+1;
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i];
		if(y==fa[now])continue;
		fa[y]=now;
		dfs1(y);
		si[now]+=si[y];
		if(si[y]>maxn){
			maxn=si[y];
			son[now]=y;
		}
	}
	return ;
}
void dfs2(int now,int top){
	tp[now]=top;
	if(!son[now])return ;
	dfs2(son[now],top);
	for(int i=0;i<(int)v[now].size();i++){
		int y=v[now][i];
		if(y==fa[now]||y==son[now])continue;
		dfs2(y,y);
	}
	return ;
}
inline int cha(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])swap(x,y);
		x=fa[tp[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	return y;
}
vector <int> tu[N];
int cnt=0;
void dfss(int now){
    cnt++;
    for(int y:tu[now]){
        dfss(y);
    }
    return ;
}
int ans=0;
bool vis[N];
inline int lca(int x,int y){
    for(int i=1;i<=n+m;i++)vis[i]=0;
    while(x){
        vis[x]=1;
        x=f[x];
    }
    while(y){
        if(vis[y])return y;
        y=f[y];
    }
    return -1;
}
void dfs(int now){
    if(now==n+m+1){
        for(int i=1;i<=n+m;i++){
            tu[i].clear();
        }
        for(int i=1;i<=n+m;i++){
            tu[f[i]].push_back(i);
        }
        cnt=0;
        // for(int i=1;i<=n+m;i++){
        //     cout<<"i "<<i<<" "<<f[i]<<endl;
        // }
        dfss(1);
        if(cnt!=n+m){
            return ;
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(lca(i,j)!=cha(i,j))return ;
            }
        }
        for(int i=1;i<=n+m;i++){
            for(int j=max(i+1,n+1);j<=n+m;j++){
                if(lca(i,j)>j+k)return ;
            }
        }
        ans++;
        return ;
    }
    for(int i=1;i<=n+m;i++){
        if(f[i]==now)continue;
        f[now]=i;
        dfs(now+1);
        f[now]=0;
    }
    return ;
}
signed main(){
    // freopen("tree.in","r",stdin);
    // freopen("tree.out","w",stdout);
    int c=read(),T=read();
    // cout<<"c "<<c<<endl;
    while(T--){
        n=read(),m=read(),k=read();
        for(int i=1;i<=n;i++){
            v[i].clear();
        }
        for(int i=1;i<n;i++){
            int fa=read();
            v[fa].push_back(i+1);
        }
        if(c==3){
            puts("0");
            continue;
        }
        if(c<=2){
            // cout<<"222"<<endl;
            ans=0;
            dfs1(1);
            dfs2(1,1);
            dfs(2);
            cout<<ans<<endl;
            continue;
        }
        if(4<=c&&c<=5){
            cout<<2*n-1<<endl;
            continue;
        }
        if(6<=c&&c<=7){
            if(k==0){
                cout<<(2*n-1)*(2*(n+1)-1)<<endl;
            }
            else{
                cout<<(2*n-1)*(2*(n+1)-1)+(n-1)<<endl;
            }
            continue;
        }
        if(8<=c&&c<=10){
            int ans=1;
            for(int i=1;i<=m;i++){
                ans=ans*(2*i-1)%mod;
            }
            cout<<ans<<endl;
            continue;
        }
    }
	return 0;
}
/*
2 3
1 2 1

2 2 1
1
2 2 0
1

*/