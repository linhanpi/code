/*
 * @Author: watering_penguin 
 * @Date: 2023-02-24 18:54:57 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-24 20:19:19
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
const int N=2e5+5;
const int M=6e4+5;
const int mo=7000007;
const int inf=1e16+9;
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
struct KDT{
    int son[2],minn[2],maxn[2],sum,si;
    point p;
    #define ls(p) tree[p].son[0]
    #define rs(p) tree[p].son[1]
}tree[N];
int tot,root,top,st[N];
bool cmpx(point &a,point &b){
    return a.zb[0]<b.zb[0];
}
bool cmpy(point &a,point &b){
    return a.zb[1]<b.zb[1];
}
int bt(){
    int now;
    if(top)now=st[top--];
    else now=++tot;
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
    tree[now].sum=tree[now].p.val+tree[ls(now)].sum+tree[rs(now)].sum;
    tree[now].si=tree[ls(now)].si+tree[rs(now)].si+1;
    return ;
}
int cnt;
void shan(int now){
    if(!now)return ;
    tp[++cnt]=tree[now].p;
    st[++top]=now;
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
    if(tree[ls(now)].si>alpha*tree[now].si||tree[rs(now)].si>alpha*tree[now].si){
        cnt=0;
        shan(now);
        now=rb(1,tree[now].si,d);
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
    else insert(rs(now),x,d^1);
    pu(now);
    ck(now,d);
    return ;
}
bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2){
    return x1<=X1&&x2>=X2&&y1<=Y1&&y2>=Y2;
}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2){
    return x1>X2||x2<X1||y1>Y2||y2<Y1;
}
int cha(int now,int x1,int y1,int x2,int y2){
    if(!now)return 0;
    if(in(x1,y1,x2,y2,tree[now].minn[0],tree[now].minn[1],tree[now].maxn[0],tree[now].maxn[1]))return tree[now].sum;
    if(out(x1,y1,x2,y2,tree[now].minn[0],tree[now].minn[1],tree[now].maxn[0],tree[now].maxn[1]))return 0;
    int res=0;
    if(in(x1,y1,x2,y2,tree[now].p.zb[0],tree[now].p.zb[1],tree[now].p.zb[0],tree[now].p.zb[1]))res+=tree[now].p.val;
    res+=cha(ls(now),x1,y1,x2,y2)+cha(rs(now),x1,y1,x2,y2);
    return res;
}
signed main(){
    int n=read();
    int ans=0;
    while(1){
        int op=read();
        if(op==3)break;
        if(op==1){
            int x=read()^ans,y=read()^ans,v=read()^ans;
            insert(root,point(x,y,v),0);
        }
        else{
            int x1=read()^ans,y1=read()^ans,x2=read()^ans,y2=read()^ans;
            ans=cha(root,x1,y1,x2,y2);
            write(ans);
            puts("");
        }
    }
    return 0;
}
