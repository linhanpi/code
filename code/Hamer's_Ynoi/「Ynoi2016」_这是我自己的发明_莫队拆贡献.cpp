/*
 * @Author: watering_penguin 
 * @Date: 2023-02-09 15:31:51 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-09 18:50:02
 */
#include<bits/stdc++.h>
#define int long long
// #define uint unsigned int
// #define rint register int
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
const int N=5e5+5;
const int M=(1<<26)+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=51061;
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
int si[N],fa[N],son[N],st[N],ed[N],num,ys[N],tp[N],dep[N],d[N];
vector <int> v[N];
map <int,int> mp[N];
void dfs1(int now){
    si[now]=1;
    dep[now]=dep[fa[now]]+1;
    for(int y:v[now]){
        if(y==fa[now])continue;
        fa[y]=now;
        dfs1(y);
        si[now]+=y;
        if(si[y]>si[son[now]]){
            son[now]=y;
        }
    }
    return ;
}
void dfs2(int now,int top){
    tp[now]=top;
    st[now]=++num;
    ys[num]=now;
    // if(!son[now])return ;
    if(son[now])dfs2(son[now],top);
    for(int y:v[now]){
        if(y!=son[now]&&y!=fa[now])dfs2(y,y);
        if(y!=fa[now]){
            mp[now][ed[y]]=y;
        }
    }
    ed[now]=num;
    return ;
}
int chak(int x,int k){
    // if(k>=dep[x])return 0;
    while(dep[tp[x]]>k){
        x=fa[tp[x]];
    }
    return ys[st[x]-(dep[x]-k)];
}
struct node{
    int l,r,i,op;
}no[N*4];
int kuaichang,cnt;
int bl[N*4];
bool operator <(const node &x,const node &y){
    // if((x.l/kuaichang)==(y.l/kuaichang)){
    //     return ((x.l/kuaichang)&1)?x.r>y.r:x.r<y.r;
    // }
    // if(x.l/kuaichang<y.l/kuaichang){
    //     return x.r<y.r;
    // }
    // return x.l/kuaichang<y.l/kuaichang;
    if(bl[x.l]==bl[y.l])return x.r<y.r;
    return bl[x.l]<bl[y.l];
}
int tong[N][2],res,ans[N],c[N],a[N],tot,qian[N];
void jia(int x,int k){
    x=ys[x];
    res+=tong[a[x]][k^1];
    tong[a[x]][k]++;
    return ;
}
void jian(int x,int k){
    x=ys[x];
    res-=tong[a[x]][k^1];
    tong[a[x]][k]--;
    return ;
}
signed main(){
    int n=read(),m=read();
    // kuaichang=max(1ll,(int)(n/sqrt(4*m)));
    kuaichang=sqrt(n);
    for(int i=1;i<=4*m;i++){
        bl[i]=i/kuaichang;
    }
    for(int i=1;i<=n;i++)a[i]=read(),d[i]=a[i];
    sort(d+1,d+n+1);
    int len=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(d+1,d+len+1,a[i])-d;
    for(int i=1;i<n;i++){
        int a=read(),b=read();
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs1(1);
    dfs2(1,1);
    // for(int i=1;i<=n;i++){
    //     cout<<"i "<<i<<" "<<st[i]<<" "<<ed[i]<<endl;
    // }
    // return 0;
    for(int i=1;i<=n;i++){
        c[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        qian[i]=qian[i-1]+c[a[ys[i]]];
    }
    // memset(tong,0,sizeof(tong));
    int root=1;
    for(int i=1;i<=m;i++){
        int op=read();
        if(op==1){
            root=read();
        }
        else{
            ++tot;
            int x=read(),y=read();
            int tx=st[x]<=st[root]&&ed[root]<=ed[x];
            if(x==root)x=1,tx=0;
            int ty=st[y]<=st[root]&&ed[root]<=ed[y];
            if(y==root)y=1,ty=0;
            // cout<<"tx ty "<<tx<<" "<<ty<<endl;
            if(tx)x=mp[x].lower_bound(st[root])->second;
            if(ty)y=mp[y].lower_bound(st[root])->second;
            // cout<<"x y "<<x<<" "<<y<<endl;
            int lx=st[x]-1,ly=st[y]-1,rx=ed[x],ry=ed[y];
            if(tx&&ty)ans[tot]=qian[n];
            if(tx)ans[tot]+=(qian[ry]-qian[ly])*(tx==ty?-1:1);
            if(ty)ans[tot]+=(qian[rx]-qian[lx])*(tx==ty?-1:1);
            no[++cnt]={rx,ry,tot,tx==ty?1:-1};
            no[++cnt]={rx,ly,tot,tx==ty?-1:1};
            no[++cnt]={lx,ry,tot,tx==ty?-1:1};
            no[++cnt]={lx,ly,tot,tx==ty?1:-1};
        }
    }
    // return 0;
    // cout<<cnt<<endl;
    // int tep=cnt;
    // int kk=0;
    // while(tep/10!=0){
    //     tep/=10;
    //     kk++;
    // }
    // cout<<tep<<endl;
    // return 0;
    sort(no+1,no+cnt+1);
    // return 0;
    int l=0,r=0;
    for(int i=1;i<=cnt;i++){
        // if(no[i].l<0||no[i].r<0){
        //     cout<<"@"<<endl;
        //     return 0;
        // }
        while(l<no[i].l)jia(++l,0);
        while(r<no[i].r)jia(++r,1);
        while(l>no[i].l)jian(l--,0);
        while(r>no[i].r)jian(r--,1);
        // cout<<"l r "<<l<<" "<<r<<" "<<res<<" "<<no[i].op<<" "<<no[i].i<<endl;
        ans[no[i].i]+=res*no[i].op;
    }
    // return 0;
    for(int i=1;i<=tot;i++){
        write(ans[i]);
        puts("");
    }
    return 0;
}
/*
2 9
1 1
1 2
2 1 1
2 1 2
2 1 1
2 1 2
2 1 1
2 1 2
2 1 1
2 1 2
2 1 1
*/