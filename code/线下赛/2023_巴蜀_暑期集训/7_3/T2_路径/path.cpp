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
const int N=3e3+5;
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
vector <int> you[N],yao;
int tu[N][N],c[N],d[N];
signed main(){
    // freopen("path.in","r",stdin);
    // freopen("path.out","w",stdout);
    memset(tu,0x3f,sizeof(tu));
    int n=read(),m=read();
    for(int i=1;i<n;i++){
        d[i]=c[i]=read();
    }
    sort(d+1,d+n);
    int cnt=unique(d+1,d+n)-d-1;
    if(cnt>10){
        puts("-1");
        return 0;
    }
    for(int i=1;i<=m;i++){
        int a=read(),b=read(),w=read();
        if(a>b)swap(a,b);
        tu[a][b]=min(tu[a][b],w);
    }
    for(int i=1;i<n;i++){
        c[i]=lower_bound(d+1,d+cnt+1,c[i])-d;
        you[c[i]].push_back(i);
    }
    // for(int i=1;i<n;i++){
    //     cout<<i<<" "<<c[i]<<endl;
    // }
    int ans=inf;
    for(int i=0;i<(1<<cnt);i++){
        yao.clear();
        yao.push_back(0);
        yao.push_back(n);
        int tep=i,tott=0;
        while(tep){
            tott++;
            if(tep&1){
                for(int y:you[tott]){
                    yao.push_back(y);
                }
            }
            tep>>=1;
        }
        sort(yao.begin(),yao.end());
        // cout<<i<<endl;
        // for(int y:yao){
        //     cout<<"y "<<y<<" ";
        // }
        // cout<<endl;
        int res=0;
        for(int j=0;j<yao.size()-1;j++){
            if(tu[yao[j]][yao[j+1]]==tu[0][0]){
                res=inf;
                break;
            }
            res+=tu[yao[j]][yao[j+1]];
        }
        ans=min(ans,res);
    }
    if(ans!=inf){
        cout<<ans<<endl;
    }
    else{
        cout<<-1<<endl;
    }
	return 0;
}
/*
10 11
1 5 10 3 9 2 8 6 4 7
2 5 8
1 1 3 0
2 2 6
1 6 8 1
2 1 10
2 4 9
1 2 5 0
1 4 8 1
1 3 6 0
2 1 10
2 3 8

*/