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
const int N=4e5+5;
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
struct node{
    int op;
    ll x1,x2,y;
}l[N*2],xie[N];
bool operator <(const node &x,const node &y){
    return x.y<y.y;
}
struct xds_data{
    int l,r,cnt;
    ll sum;
    xds_data(){
        l=r=cnt=sum=0;
    }
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define cnt(p) tree[p].cnt
    #define sum(p) tree[p].sum
}tree[N<<3];
ll d[2*N],ans;
vector<int> v[N];
map<pii,int> mp;
void bd(int p,int l,int r){
    l(p)=l,r(p)=r;
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    bd(lson,l,mid);
    bd(rson,mid+1,r);
    return ;
}
void pu(int p){
    if(cnt(p)>0){
        sum(p)=d[r(p)+1]-d[l(p)];
    }
    else{
        sum(p)=sum(lson)+sum(rson);
    }
    return ;
}
void cg(int p,int L,int R,int v){
    if(L<=l(p)&&r(p)<=R){
        cnt(p)+=v;
        pu(p);
        return ;
    }
    int mid=(l(p)+r(p))>>1;
    if(L<=mid)cg(lson,L,R,v);
    if(R>mid)cg(rson,L,R,v);
    pu(p);
    return ;
}
signed main(){
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    int c=read(),n=read(),m=read(),q=read();
    int tot=0,cntx=0;
    for(int i=1;i<=q;i++){
        int op=read();
        long long x1=read(),y1=read(),x2=read(),y2=read();
        if(op==3){
			xie[++cntx].x1=x1,xie[cntx].x2=x2,xie[cntx].y=y1;
			continue;
		}
        ++tot;
        l[(tot<<1)-1].x1=x1,l[(tot<<1)-1].x2=x2,l[(tot<<1)-1].y=y1,l[(tot<<1)-1].op=1,d[(tot<<1)-1]=x1;
		l[(tot<<1)].x1=x1,l[(tot<<1)].x2=x2,l[(tot<<1)].y=y2,l[(tot<<1)].op=-1,d[(tot<<1)]=x2;
    }
    int cntt=0;
    do{
        cntt=0;
        for(int i=1;i<=cntx;i++){
            for(int j=1;j<=cntx;j++){
                if(j==i)continue;
                if((!xie[i].y)||(!xie[j].y))continue;
                if(xie[i].y-xie[i].x1!=xie[j].y-xie[j].x1)continue;
                if(xie[j].x1>=xie[i].x1&&xie[j].x2<=xie[i].x2||xie[i].x1<=xie[j].x1&&xie[j].x1<=xie[i].x2&&xie[i].x2<=xie[j].x2){
                    ++cntt;
                    xie[i].x1=min(xie[i].x1,xie[j].x1);
					xie[i].x2=max(xie[i].x2,xie[j].x2);
					xie[i].y=min(xie[i].y,xie[j].y);
					xie[j].y=0;
                }
            }
        }
    }while(cntt);
    for(int i=1;i<=cntx;i++){
        if(xie[i].y){
            ans+=xie[i].x2-xie[i].x1+1;
        }
    }
    // cout<<ans<<endl;
    int bh=0;
    for(int i=1;i<=2*tot;i+=2){
        if(l[i].y==l[i+1].y){
            if(!mp[{l[i].y,0}]){
                mp[{l[i].y,0}]=++bh;
            }
            v[mp[{0,l[i].y}]].push_back(i);
        }
        else if(l[i].x1==l[i].x2){
            if(!mp[{0,l[i].x1}]){
                mp[{0,l[i].x1}]=++bh;
            }
            v[mp[{0,l[i].x1}]].push_back(i);
        }
    }
    for(int i=1;i<=cntx;i++){
        if(!xie[i].y)continue;
        for(int j=1;j<=2*tot;j+=2){
            ll xx=l[j].y-xie[i].y+xie[i].x1;
            ll yy=l[j].x1+xie[i].y-xie[i].x1;
            if(l[j].x1==l[j].x2&&l[j].x1>=xie[i].x1&&l[j].x1<=xie[i].x2&&yy>=l[j].y&&yy<=l[j+1].y){
				if(!mp[{l[j].x1,yy}]){
                    mp[{l[j].x1,yy}]=1;
                    ans--;
                }
			}
            else if(l[j].y==l[j+1].y&&l[j].y>=xie[i].y&&l[j].y<=xie[i].y+xie[i].x2-xie[i].x1&&xx>=l[j].x1&&xx<=l[j].x2){
				if(!mp[{xx,l[j].y}]){
                    mp[{xx,l[j].y}]=1;
                    ans--;
                }
			}
        }
    }
    // cout<<ans<<endl;
    for(int i=1;i<=2*tot;i++){
        l[i].x1--;
        if(i&1){
            l[i].y--,d[i]--;
        }
    }
    sort(d+1,d+2*tot+1);
    sort(l+1,l+2*tot+1);
    int totls=unique(d+1,d+2*tot+1)-d-1;
    bd(1,1,totls);
    for(int i=1;i<2*tot;i++){
        int posl=lower_bound(d+1,d+totls+1,l[i].x1)-d;
        int posr=lower_bound(d+1,d+totls+1,l[i].x2)-d-1;
        cg(1,posl,posr,l[i].op);
        ans+=sum(1)*(l[i+1].y-l[i].y);
    }
    cout<<ans<<endl;
	return 0;
}
