/*
 * @Author: watering_penguin 
 * @Date: 2023-02-28 17:09:20 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-01 15:51:52
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
    int zb[2],id;
    point(int _x=0,int _y=0,int _i=0){
        zb[0]=_x,zb[1]=_y,id=_i;
    }
}tp[N],a[N];
bool cmpx(point &x,point &y){
    return x.zb[0]<y.zb[0];
}
bool cmpy(point &x,point &y){
    return x.zb[1]<y.zb[1];
}
struct KDT{
    int son[2],minn[2],maxn[2],si;
    point p;
    #define ls(p) tree[p].son[0]
    #define rs(p) tree[p].son[1]
}tree[N];
int root,tot,st[N],top;
int bt(){
    int now=++tot;
    // if(top)now=st[top--];
    // else now=++tot;
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
void ren(int now){
    if(!now)return ;
    tp[++cnt]=tree[now].p;
    st[++top]=now;
    ren(ls(now));
    ren(rs(now));
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
        ren(now);
        now=rb(1,cnt,d);
    }
    return;
}
void insert(int &now,point x,int d){
    if(!now){
        now=bt();
        tree[now].p=x;
        pu(now);
        return ;
    }
    if(x.zb[d]<=tree[now].p.zb[d])insert(ls(now),x,d^1);
    else insert(rs(now),x,d^1);
    pu(now);
    ck(now,d);
    return ;
}
struct an{
    int i,res;
};
bool operator <(const an &x,const an &y){
    return x.res>y.res||(x.res==y.res&&x.i<y.i);
}
priority_queue <an> q;
int disy(point x,int now){
    int res=0;
    for(int i=0;i<2;i++){
        res+=max((x.zb[i]-tree[now].minn[i])*(x.zb[i]-tree[now].minn[i]),(tree[now].maxn[i]-x.zb[i])*(tree[now].maxn[i]-x.zb[i]));
    }
    return res;
}
int dist(point x,point y){
    return (x.zb[0]-y.zb[0])*(x.zb[0]-y.zb[0])+(x.zb[1]-y.zb[1])*(x.zb[1]-y.zb[1]);
}
void cha(int now,point x){
    // cout<<now<<" "<<x.zb[0]<<" "<<x.zb[1]<<endl;
    int res=dist(x,tree[now].p);
    if(res>q.top().res||(res==q.top().res&&tree[now].p.id<q.top().i)){
        q.pop();
        q.push({tree[now].p.id,res});
    }
    int dl=-inf,dr=-inf;
    if(ls(now))dl=disy(x,ls(now));
    if(rs(now))dr=disy(x,rs(now));
    if(dl>dr){
        if(dl>=q.top().res&&ls(now))cha(ls(now),x);
        if(dr>=q.top().res&&rs(now))cha(rs(now),x);
    }
    else{
        if(dr>=q.top().res&&rs(now))cha(rs(now),x);
        if(dl>=q.top().res&&ls(now))cha(ls(now),x);
    }
    return ;
}
signed main(){
    int n=read(),k=read();
    for(int i=1;i<=n;i++){
        a[i].zb[0]=read(),a[i].zb[1]=read(),a[i].id=i;
        tp[i]=a[i];
    }
    root=rb(1,n,0);
    for(int j=1;j<=2*k;j++)q.push({0,-1});
    for(int i=1;i<=n;i++){
        int x=a[i].zb[0],y=a[i].zb[1];
        // cout<<"111"<<endl;
        cha(root,point(x,y,0));
    }
    write(q.top().res);
    puts("");
    return 0;
}
