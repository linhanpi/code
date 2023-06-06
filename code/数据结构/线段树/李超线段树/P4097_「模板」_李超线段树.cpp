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
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=39989;
const int mo=1e9;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(double x,double y){return abs(x-y)<=eps;}
inline bool dayu(double x,double y){return x-y>=eps;}
inline bool xiaoyu(double x,double y){return y-x>=eps;}
int cnt;
double k[N],b[N];
struct lcxds{
    struct data{
        int maxn;
        #define maxn(p) tree[p].maxn
    }tree[N<<2];
    double zhi(int x,int id){return k[id]*x+b[id];}
    int getmx(int a,int c,int x){
        double b=zhi(x,a),d=zhi(x,c);
        return dengyu(b,d)?min(a,c):b>d?a:c;
    }
    void quanxg(int p,int l,int r,int id){
        int mid=(l+r)>>1;
        if(zhi(mid,id)>zhi(mid,maxn(p))||zhi(mid,id)==zhi(mid,maxn(p))&&id<maxn(p))swap(maxn(p),id);
        if(l==r)return ;
        if(zhi(l,id)>zhi(l,maxn(p))||zhi(l,id)==zhi(l,maxn(p))&&id<maxn(p))quanxg(lson,l,mid,id);
        else if(zhi(r,id)>zhi(r,maxn(p))||zhi(r,id)==zhi(r,maxn(p))&&id<maxn(p))quanxg(rson,mid+1,r,id);
        return ;
    }
    void quxg(int p,int l,int r,int ql,int qr,int id){
        if(ql<=l&&r<=qr){
            quanxg(p,l,r,id);
            return ;
        }
        int mid=(l+r)>>1;
        if(ql<=mid)quxg(lson,l,mid,ql,qr,id);
        if(qr>mid)quxg(rson,mid+1,r,ql,qr,id);
        return ;
    }
    int cha(int p,int l,int r,int pos){
        if(l==r)return maxn(p);
        int mid=(l+r)>>1;
        if(pos<=mid)return getmx(cha(lson,l,mid,pos),maxn(p),pos);
        else return getmx(cha(rson,mid+1,r,pos),maxn(p),pos);
    }
}lcs;
signed main(){
	int n=read();
    for(int i=1,las=0;i<=n;i++){
        int op=read(),c=read();c=(c+las-1)%mod+1;
        if(op==0){
            write(las=lcs.cha(1,1,mod,c));
            puts("");
        }
        else{
            int d=read(),e=read(),f=read();
            e=(e+las-1)%mod+1;
            d=(d+las-1)%mo+1,f=(f+las-1)%mo+1;
            if(c>e)swap(c,e),swap(d,f);
            if(c==e)b[++cnt]=max(d,f);
            else k[++cnt]=(double)(f-d)/(e-c),b[cnt]=d-c*k[cnt];
            lcs.quxg(1,1,mod,c,e,cnt);
        }
    }
	return 0;
}
