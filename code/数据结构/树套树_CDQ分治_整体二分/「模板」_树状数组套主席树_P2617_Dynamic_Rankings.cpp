#include<bits/stdc++.h>
// #define int long long
// #define ll long long
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
struct hjt_tree{
    int v,ls,rs;
    #define v(p) tree[p].v
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
}tree[N*400];
int tot;
struct xw{
    int l,r,k;
    int pos,t;
    bool opt;
}q[N];
int a[N],len,c[N<<1],root[N],n,cnt[2],tmp[2][20];
void cg(int &now,int l,int r,int pos,int v){
    if(!now)now=++tot;
    v(now)+=v;
    if(l==r)return ;
    int mid=(l+r)>>1;
    if(pos<=mid)cg(ls(now),l,mid,pos,v);
    else cg(rs(now),mid+1,r,pos,v);
    return ;
}
void pcg(int x,int v){
    int k=lower_bound(c+1,c+len+1,a[x])-c;
    for(int i=x;i<=n;i+=lowbit(i)){
        cg(root[i],1,len,k,v);
    }
    return ;
}
int cha(int l,int r,int k){
    if(l==r)return l;
    int mid=(l+r)>>1,sum=0;
    for(int i=1;i<=cnt[1];i++)sum+=v(ls(tmp[1][i]));
    for(int i=1;i<=cnt[0];i++)sum-=v(ls(tmp[0][i]));
    if(k<=sum){
        for(int i=1;i<=cnt[1];i++)tmp[1][i]=ls(tmp[1][i]);
        for(int i=1;i<=cnt[0];i++)tmp[0][i]=ls(tmp[0][i]);
        return cha(l,mid,k);
    }
    else{
        for(int i=1;i<=cnt[1];i++)tmp[1][i]=rs(tmp[1][i]);
        for(int i=1;i<=cnt[0];i++)tmp[0][i]=rs(tmp[0][i]);
        return cha(mid+1,r,k-sum);
    }
}
int pcha(int l,int r,int k){
    // memset(tmp,0,sizeof(tmp));
    cnt[0]=cnt[1]=0;
    for(int i=r;i;i-=lowbit(i))tmp[1][++cnt[1]]=root[i];
    for(int i=l-1;i;i-=lowbit(i))tmp[0][++cnt[0]]=root[i];
    return cha(1,len,k);
}
signed main(){
    n=read();
    int Q=read();
    for(int i=1;i<=n;i++)a[i]=read(),c[++len]=a[i];
    for(int i=1;i<=Q;i++){
        char opt;cin>>opt;
        q[i].opt=(opt=='Q');
        if(q[i].opt)q[i].l=read(),q[i].r=read(),q[i].k=read();
        else q[i].pos=read(),q[i].t=read(),c[++len]=q[i].t;
    }
    sort(c+1,c+len+1);
    len=unique(c+1,c+len+1)-c-1;
    for(int i=1;i<=n;i++)pcg(i,1);
    for(int i=1;i<=Q;i++){
        if(q[i].opt){
            write(c[pcha(q[i].l,q[i].r,q[i].k)]);
            puts("");
        }
        else{
            pcg(q[i].pos,-1);
            a[q[i].pos]=q[i].t;
            pcg(q[i].pos,1);
        }
    }
	return 0;
}
/*
*/