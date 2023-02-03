/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:53:39 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:53:39 
 */
#include<bits/stdc++.h>
#define int long long
//#define double long double
//#define pii pair <int,int>
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
const int N=1e6+5;
const int M=(1<<12);
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;
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
int cha[N];
vector <int> v[N];
int maxdep,sum[N],deep[N];
void dfs(int now,int fa){
    maxdep=max(maxdep,deep[now]);
    sum[deep[now]]++;
    for(int i=0;i<(int)v[now].size();i++){
        int y=v[now][i];
        if(y==fa)continue;
        deep[y]=deep[now]+1;
        dfs(y,now);
    }
    return ;
}
#define X(i) (i)
#define k(i) (i)
#define Y(i) (-sum[i])
double xie(int i,int j){
    if(i==j)return 1e9;
    return (double)(Y(i+1)-Y(j+1))/(i-j);
}
int ans[N];
int q[N];
signed main(){
	int n=read(),Q=read();
    for(int i=1;i<=Q;i++)cha[i]=read();
    for(int i=2;i<=n;i++){
        int a=read();
        v[a].push_back(i);
    }
    deep[1]=1;
    dfs(1,0);
    for(int i=maxdep-1;i>=1;i--){
        sum[i]+=sum[i+1];
    }
    // cout<<sum[1]<<" "<<deep[2]<<endl;
    int l=1,r=1;
    for(int i=1;i<=maxdep;i++){
        while(l<r&&xie(q[r],q[r-1])>=xie(i,q[r]))r--;
        q[++r]=i;
    }
    for(int i=1;i<=n;i++){
        while(l<r&&xie(q[l],q[l+1])<k(i))l++;
        ans[i]=q[l]+ceil(1.0*sum[q[l]+1]/i);
    }
    for(int i=1;i<=Q;i++){
        if(cha[i]>n){
            cout<<ans[n]<<" ";
            continue;
        }
        cout<<ans[cha[i]]<<" ";
    }
	return 0;
}
/*
ababbab
aba
1
*/