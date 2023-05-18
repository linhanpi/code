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
const int N=1e2+5;
const int M=1e2+5;
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
struct zdj{
    int t[26],f,cnt;
    #define t(p,c) acam[p].t[c]
    #define f(p) acam[p].f
    #define cnt(p) acam[p].cnt
}acam[N];
int tot;
void insert(string s){
    int p=0;
    for(int i=0;i<s.size();i++){
        int ne=s[i]-'a';
        if(!t(p,ne))t(p,ne)=++tot;
        p=t(p,ne);
    }
    cnt(p)++;
    return ;
}
void bd(){
    queue <int> q;
    for(int i=0;i<26;i++)if(t(0,i))f(t(0,i))=0,q.push(t(0,i));
    while(!q.empty()){
        int now=q.front();
        q.pop();
        cnt(now)+=cnt(f(now));
        for(int i=0;i<26;i++){
            if(t(now,i))f(t(now,i))=t(f(now),i),q.push(t(now,i));
            else t(now,i)=t(f(now),i);
        }
    }
    return ;
}
int zhao(int p,string s){
    for(char y:s){
        p=t(p,y-'a');
        if(cnt(p))return -1;
    }
    return p;
}
struct jz{
    int n,m,a[2*N][2*N];
    jz(){
        memset(a,0,sizeof(a));
    }
    void pt(){
        cout<<n<<" "<<m<<endl;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cout<<i<<" "<<j<<" "<<a[i][j]<<endl;
            }
        }
        return ;
    }
}A,B;
jz operator *(const jz &x,const jz &y){
    jz c;
    c.n=x.n,c.m=y.m;
    for(int i=1;i<=x.n;i++){
        for(int j=1;j<=y.m;j++){
            for(int k=1;k<=x.m;k++){
                c.a[i][j]=(c.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
            }
        }
    }
    return c;
}
string jb[N];
int xia[N][N],dp[N][N],ke[N],ys[N];
signed main(){
	int n=read(),m=read(),L=read();
    for(int i=1;i<=n;i++){
        cin>>jb[i];
    }
    for(int i=1;i<=m;i++){
        string s;cin>>s;
        insert(s);
    }
    bd();
    for(int i=0;i<=tot;i++){
        if(cnt(i))continue;
        for(int j=1;j<=n;j++){
            xia[i][j]=zhao(i,jb[j]);
        }
    }
    if(L<=100){
        dp[0][0]=1;
        for(int i=0;i<=L;i++){
            for(int now=0;now<=tot;now++){
                if(!dp[now][i])continue;
                for(int j=1;j<=n;j++){
                    if((~xia[now][j])&&i+jb[j].size()<=L){
                        dp[xia[now][j]][i+jb[j].size()]=(dp[xia[now][j]][i+jb[j].size()]+dp[now][i])%mod;
                    }
                }
            }
        }
        int ans=0;
        for(int i=0;i<=tot;i++){
            if(dp[i][L])ans=(ans+dp[i][L])%mod;
        }
        cout<<ans<<endl;
    }
    else{
        int cnt=0;
        for(int i=0;i<=tot;i++){
            if(!cnt(i)){
                ke[ys[i]=++cnt]=i;
            }
        }
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=n;j++){
                if(!(~xia[ke[i]][j]))continue;
                // cout<<"ke "<<ke[i]<<" "<<j<<" "<<xia[ke[i]][j]<<endl;
                if(jb[j].size()==1)++B.a[i][ys[xia[ke[i]][j]]];
                else ++B.a[cnt+i][ys[xia[ke[i]][j]]];
            }
            ++B.a[i][i+cnt];
        }
        A.n=A.m=B.n=B.m=2*cnt;
        // B.pt();
        // cout<<"A-----------------------\n";
        A.a[1][ys[0]]=1;
        // A=A*B;
        // A.pt();
        while(L){
            if(L&1)A=A*B;
            B=B*B;
            L>>=1;
        }
        // A.pt();
        int ans=0;
        for(int i=1;i<=cnt;i++)ans=(ans+A.a[1][i])%mod;
        cout<<ans<<endl;
    }
	return 0;
}
/*
2 2 3
a
ab
aba
aaa
*/