/*
 * @Author: watering_penguin 
 * @Date: 2023-02-24 21:07:20 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-28 16:46:41
 */
#include<bits/stdc++.h>
// #define int long long
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
    int zb[2];
    point(int _x=0,int _y=0){
        zb[0]=_x,zb[1]=_y;
    }
}tp[N],a[N];
struct KDT{
    int son[2],minn[2],maxn[2],si;
    point p;
    #define ls(p) tree[p].son[0]
    #define rs(p) tree[p].son[1]
}tree[N];
int tot,root,top,st[N];
bool cmpx(point &x,point &y){
    return x.zb[0]<y.zb[0];
}
bool cmpy(point &x,point &y){
    return x.zb[1]<y.zb[1];
}
int bt(){
    int now;
    if(top)now=st[top--];
    now=++tot;
    ls(now)=rs(now)=0;
    return now;
}
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
    tree[now].si=tree[ls(now)].si+tree[rs(now)].si+1;
    return ;
}
int cnt;
void shan(int now){
    if(!now)return ;
    st[++top]=now;
    tp[++cnt]=tree[now].p;
    shan(ls(now));
    shan(rs(now));
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
void ck(int &now,int d){
    if(tree[ls(now)].si>tree[now].si*alpha&&tree[rs(now)].si>tree[now].si*alpha){
        cnt=0;
        shan(now);
        now=rb(1,cnt,d);
    }
    return ;
}
void insert(int &now,point x,int d){
    if(!now){
        now=bt();
        tree[now].p=x;
        pu(now);
        return ;
    }
    if(x.zb[d]<=tree[now].p.zb[d])insert(ls(now),x,d^1);
    else insert(rs(now),x,d);
    pu(now);
    ck(now,d);
    return ;
}
int disj(point x,int now){
    int res=0;
    for(int i=0;i<2;i++){
        res+=max(0,tree[now].minn[i]-x.zb[i])+max(0,x.zb[i]-tree[now].maxn[i]);
    }
    return res;
}
int disy(point x,int now){
    int res=0;
    for(int i=0;i<2;i++){
        res+=max(0,tree[now].maxn[i]-x.zb[i])+max(0,x.zb[i]-tree[now].minn[i]);
    }
    return res;
}
int dist(point x,point y){
    return abs(x.zb[0]-y.zb[0])+abs(x.zb[1]-y.zb[1]);
}
int ans;
void chaj(int now,point x){
    int res=min(ans,dist(tree[now].p,x));
    if(res>0)ans=res;
    int dl=inf,dr=inf;
    if(ls(now))dl=disj(x,now);
    if(rs(now))dr=disj(x,now);
    if(dl<dr){
        if(dl<ans)chaj(ls(now),x);
        if(dr<ans)chaj(rs(now),x);
    }
    else{
        if(dr<ans)chaj(rs(now),x);
        if(dl<ans)chaj(ls(now),x);
    }
    return;
}
void chay(int now,point x){
    ans=max(ans,dist(tree[now].p,x));
    int dl=0,dr=0;
    if(ls(now))dl=disy(x,now);
    if(rs(now))dr=disy(x,now);
    if(dl>dr){
        if(dl>ans)chay(ls(now),x);
        if(dr>ans)chay(rs(now),x);
    }
    else{
        if(dr>ans)chay(rs(now),x);
        if(dl>ans)chay(ls(now),x);
    }
    return;
}
int resx[N],resd[N];
signed main(){
    int n=read();
    for(int i=1;i<=n;i++){
        a[i].zb[0]=read(),a[i].zb[1]=read();
        tp[i]=a[i];
    }
    root=rb(1,n,0);
    int res=inf; 
    for(int i=1;i<=n;i++){
        ans=inf;
        chaj(root,a[i]);
        resx[i]=ans;
        ans=0;
        chay(root,a[i]);
        resd[i]=ans;
        res=min(res,-resx[i]+resd[i]);
    }
    cout<<res<<endl;
    return 0;
}
