/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:50:50 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:50:50 
 */
#include<bits/stdc++.h>
// #define int long long
// #define double long double
//#define pii pair <int,int>
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
const int N=1e5+5;
const int M=1e6+5;
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod=(1<<30);
const double eps=1e-6;
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
int p[N],vis[N],miu[N],tot,f[N];
int A,B,C,maxn,ans,cnt;
vector <int> v[N];
unordered_map <int,bool> mp[N];
int sA[M],sB[M],sC[M],du[N];
int ta,tb,tc;
void ycl(){
    miu[1]=1;
    for(int i=2;i<=N-5;i++){
        if(!vis[i])p[++tot]=i,miu[i]=-1;
        for(int j=1;j<=tot&&i*p[j]<=N-5;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                miu[i*p[j]]=0;
                break;
            }
            miu[i*p[j]]=-miu[i];
        }
    }
    for(int i=1;i<=N-5;i++){
        for(int l=1,r;l<=i;l=r+1){
            r=i/(i/l);
            (f[i]+=1ll*(r-l+1)*(i/l)%mod)%=mod;
        }
    }
    return ;
}
int res;
void gx(int a,int b,int c){
    (res+=1ll*f[a/ta]*f[b/tb]%mod*f[c/tc]%mod)%=mod;
}
void get(int a,int b,int c){
    res=0;
    if(a==b&&b==c)gx(A,B,C);
    else if(a==b||b==c||c==a)gx(A,B,C),gx(C,A,B),gx(B,C,A);
    else gx(A,B,C),gx(A,C,B),gx(B,A,C),gx(B,C,A),gx(C,A,B),gx(C,B,A);
    (ans+=(miu[a]*miu[b]*miu[c]*res%mod+mod)%mod)%=mod;
    return ;
}
void syh(){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=cnt;i++){
        int &a=sA[i],&b=sB[i];
        if(du[a]>du[b])swap(a,b);
        else if(du[a]==du[b]&&a>b)swap(a,b);
        v[a].push_back(i);
    }
    for(int i=1;i<=maxn;i++){
        for(int j:v[i]){
            vis[sB[j]]=sC[j];
        }
        for(int j:v[i]){
            for(int k:v[sB[j]]){
                if(vis[sB[k]])ta=vis[sB[k]],tb=sC[j],tc=sC[k],get(i,sB[j],sB[k]);
            }
        }
        for(int j:v[i])vis[sB[j]]=0;
    }
    return ;
}
signed main(){
    ycl();
    // cout<<f[100000]<<endl;
    int T=1;
    while(T--){
        ans=cnt=0;
        A=read(),B=read(),C=read();
        maxn=max(A,max(B,C));
        for(int i=maxn;i>=1;i--){
            for(int j=i;j<=maxn;j+=i){
                if(!miu[j])continue;
                for(int k=j;k<=1ll*maxn*i/j;k+=i){
                    if(!miu[k])continue;
                    if(!mp[j][k])++cnt,sA[cnt]=j,sB[cnt]=k,sC[cnt]=j/i*k,du[j]++,du[k]++,mp[j][k]=1;
                }
                // if(A==100000)cout<<i<<" "<<j<<endl;
            }
        }
        // cout<<"cnt "<<cnt<<endl;
        // cout<<"1111"<<endl;
        syh();
        for(int i=1;i<=maxn;i++){
            v[i].clear(),mp[i].clear(),du[i]=0;
        }
        cout<<(ans+mod)%mod<<endl;
    }
	return 0;
}
/*
*/