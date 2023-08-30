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
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=1e5+5;
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
char ch[10];
int n,m,mp[N][10],x,y,f[30],tag[30],v[30],q;
int get(int x){
    return f[x]==x?x:f[x]=get(f[x]);
}
struct node{
    int f[14],tag[14],l,r,sum;
    int get(int x){
        return x==f[x]?x:f[x]=get(f[x]);
    }
    void make(){
        int p=l;
        sum=0;
        for(int i=1;i<=2*m;i++){
            f[i]=i,tag[i]=0;
        }
        for(int i=1;i<=m;i++){
            if(mp[p][i]==4){
                tag[i]=1,sum++;
            }
        }
        for(int i=1;i<=m;i++){
            if(mp[p][i]>1){
                if(i!=1&&mp[p][i-1]>1){
                    int x=get(i),y=get(i-1);
                    if(x!=y){
                        f[y]=x;
                        if(tag[x]&&tag[y]){
                            sum--;
                        }
                        else if(tag[y]){
                            tag[x]=1;
                        }
                    }
                }
                if(i!=m&&mp[p][i+1]>1){
                    int x=get(i),y=get(i+1);
                    if(x!=y){
                        f[y]=x;
                        if(tag[x]&&tag[y]){
                            sum--;
                        }
                        else if(tag[y]){
                            tag[x]=1;
                        }
                    }
                }
            }
        }
        for(int i=1;i<=m;i++){
            f[i+m]=f[i];
        }
    }
}t[N*4];
node merge(node x,node y){
    node tmp;
    memset(tmp.tag,0,sizeof(tmp.tag));
    tmp.l=x.l;
    tmp.r=y.r;
    tmp.sum=x.sum+y.sum;
    for(int i=1;i<=2*m;i++){
        f[i]=x.f[i],tag[i]=x.tag[i];
    }    
    for(int i=1;i<=2*m;i++){
        f[i+2*m]=y.f[i]+2*m,tag[i+2*m]=y.tag[i];
    }
    int p=x.r,q=p+1;
    for(int i=1;i<=m;i++){
        if(mp[p][i]!=0&&mp[p][i]!=2&&mp[q][i]!=0&&mp[q][i]!=2){
            int x=get(m+i),y=get(m*2+i);
            if(x!=y){
                f[x]=y;
                if(tag[x]&&tag[y]){
                    tmp.sum--;
                }
                else if(tag[x]){
                    tag[y]=1;
                }
            }
        }
    }
    memset(v,0,sizeof(v));
    for(int i=1;i<=m;i++){
        int x=get(i);
        if(!v[x]){
            v[x]=i,tmp.tag[i]=tag[x];
        }
        x=get(i+3*m);
        if(!v[x]){
            v[x]=i+m,tmp.tag[i+m]=tag[x];
        }
    }
    for(int i=1;i<=m;i++){
        tmp.f[i]=v[get(i)];
        tmp.f[i+m]=v[get(i+3*m)];
    }
    return tmp;
}
void bd(int x,int l,int r){
    t[x].l=l,t[x].r=r;
    if(l==r){
        t[x].make();
        return;
    }
    int mid=(l+r)>>1;
    bd(x*2,l,mid);
    bd(x*2+1,mid+1,r);
    t[x]=merge(t[x*2],t[x*2+1]);
}
void rebd(int x,int y){
    int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
    if(l==r){
        t[x].make();
        return;
    }
    if(y<=mid) rebd(x*2,y);
    else rebd(x*2+1,y);
    t[x]=merge(t[x*2],t[x*2+1]);
}
node ask(int x,int a,int b){
    int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
    if(l==a&&r==b) return t[x];
    if(b<=mid) return ask(x*2,a,b);
    if(a>mid) return ask(x*2+1,a,b);
    return merge(ask(x*2,a,mid),ask(x*2+1,mid+1,b));
}
inline int ha(char ch){
    if(ch=='.') return 0;
    if(ch=='|') return 1;
    if(ch=='-') return 2;
    if(ch=='+') return 3;
    if(ch=='O') return 4;
    return -1;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",ch+1);
        for(int j=1;j<=m;j++) mp[i][j]=ha(ch[j]);
    }
    bd(1,1,n);
    q=read();
    for(int i=1;i<=q;i++){
        scanf("%s",ch);
        if(ch[0]=='Q'){
            int x=read(),y=read();
            printf("%d\n",ask(1,x,y).sum);
        }
        else{
            
            int x=read(),y=read();
            scanf("%s",ch);
            mp[x][y]=ha(ch[0]);
            rebd(1,x);
        }
    }
    return 0;
}