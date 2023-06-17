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
const int N=2e5+5;
const int M=1e2+5;
const int S=5;
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
struct juzheng{
    int a[S][S];
    juzheng(){
        memset(a,0x3f,sizeof(a));
    }
}G[N],ans,I;
inline juzheng operator *(const juzheng &x,const juzheng &y){
    juzheng c;
    for(int i=0;i<S;i++){
        for(int j=0;j<S;j++){
            for(int k=0;k<S;k++){
                c.a[i][j]=min(c.a[i][j],x.a[i][k]+y.a[k][j]);
            }
        }
    }
    return c;
}
inline juzheng operator /(const juzheng &x,const juzheng &y){
    juzheng c;
    for(int i=0;i<S;i++){
        for(int j=0;j<S;j++){
            c.a[0][i]=min(c.a[0][i],x.a[0][j]+y.a[j][i]);
        }
    }
    return c;
}
struct xianduanshu{
    juzheng val[N<<2];
    inline void pu(int p){
        val[p]=val[lson]*val[rson];
        return ;
    }
    void bd(int p,int l,int r){
        if(l==r)return val[p]=G[l],void();
        int mid=(l+r)>>1;
        bd(lson,l,mid);
        bd(rson,mid+1,r);
        pu(p);
        return ;
    }
    void cha(int p,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr){
            return ans=ans/val[p],void();
        }
        int mid=(l+r)>>1;
        if(ql<=mid)cha(lson,l,mid,ql,qr);
        if(qr>mid)cha(rson,mid+1,r,ql,qr);
        return ;
    }
}xds;
signed main(){
	int n=read(),q=read();
    I.a[0][0]=0;
    for(int i=1;i<=n;i++){
        char ch;cin>>ch;
        for(int j=0;j<S;j++)G[i].a[j][j]=0;
        if(ch=='2')G[i].a[0][0]=1,G[i].a[0][1]=0;
        if(ch=='0')G[i].a[1][1]=1,G[i].a[1][2]=0;
        if(ch=='1')G[i].a[2][2]=1,G[i].a[2][3]=0;
        if(ch=='7')G[i].a[3][3]=1,G[i].a[3][4]=0;
        if(ch=='6')G[i].a[3][3]=1,G[i].a[4][4]=1;
    }
    xds.bd(1,1,n);
    while(q--){
        int l=read(),r=read();
        ans=I;
        xds.cha(1,1,n,l,r);
        cout<<((ans.a[0][4]<=n?ans.a[0][4]:-1))<<endl;
    }
	return 0;
}
