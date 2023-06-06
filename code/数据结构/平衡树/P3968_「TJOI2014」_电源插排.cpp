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
const int mod=1e9+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra() (ran_int(20071027,1145141919))
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
unordered_map <int,int> mp;
struct fhq{
    struct node{
        int a,b;
        node(int a_=0,int b_=0){
            a=a_,b=b_;
        }
    };
    struct data{
        int rk,si,ls,rs;
        int lpos,rpos;
        int zhan,lmax,rmax,maxn,maxpos;
        int sum,len;
        #define rk(p) tree[p].rk
        #define si(p) tree[p].si
        #define ls(p) tree[p].ls
        #define rs(p) tree[p].rs
        #define lpos(p) tree[p].lpos
        #define rpos(p) tree[p].rpos
        #define zhan(p) tree[p].zhan
        #define lmax(p) tree[p].lmax
        #define rmax(p) tree[p].rmax
        #define maxn(p) tree[p].maxn
        #define maxpos(p) tree[p].maxpos
        #define sum(p) tree[p].sum
        #define len(p) tree[p].len
    }tree[N];
    int tot,root;
    inline void pu(int p){
        if(!p)return ;
        maxn(p)=0;
        si(p)=si(ls(p))+si(rs(p))+len(p);
        sum(p)=sum(ls(p))+sum(rs(p))+zhan(p);
        lmax(p)=lmax(ls(p)),rmax(p)=rmax(rs(p));
        if(ls(p)){
            maxn(p)=maxn(ls(p));
            maxpos(p)=maxpos(ls(p));
        }
        if(!zhan(p)){
            if(!sum(ls(p)))lmax(p)=lmax(ls(p))+len(p)+lmax(rs(p));
            if(!sum(rs(p)))rmax(p)=rmax(rs(p))+len(p)+rmax(ls(p));
            int len=len(p)+rmax(ls(p))+lmax(rs(p));
            if(len>=maxn(p)){
                maxn(p)=len;
                maxpos(p)=((lpos(p)-rmax(ls(p)))+(rpos(p)+lmax(rs(p)))+1)>>1;
            }
        }
        if(maxn(rs(p))>=maxn(p)){
            maxn(p)=maxn(rs(p));
            maxpos(p)=maxpos(rs(p));
        }
        return ;
    }
    inline int bn(int l,int r){
        int p=++tot;
        rk(p)=ra();
        lpos(p)=l,rpos(p)=r;
        zhan(p)=sum(p)=0;
        len(p)=si(p)=r-l+1;
        pu(p);
        return p;
    }
    int hb(int p,int q){
        if(!p||!q)return p^q;
        if(rk(p)<rk(q)){
            rs(p)=hb(rs(p),q);
            pu(p);
            return p;
        }
        else{
            ls(q)=hb(p,ls(q));
            pu(q);
            return q;
        }
    }
    inline void flr(int p,int k){
        if(k<=0)return ;
        if(len(p)<=k)return ;
        int now=lpos(p)+k-1;
        int np=bn(now+1,rpos(p));
        rpos(p)=now;
        len(p)=k;
        maxpos(p)=(lpos(p)+rpos(p)+1)>>1;
        rs(p)=hb(np,rs(p));
        pu(p);
        return ;
    }
    inline void fll(int p,int k){
        if(k<=0)return ;
        if(len(p)<=k)return ;
        int now=lpos(p)+k-1;
        int np=bn(lpos(p),now);
        lpos(p)=now+1;
        len(p)-=k;
        maxpos(p)=(lpos(p)+rpos(p)+1)>>1;
        ls(p)=hb(ls(p),np);
        pu(p);
        return ;
    }
    node fl(int p,int k){
        if(!p)return node(0,0);
        if(si(ls(p))+len(p)<k){
        // if(si(ls(p))<k){
            // flr(p,k-si(ls(p)));
            node t=fl(rs(p),k-si(ls(p))-len(p));
            rs(p)=t.a;
            pu(p);
            return node(p,t.b);
        }
        else{
            fll(p,k-si(ls(p))-1);
            node t=fl(ls(p),k);
            ls(p)=t.b;
            pu(p);
            return node(t.a,p);
        }
    }
    inline void cha(int l,int r){
        node t1=fl(root,r+1);
        node t2=fl(t1.a,l);
        // node t1=fl(root,r);
        // node t2=fl(t1.a,l-1);
        write(sum(t2.b));
        puts("");
        root=hb(hb(t2.a,t2.b),t1.b);
        return ;
    }
    inline void shan(int k){
        int now=mp[k];
        mp.erase(k);
        node t1=fl(root,now+1);
        node t2=fl(t1.a,now);
        // node t1=fl(root,now);
        // node t2=fl(t1.a,now-1);
        zhan(t2.b)=sum(t2.b)=0;
        maxpos(t2.b)=now;
        maxn(t2.b)=lmax(t2.b)=rmax(t2.b)=len(t2.b);
        root=hb(hb(t2.a,t2.b),t1.b);
        return ;
    }
    inline void add(int k){
        int now=maxpos(root);
        mp[k]=now;
        node t1=fl(root,now+1);
        node t2=fl(t1.a,now);
        // node t1=fl(root,now);
        // node t2=fl(t1.a,now-1);
        zhan(t2.b)=sum(t2.b)=1;
        maxpos(t2.b)=maxn(t2.b)=lmax(t2.b)=rmax(t2.b)=0;
        root=hb(hb(t2.a,t2.b),t1.b);
        return ;
    }
}phs;
signed main(){
	int n=read(),q=read();
    phs.root=phs.bn(1,n);
    phs.maxpos(phs.root)=(2+n)>>1;
    while(q--){
        int k=read();
        if(!k){
            int l=read(),r=read();
            phs.cha(l,r);
        }
        else{
            if(mp.count(k))phs.shan(k);
            else phs.add(k);
        }
    }
	return 0;
}
