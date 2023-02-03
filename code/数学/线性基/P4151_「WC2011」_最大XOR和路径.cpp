/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:51:26 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:51:26 
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
const int N=5e4+5;
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
struct node{
    int dao,quan;
};
vector <node> v[N];
int ji[70];
void add(int x){
    for(int i=63;i>=0;i--){
        if(x&(1ll<<i)){
            if(ji[i]){
                x^=ji[i];
            }
            else{
                ji[i]=x;
                return;
            }
        }
    }
    return ;
}
bool vis[N];
int deep[N];
void dfs(int now){
    vis[now]=1;
    for(int i=0;i<(int)v[now].size();i++){
        int y=v[now][i].dao;
        if(!vis[y])deep[y]=deep[now]^v[now][i].quan,dfs(y);
        else{
            add(deep[y]^deep[now]^v[now][i].quan);
        }
    }
    return ;
}
int n,m;
int maxji(){
    int res=deep[n];
    for(int i=63;i>=0;i--){
        if((res^ji[i])>res)res^=ji[i];
    }
    return res;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int s=read(),t=read(),d=read();
        v[s].push_back({t,d});
        v[t].push_back({s,d});
    }
    dfs(1);
    cout<<maxji()<<endl;
    return 0;
}
/*
ababbab
aba
1
*/