/*
 * @Author: watering_penguin 
 * @Date: 2023-02-28 17:09:20 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-01 16:47:19
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
struct point{
    int zb[2],val;
    point(int _x=0,int _y=0,int _val=0){
        zb[0]=_x,zb[1]=_y,val=_val;
    }
}tp[N];
bool cmpx(point &x,point &y){
    return x.zb[0]<y.zb[0];
}
bool cmpy(point &x,point &y){
    return x.zb[1]<y.zb[1];
}
int root,tot;
int bt(){
    int now=++tot;
    return now;
}
struct KDT{
    int son[2],minn[2],maxn[2],val;
    point p;
    #define ls(p) tree[p].son[0]
    #define rs(p) tree[p].son[1]
}tree[N];
void pu(int now){
    for(int i=0;i<2;i++){
        tree[now].minn[i]=tree[now].maxn[i]=tree[now].p.zb[i];
        if(ls(now)){
            tree[now].minn[i]=min(tree[now].minn[i],tree[ls(now)].minn[i]);
            tree[now].maxn[i]=max(tree[now].maxn[i],tree[ls(now)].maxn[i]);
        }
        if(rs(now)){
            tree[now].minn[i]=min(tree[now].minn[i],tree[rs(now)].minn[i]);
            tree[now].maxn[i]=max(tree[now].maxn[i],tree[rs(now)].maxn[i]);
        }
    }
    tree[now].val=tree[now].p.val+tree[ls(now)].val+tree[rs(now)].val;
    return ;
}
int rb(int l,int r,int d){
    if(l>r)return 0;
    int mid=(l+r)>>1,now=bt();
    nth_element(tp+l,tp+mid,tp+r+1,d?cmpy:cmpx);
    tree[now].p=tp[mid];
    ls(now)=rb(l,mid-1,d^1);
    rs(now)=rb(mid+1,r,d^1);
    pu(now);
    return now;
}
int A,B,C;
int maxv(int now){
    return max(A*tree[now].maxn[0],A*tree[now].minn[0])+max(B*tree[now].maxn[1],B*tree[now].minn[1]);
}
int minv(int now){
    return min(A*tree[now].maxn[0],A*tree[now].minn[0])+min(B*tree[now].maxn[1],B*tree[now].minn[1]);
}
int ans;
void cha(int now){
    if(!now)return ;
    if(tree[now].p.zb[0]*A+tree[now].p.zb[1]*B<C)ans+=tree[now].p.val;
    if(ls(now)){
        int maxn=maxv(ls(now)),minn=minv(ls(now));
        if(maxn<C)ans+=tree[ls(now)].val;
        else if(minn<C)cha(ls(now));
    }
    if(rs(now)){
        int maxn=maxv(rs(now)),minn=minv(rs(now));
        if(maxn<C)ans+=tree[rs(now)].val;
        else if(minn<C)cha(rs(now));
    }
    return ;
}
signed main(){
    int n=read(),m=read();
    for(int i=1;i<=n;i++){
        tp[i].zb[0]=read(),tp[i].zb[1]=read(),tp[i].val=read();
    }
    root=rb(1,n,0);
    for(int i=1;i<=m;i++){
        ans=0;
        A=read(),B=read(),C=read();
        cha(root);
        write(ans);
        puts("");
    }
    return 0;
}
