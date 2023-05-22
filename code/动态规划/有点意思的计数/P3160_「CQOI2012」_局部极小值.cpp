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
template<typename T>inline T red() {
	T x=0;
	bool f=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=true;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>inline void write(T x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x/10) write(x/10);
	putchar((x%10)^48);
	return;
}
const int N=35;
const int M=265;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=12345678;
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
inline int qmi(int x,int y,int mod){
	int ans=1;
	x%=mod;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
inline int fang(int x) {return x*x;}
int f[N][M],x[N],y[N],mp[N][N],vis[N][N],re[M];
int dx[]={-1,0,1,0,-1,1,-1,1,0},dy[]={0,-1,0,1,-1,-1,1,1,0};
int n,m,cnt;
inline int dp(){
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<(1<<cnt);i++){
        memset(vis,0,sizeof(vis));
        re[i]=n*m;
        for(int j=1;j<=cnt;j++){
            if((i&(1<<(j-1)))==0){
                for(int k=0;k<=8;k++){
                    vis[x[j]+dx[k]][y[j]+dy[k]]=1;
                }
            }
        }
        for(int j=1;j<=n;j++){
            for(int k=1;k<=m;k++){
                if(vis[j][k])re[i]--;
            }
        }
    }
    for(int i=1;i<=n*m;i++){
        for(int j=0;j<(1<<cnt);j++){
            if(re[j]-i+1>0)(f[i][j]+=f[i-1][j]*(re[j]-i+1))%=mod;
            for(int k=1;k<=cnt;k++){
                if((1<<(k-1))&j){
                    (f[i][j]+=f[i-1][j^(1<<(k-1))])%=mod;
                }
            }
        }
    }
    // cout<<cnt<<" "<<f[n*m][(1<<cnt)-1]<<endl;
    return f[n*m][(1<<cnt)-1];
}
inline int dfs(int nowx,int nowy){
    int ans=0;
    if(nowy==m+1)nowx++,nowy=1;
    if(nowx==n+1)return dp();
    ans=dfs(nowx,nowy+1);
    for(int i=0;i<=8;i++){
        if(mp[nowx+dx[i]][nowy+dy[i]])return ans;
    }
    x[++cnt]=nowx,y[cnt]=nowy,mp[nowx][nowy]=1;
    (ans+=mod-dfs(nowx,nowy+1))%=mod;
    mp[nowx][nowy]=0,--cnt;
    return ans;
}
char s[N];
signed main(){
	n=read(),m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++){
            if(s[j]=='X')mp[i][j]=1,x[++cnt]=i,y[cnt]=j;
        }
    }
    // cout<<"114514\n";
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<i;j++){
            if(abs(x[i]-x[j])<2&&abs(y[i]-y[j])<2){
                puts("0");
                return 0;
            }
        }
    }
    // cout<<"114514\n";
    if(cnt==0){
        puts("0");
        return 0;
    }
    // cout<<"114514\n";
    cout<<dfs(1,1)<<endl;
	return 0;
}
