/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:51:17 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:51:17 
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
const int N=2e4+5;
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
int a[N];
vector <int> v[N];
struct node{
    int ji[61];
    node(){
        memset(ji,0,sizeof(ji));
    }
    void add(int x){
        for(int i=60;i>=0;i--){
            if(x&(1ll<<i)){
                if(ji[i])x^=ji[i];
                else{
                    ji[i]=x;
                    return ;
                }
            }
        }
        return ;
    }
    int maxji(){
        int res=0;
        for(int i=60;i>=0;i--){
            if((res^ji[i])>res)res^=ji[i];
        }
        return res;
    }
}bzji[N][20];
void hb(node &y,node &z){
    for(int i=0;i<=60;i++){
        z.add(y.ji[i]);
    }
    return ;
}
int fa[N][20];
int deep[N];
void dfs(int now){
    for(int i=0;i<(int)v[now].size();i++){
        int y=v[now][i];
        if(fa[now][0]==y)continue;
        fa[y][0]=now;
        bzji[y][0].add(a[y]);
        for(int j=1;j<=18;j++){
            fa[y][j]=fa[fa[y][j-1]][j-1];
            memcpy(bzji[y][j].ji,bzji[y][j-1].ji,sizeof(bzji[y][j-1].ji));
            hb(bzji[fa[y][j-1]][j-1],bzji[y][j]);
        }
        deep[y]=deep[now]+1;
        dfs(y);
    }
    return;
}
inline int lca(int x,int y){
    node res;
    if(deep[x]>deep[y])swap(x,y);
	for(int i=18;i>=0;i--){
		if(deep[fa[y][i]]>=deep[x])hb(bzji[y][i],res),y=fa[y][i];
	}
	if(x==y){
        res.add(a[x]);
        return res.maxji();
    }
	for(int i=18;i>=0;i--){
		if(fa[x][i]!=fa[y][i])hb(bzji[x][i],res),hb(bzji[y][i],res),x=fa[x][i],y=fa[y][i];
	}
    res.add(a[x]),res.add(a[y]),res.add(a[fa[x][0]]);
	return res.maxji();
}
signed main(){
    int n=read(),q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    bzji[1][0].add(a[1]);
    for(int j=1;j<=18;j++){
        bzji[1][j].add(a[1]);
    }
    dfs(1);
    // cout<<bzji[1][0].maxji()<<endl;
    while(q--){
        int x=read(),y=read();
        write(lca(x,y));
        puts("");
        // cout<<lca(x,y)<<endl;
    }
    return 0;
}
/*
ababbab
aba
1
*/