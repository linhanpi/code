/*
 * @Author: watering_penguin 
 * @Date: 2023-03-02 15:41:42 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-02 16:55:01
 */
#include<bits/stdc++.h>
#define int long long
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
const int N=6e5+5;
const int M=6e4+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
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
struct circle{
    int zb[2],minn[2],maxn[2],r,i;
    #define x(p) yuan[p].zb[0]
    #define y(p) yuan[p].zb[1]
    #define r(p) yuan[p].r
}yuan[N];
struct KDT{
    int son[2],minn[2],maxn[2],i;
    #define ls(p) tree[p].son[0]
    #define rs(p) tree[p].son[1]
    #define minn(p,i) tree[p].minn[i]
    #define maxn(p,i) tree[p].maxn[i]
    #define id(p) tree[p].i
}tree[N];
int root,tot;
int bt(){
    int now=++tot;
    return now;
}
bool cmpx(int a,int b){
    return yuan[a].zb[0]<yuan[b].zb[0];
}
bool cmpy(int a,int b){
    return yuan[a].zb[1]<yuan[b].zb[1];
}
bool cmp(circle &x,circle &y){
    return (x.r==y.r)?x.i<y.i:x.r>y.r;
}
void pu(int now){
    for(int i=0;i<2;i++){
        minn(now,i)=yuan[id(now)].minn[i];
        maxn(now,i)=yuan[id(now)].maxn[i];
        if(ls(now)){
            minn(now,i)=min(minn(now,i),minn(ls(now),i));
            maxn(now,i)=max(maxn(now,i),maxn(ls(now),i));
        }
        if(rs(now)){
            minn(now,i)=min(minn(now,i),minn(rs(now),i));
            maxn(now,i)=max(maxn(now,i),maxn(rs(now),i));
        }
    }
    // cout<<"pu "<<now<<" " <<id(now)<<" "<<minn(now,0)<<" "<<minn(now,1)<<" "<<maxn(now,0)<<" "<<maxn(now,1)<<" "<<ls(now)<<" "<<rs(now)<<endl;
    return ;
}
int tp[N];
int rb(int l,int r,int d){
    if(l>r)return 0;
    int mid=(l+r)>>1,now=bt();
    nth_element(tp+l,tp+mid,tp+r+1,d?cmpy:cmpx);
    id(now)=tp[mid];
    // cout<<"now "<<now<<" "<<id(now)<<endl;
    ls(now)=rb(l,mid-1,d^1);
    rs(now)=rb(mid+1,r,d^1);
    pu(now);
    return now;
}
int ans[N];
bool jiao(int i,int j){
    return fang(yuan[i].zb[0]-yuan[j].zb[0])+fang(yuan[i].zb[1]-yuan[j].zb[1])<=fang(yuan[i].r+yuan[j].r);
}
void shan(int now,int res){
    if(!now)return ;
    // cout<<"shan "<<now<<endl;
    if(yuan[res].maxn[0]<minn(now,0)||maxn(now,0)<yuan[res].minn[0]||yuan[res].maxn[1]<minn(now,1)||maxn(now,1)<yuan[res].minn[1])return ;
    if(!ans[yuan[id(now)].i]&&jiao(id(now),res))ans[yuan[id(now)].i]=yuan[res].i;
    if(ls(now))shan(ls(now),res);
    if(rs(now))shan(rs(now),res);
    return ;
}
signed main(){
    int n=read();
    for(int i=1;i<=n;i++){
        x(i)=read(),y(i)=read(),r(i)=read();
        yuan[i].minn[0]=x(i)-r(i),yuan[i].minn[1]=y(i)-r(i);
        yuan[i].maxn[0]=x(i)+r(i),yuan[i].maxn[1]=y(i)+r(i);
        tp[i]=i;
        yuan[i].i=i;
    }
    sort(yuan+1,yuan+n+1,cmp);
    // for(int i=1;i<=n;i++){
    //     cout<<"yuan "<<i<<" "<<yuan[i].i<<" "<<yuan[i].minn[0]<<" "<<yuan[i].minn[1]<<" "<<yuan[i].maxn[0]<<" "<<yuan[i].maxn[1]<<endl;
    // }
    root=rb(1,n,0);
    // cout<<tot<<endl;
    for(int i=1;i<=n;i++){
        if(!ans[yuan[i].i]){
            // cout<<i<<" "<<yuan[i].i<<endl;
            shan(root,i);
        }
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    return 0;
}
