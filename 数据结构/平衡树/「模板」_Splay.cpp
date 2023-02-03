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
int n;
int root,tot;
struct balance_tree{
    int dist,size,cnt;
    int son[2],fa;
    void init(int _fa,int _dist){
        dist=_dist,fa=_fa;
        size=1,cnt=1;
    }
}tr[N];
void pushup(int p){
    tr[p].size=tr[tr[p].son[0]].size+tr[tr[p].son[1]].size+tr[p].cnt;
    return;
}
int max(int x,int y){
    return x>y?x:y;
}
int min(int x,int y){
    return x<y?x:y;
}
void rotate(int x){
    int y=tr[x].fa,z=tr[y].fa;
    int k=tr[y].son[1]==x;
    tr[z].son[tr[z].son[1]==y]=x,tr[x].fa=z;
    tr[y].son[k]=tr[x].son[k^1],tr[tr[x].son[k^1]].fa=y;
    tr[x].son[k^1]=y,tr[y].fa=x;
    pushup(y),pushup(x);
    return;
}
void splay(int x,int p){
    while(tr[x].fa!=p){
        int y=tr[x].fa;
		int z=tr[y].fa;
        if(z!=p){
        	if((tr[z].son[1]==y)^(tr[y].son[1]==x)) rotate(x);
       		else rotate(y);
		}
        rotate(x);
    }
    if(!p) root=x;
    return;
}
void insert(int x){
    int p=root,fa=0;
    while(p){
        if(tr[p].dist==x){
            tr[p].cnt++;
			tr[p].size++;
            splay(p,0);
            return;
        }
        fa=p,p=tr[p].son[tr[p].dist<x];
    }
    p=++tot;
    if(fa) tr[fa].son[tr[fa].dist<x]=p;
    tr[p].init(fa,x);
    splay(p,0);
    return;
}
int get_pre(int x){
	int p=root,fa=tr[p].fa;
	while(p){
	    if(tr[p].dist<x)fa=p,p=tr[p].son[1];
	    else p=tr[p].son[0];
	}
	splay(fa,0);
	return fa;
}
int get_suc(int x){
    int p=root,fa=tr[p].fa;
    while(p){
        if(tr[p].dist>x)fa=p,p=tr[p].son[0];
        else p=tr[p].son[1];
    }
    splay(fa,0);
    return fa;
}
void erase(int x){
    int pre=get_pre(x),suc=get_suc(x);
    splay(pre,0);
    splay(suc,pre);
    if(tr[tr[suc].son[0]].cnt>1) tr[tr[suc].son[0]].cnt--,tr[tr[suc].son[0]].size--;
    else tr[tr[suc].son[0]].fa=0,tr[suc].son[0]=0;
	pushup(suc);
	pushup(pre);
    return;
}
int query(int x){
	int p=root;
	int res=0;
	while(p){
		if(tr[p].dist==x){
			res+=tr[tr[p].son[0]].size;
			splay(p,0);
			return res;
		}
		if(tr[p].dist<x){
			res+=tr[tr[p].son[0]].size;
			res+=tr[p].cnt;
			p=tr[p].son[1];
		}else p=tr[p].son[0];
	}
	return res;
}
int rk(int x){
	int k=x+1;
	int p=root;
	while(p){
	    if(tr[tr[p].son[0]].size+tr[p].cnt<k){
	        k-=tr[tr[p].son[0]].size+tr[p].cnt;
	        p=tr[p].son[1];
	    }else if(tr[tr[p].son[0]].size>=k) p=tr[p].son[0];
	    else{
			splay(p,0);
			return tr[p].dist;
		}
	}
	return 0;
}
signed main(){
    n=read();
    insert(inf),insert(-inf);
    for(int i=1;i<=n;++i){
        int pos,x;
        pos=read(),x=read();
        if(pos==1) insert(x);
        if(pos==2) erase(x);
        if(pos==3) printf("%d\n",query(x));
        if(pos==4) printf("%d\n",rk(x));
        if(pos==5) printf("%d\n",tr[get_pre(x)].dist);
        if(pos==6) printf("%d\n",tr[get_suc(x)].dist);
    }
    return 0;
}