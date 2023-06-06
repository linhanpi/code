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
#define ra (inf-rnd())
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
int n,q;
int st[N][20],a[N],lg[N],mi2[N];
inline int mind(const int &x,const int &y){
    return a[x]<a[y]?x:y;
}
inline void stycl(){
    mi2[0]=1;
    for(int i=1;i<=16;i++)mi2[i]=mi2[i-1]<<1;
    for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)st[i][0]=i;
    for(int j=1;j<=lg[n];j++){
        for(int i=1;i<=n-mi2[j]+1;i++){
            st[i][j]=mind(st[i][j-1],st[i+mi2[j-1]][j-1]);
        }
    }
    return ;
}
inline int cha(int l,int r){
    int t=lg[r-l+1];
    return mind(st[l][t],st[r-mi2[t]+1][t]);
}
int kuaichang;
struct node{
    int l,r,pos,id;
}Q[N];
bool operator <(const node &x,const node &y){
    return (x.pos==y.pos)?x.pos&1?x.r>y.r:x.r<y.r:x.pos<y.pos;
}
int s[N],top,qian[N],hou[N],fq[N],fh[N];
void ddzycl(){
    for(int i=1;i<=n;i++){
        while(top&&a[s[top]]>a[i])hou[s[top--]]=i;
        qian[i]=s[top];
        s[++top]=i;
    }
    while(top)qian[s[top]]=s[top-1],hou[s[top--]]=n+1;
    for(int i=1;i<=n;i++)fq[i]=a[i]*(i-qian[i])+fq[qian[i]];
    for(int i=n;i>=1;i--)fh[i]=a[i]*(hou[i]-i)+fh[hou[i]];
    return ;
}
inline int zuo(int l,int r){int qi=cha(l-1,r);return a[qi]*(r-qi+1)+fh[l-1]-fh[qi];}
inline int you(int l,int r){int qi=cha(l,r+1);return a[qi]*(qi-l+1)+fq[r+1]-fq[qi];}
int ans[N];
signed main(){
	n=read(),q=read(),kuaichang=sqrt(q);
    for(int i=1;i<=n;i++)a[i]=read();
    stycl();
    for(int i=1;i<=q;i++){
        Q[i].l=read(),Q[i].r=read();
        Q[i].pos=Q[i].l/kuaichang;
        Q[i].id=i;
    }
    sort(Q+1,Q+q+1);
    ddzycl();
    int l=1,r=0,res=0;
    for(int i=1;i<=q;i++){
        while(l>Q[i].l)res+=zuo(l--,r);
        while(r<Q[i].r)res+=you(l,r++);
        while(l<Q[i].l)res-=zuo(++l,r);
        while(r>Q[i].r)res-=you(l,--r);
        ans[Q[i].id]=res;
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
	return 0;
}
