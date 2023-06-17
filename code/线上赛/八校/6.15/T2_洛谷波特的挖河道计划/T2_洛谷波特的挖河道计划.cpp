#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
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
const int N=1e4+5;
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
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
struct xianh{
    int x1,y1,x2,y2;
}xdh[N];
bool operator <(const xianh &x,const xianh &y){
    return (x.y1==y.y1)?x.x1<y.x1:x.y1<y.y1;
}
int toth;
struct xians{
    int x1,y1,x2,y2;
}xds[N];
bool operator <(const xians &x,const xians &y){
    return (x.x1==y.x1)?x.y1<y.y1:x.x1<y.x1;
}
int tots;
int tot;
int du[N];
struct dian{
    int x,y;
};
struct bian{
    int dao,fan;
};
bool operator <(const dian &x,const dian &y){
    return (x.x==y.x)?x.y<y.y:x.x<y.x;
}
dian ys[N];
vector <bian> you[N];
int vis[N][3];
map <dian,int> mp;
int ans[N];
signed main(){
    freopen("bot.in","r",stdin);
    freopen("bot.out","w",stdout);
	int n=read();
    for(int i=1;i<=n;i++){
        int x1=read(),y1=read(),x2=read(),y2=read();
        if(x1==x2){
            if(y1==y2)continue;
            if(y1>y2)swap(y1,y2);
            xds[++tots]={x1,y1,x2,y2};
        }
        else{
            if(x1==x2)continue;
            if(x1>x2)swap(x1,x2);
            xdh[++toth]={x1,y1,x2,y2};
        }
    }
    sort(xds+1,xds+tots+1);
    sort(xdh+1,xdh+toth+1);
    int re=1;
    for(int i=2;i<=toth;i++){
        if(xdh[i].y1==xdh[re].y1&&xdh[i].x1==xdh[re].x2){
            xdh[re].x2=xdh[i].x2;
        }
        else xdh[++re]=xdh[i];
    }
    if(toth==0)re=0;
    toth=re;
    re=1;
    for(int i=2;i<=tots;i++){
        if(xds[i].x1==xds[re].x1&&xds[i].y1==xds[re].y2){
            xds[re].y2=xds[i].y2;
        }
        else xds[++re]=xds[i];
    }
    if(tots==0)re=0;
    tots=re;
    // cout<<tots<<endl;
    // for(int i=1;i<=tots;i++){
    //     cout<<xds[i].x1<<" "<<xds[i].y1<<" "<<xds[i].x2<<" "<<xds[i].y2<<endl;
    // }
    // cout<<toth<<endl;
    // for(int i=1;i<=toth;i++){
    //     cout<<xdh[i].x1<<" "<<xdh[i].y1<<" "<<xdh[i].x2<<" "<<xdh[i].y2<<endl;
    // }
    for(int i=1;i<=toth;i++){
        if(!mp[{xdh[i].x1,xdh[i].y1}])mp[{xdh[i].x1,xdh[i].y1}]=++tot,ys[tot]={xdh[i].x1,xdh[i].y1};
        du[mp[{xdh[i].x1,xdh[i].y1}]]++;
        if(!mp[{xdh[i].x2,xdh[i].y2}])mp[{xdh[i].x2,xdh[i].y2}]=++tot,ys[tot]={xdh[i].x2,xdh[i].y2};
        du[mp[{xdh[i].x2,xdh[i].y2}]]++;
        you[mp[{xdh[i].x1,xdh[i].y1}]].push_back({mp[{xdh[i].x2,xdh[i].y2}],(int)you[mp[{xdh[i].x2,xdh[i].y2}]].size()});
        you[mp[{xdh[i].x2,xdh[i].y2}]].push_back({mp[{xdh[i].x1,xdh[i].y1}],(int)you[mp[{xdh[i].x1,xdh[i].y1}]].size()-1});
    }
    for(int i=1;i<=tots;i++){
        if(!mp[{xds[i].x1,xds[i].y1}])mp[{xds[i].x1,xds[i].y1}]=++tot,ys[tot]={xds[i].x1,xds[i].y1};
        du[mp[{xds[i].x1,xds[i].y1}]]++;
        if(!mp[{xds[i].x2,xds[i].y2}])mp[{xds[i].x2,xds[i].y2}]=++tot,ys[tot]={xds[i].x2,xds[i].y2};
        du[mp[{xds[i].x2,xds[i].y2}]]++;
        you[mp[{xds[i].x1,xds[i].y1}]].push_back({mp[{xds[i].x2,xds[i].y2}],(int)you[mp[{xds[i].x2,xds[i].y2}]].size()});
        you[mp[{xds[i].x2,xds[i].y2}]].push_back({mp[{xds[i].x1,xds[i].y1}],(int)you[mp[{xds[i].x1,xds[i].y1}]].size()-1});
    }
    int cnt=0;
    for(int i=1;i<=tot;i++){
        if(du[i]&1)cnt++;
    }
    if(cnt>2){
        puts("0");
        return 0;
    }
    if(cnt==0){
        cout<<toth+tots+1<<endl;
        int now=1;
        cout<<ys[now].x<<" "<<ys[now].y<<endl;
        vis[now][0]=1;
        vis[you[now][0].dao][you[now][0].fan]=1;
        now=you[now][0].dao;
        while(now!=1){
            cout<<ys[now].x<<" "<<ys[now].y<<endl;
            for(int i=0;i<(int)you[now].size();i++){
                if(vis[now][i])continue;
                vis[now][i]=1;
                vis[you[now][i].dao][you[now][i].fan]=1;
                now=you[now][i].dao;
                break;
            }
        }
        cout<<ys[now].x<<" "<<ys[now].y<<endl;
        return 0;
    }
    int now=0;
    for(int i=1;i<=tot;i++){
        if(du[i]&1)now=i;
    }
    int res=0;
    ans[++res]=now;
    vis[now][0]=1;
    vis[you[now][0].dao][you[now][0].fan]=1;
    now=you[now][0].dao;
    while(!(du[now]&1)){
        ans[++res]=now;
        for(int i=0;i<(int)you[now].size();i++){
            if(vis[now][i])continue;
            vis[now][i]=1;
            vis[you[now][i].dao][you[now][i].fan]=1;
            now=you[now][i].dao;
            break;
        }
    }
    ans[++res]=now;
    cout<<res<<endl;
    for(int i=1;i<=res;i++){
        cout<<ys[ans[i]].x<<" "<<ys[ans[i]].y<<endl;
    }
	return 0;
}
/*
5
1 1 1 2 
1 3 1 5
1 6 1 5
1 3 1 2
1 6 1 10
*/