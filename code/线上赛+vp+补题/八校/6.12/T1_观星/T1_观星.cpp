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
const int N=3e3+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e18;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-10;
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
struct diandata{
    int x,y;
};
bool operator <(const diandata &x,const diandata &y){
    return (x.x==y.x)?x.y<y.y:x.x<y.x;
}
vector <diandata> dian[3];
ld xies(int i,int j){
    if(dian[0][i].x==dian[0][j].x)return inf;
    return (ld)(dian[0][i].y-dian[0][j].y)/(dian[0][i].x-dian[0][j].x);
}
ld xiex(int i,int j){
    if(dian[0][i].x==dian[0][j].x)return inf;
    return (ld)(dian[0][i].y-dian[0][j].y)/(dian[0][i].x-dian[0][j].x);
}
ld xie(int x1,int x2,int y1,int y2){
    if(x1==x2)return inf;
    return (ld)(y1-y2)/(x1-x2);
}
inline ld S(int x1,int x2,int x3,int y1,int y2,int y3){
    return fabs((ld)0.5*((ld)x1*y2-x1*y3+x2*y3-x2*y1+x3*y1-x3*y2));
}
int qs[N],qx[N],tops,topx;
inline void pt(diandata x){
    cout<<x.x<<" "<<x.y<<" ";
    return ;
}
signed main(){
//    freopen("star.in","r",stdin);
//    freopen("star.out","w",stdout);
	int T=read();
    while(T--){
        dian[0].clear(),dian[1].clear(),dian[2].clear();
        memset(qs,0,sizeof(qs));
        memset(qx,0,sizeof(qx));
        tops=topx=0;
        int n=read();
        for(int i=1;i<=n;i++){
            int u=read(),v=read(),c=read();
            dian[c].push_back({u,v});
        }
        sort(dian[0].begin(),dian[0].end());
        for(int i=0;i<dian[0].size();i++){
            while(tops>1&&xiaoyu(xies(qs[tops],qs[tops-1]),xies(qs[tops-1],i)))tops--;
            qs[++tops]=i;
            while(topx>1&&dayu(xiex(qx[topx],qx[topx-1]),xiex(qx[topx-1],i)))topx--;
            qx[++topx]=i;
        }
        // for(int i=1;i<=tops;i++){
        //     pt(dian[0][qs[i]]);
        // }
        // cout<<endl;
        ld ans=0;
        for(int i=0;i<dian[1].size();i++){
            for(int j=0;j<dian[2].size();j++){
                ld xl=xie(dian[1][i].x,dian[2][j].x,dian[1][i].y,dian[2][j].y);
                int l=1,r=tops;
                while(l<r){
                    int mid=(l+r)>>1;
                    if(dayu(xies(qs[mid],qs[mid+1]),xl))l=mid+1;
                    else r=mid;
                }
                l=qs[l];
                // cout<<"xl "<<xl<<" ";pt(dian[1][i]);pt(dian[2][j]);pt(dian[0][l]);cout<<"S "<<S(dian[1][i].x,dian[2][j].x,dian[0][l].x,dian[1][i].y,dian[2][j].y,dian[0][l].y)<<endl;
                ld res=S(dian[1][i].x,dian[2][j].x,dian[0][l].x,dian[1][i].y,dian[2][j].y,dian[0][l].y);
                if(dayu(res,ans))ans=res;
                l=1,r=topx;
                while(l<r){
                    int mid=(l+r)>>1;
                    if(xiaoyu(xiex(qx[mid],qx[mid+1]),xl))l=mid+1;
                    else r=mid;
                }
                l=qx[l];
                res=S(dian[1][i].x,dian[2][j].x,dian[0][l].x,dian[1][i].y,dian[2][j].y,dian[0][l].y);
                if(dayu(res,ans))ans=res;
                // cout<<"xl "<<xl<<" ";pt(dian[1][i]);pt(dian[2][j]);pt(dian[0][l]);cout<<"S "<<S(dian[1][i].x,dian[2][j].x,dian[0][l].x,dian[1][i].y,dian[2][j].y,dian[0][l].y)<<endl;
            }
        }
        printf("%.1LF\n",ans);
    }
	return 0;
}
/*
2
8
3 1 0
-5 3 0
-1 1 1
-1 -1 0
-2 1 0
2 -4 0
1 1 0
7 7 2
17
-5 1 0
-4 1 0
-3 1 0
-2 1 0
-1 1 0
0 1 0
1 1 0
2 1 0
3 1 0
4 1 0
5 1 0
-2 3 1
-4 2 1
7 5 1
9 1 2
7 3 2
-1 3 2
*/
