#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned long long
// #define uint unsigned int
// #define rint register int
// #define ll long long
// #define double long double
#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (now<<1)
#define rson (now<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=1e18+7;
const int base=131;
const int mod=998244353;
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
char s[N],ch[N];
int p[N];
int len,zf=27;
int sa[N],tong[N],rk[N],tp[N];
struct BIT{
    int c[N*2+5];
    void ycl(){
        memset(c,0,sizeof(c));
        return ;
    }
    void add(int x,int v){
        for(int i=x;i<=len;i+=lowbit(i)){
            c[i]+=v;
        }
        return ;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)){
            ret+=c[i];
        }
        return ret;
    }
}bit[2],tt;
void jspai(){
    for(int i=0;i<=zf;i++)tong[i]=0;
    for(int i=1;i<=len;i++)tong[rk[i]]++;
    for(int i=1;i<=zf;i++)tong[i]+=tong[i-1];
    for(int i=len;i>=1;i--)sa[tong[rk[tp[i]]]--]=tp[i];
    return ;
}
vector <pii> qv[N+5];
int res[N];
signed main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    int c=read(),T=read();
    while(T--){
        int n=read(),q=read();
        scanf("%s",s+1);
        ch[0]='~',ch[1]='|';
        for(int i=1;i<=n;i++){
            ch[i<<1]=s[i];
            ch[i<<1|1]='|';
        }
        s[n+1]='{';
        for(int i=1;i<=n;i++){
            s[n+i+1]=s[n-i+1];
        }
        memset(p,0,sizeof(p));
        for(int i=1,r=0,mid=0;i<=(n<<1|1);i++){
            p[i]=min(p[(mid<<1)-i],r-i+1);
            while(ch[i+p[i]]==ch[i-p[i]])p[i]++;
            if(i+p[i]-1>r)r=i+p[i]-1,mid=i;
        }
        for(int i=1;i<=(n<<1|1);i++){
            if(i&1){
                p[i>>1]=p[i]/2;
            }
        }
        len=2*n+1;
        for(int i=1;i<=len;i++){
            tp[i]=i;
            rk[i]=s[i]-'a'+1;
        }
        jspai();
        for(int w=1,p=0;p<len;zf=p,w<<=1){
            p=0;
            for(int i=1;i<=w;i++)tp[++p]=len-w+i;
            for(int i=1;i<=len;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
            jspai();
            swap(tp,rk);
            rk[sa[1]]=p=1;
            for(int i=2;i<=len;i++){
                rk[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
            }
        }
        for(int i=1;i<=n;i++){
            qv[i].clear();
        }
        memset(res,0,sizeof(res));
        for(int i=1;i<=q;i++){
            int x=read(),y=read();
            qv[x].push_back({y,i});
        }
        bit[0].ycl(),bit[1].ycl();
        for(int i=len;i;i--){
            if(sa[i]>n+1){
                int pos=len-sa[i]+1;
                bit[pos&1].add(pos,1);
            }
            else if(sa[i]<=n){
                int pos=sa[i];
                for(pii p:qv[pos]){
                    res[p.second]=bit[(pos&1)^1].query(pos+2*p.first-1)-bit[(pos&1)^1].query(pos-1);
                }
            }
        }
        for(int i=1;i<=n;i++){
            // cout<<"i "<<p[i]<<endl;
            for(int j=1;j<=p[i];j++){
                int l=i-j+1,r=i+j;
                if(rk[2*n-r+2]>rk[l]){
                    for(pii p:qv[l]){
                        if(l+p.first*2-1<r)continue;
                        res[p.second]--;
                    }
                }
            }
        }
        for(int i=1;i<=q;i++){
            write(res[i]);
            puts("");
        }
    }
	return 0;
}
/*
0 1
9 3
abacababa
1 4
2 4
3 3
9 3
*/