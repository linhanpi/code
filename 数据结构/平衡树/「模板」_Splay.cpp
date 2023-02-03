#include<bits/stdc++.h>
#define int long long
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
const int inf=INT_MAX;
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
struct splay_tree{
    int val,si,cnt;
    int son[2],fa;
    void init(int _fa,int _val){
        fa=_fa,val=_val;
        si=cnt=1;
    }
    #define val(p) tree[p].val
    #define si(p) tree[p].si
    #define cnt(p) tree[p].cnt
    #define son(p,i) tree[p].son[i]
    #define fa(p) tree[p].fa
}tree[N+M];
int root,tot;
void pu(int p){
    si(p)=si(son(p,0))+si(son(p,1))+cnt(p);
    return ;
}
void rotate(int x){
    int fa=fa(x),gfa=fa(fa);
    int k=son(fa,1)==x,kfa=son(gfa,1)==fa;
    son(gfa,kfa)=x,fa(x)=gfa;               // x 替代 fa
    son(fa,k)=son(x,k^1),fa(son(x,k^1))=fa; // x 的 k^1 son 替代 fa 的 k son
    son(x,k^1)=fa,fa(fa)=x;                 //fa 替代 x 的 k^1 son
    pu(fa),pu(x);
    return ;
}
void splay(int x,int p){
    while(fa(x)!=p){
        int fa=fa(x),gfa=fa(fa);
        if(gfa!=p){
            if((son(fa,1)==x)^(son(gfa,1)==fa))rotate(x);
            else rotate(fa);
        }
        rotate(x);
    }
    if(!p) root=x;
    return ;
}
void insert(int x){
    int p=root,fa=0;
    while(p){
        // cout<<"p "<<p<<endl;
        if(val(p)==x){
            cnt(p)++;
            si(p)++;
            splay(p,0);
            return ;
        }
        fa=p,p=son(p,val(fa)<x);
    }
    p=++tot;
    if(fa)son(fa,val(fa)<x)=p;
    tree[p].init(fa,x);
    splay(p,0);
    return ;
}
int qq(int x){
    int p=root,fa=fa(p);
    while(p){
        if(val(p)<x)fa=p,p=son(p,1);
        else p=son(p,0);
    }
    splay(fa,0);
    return fa;
}
int hj(int x){
    int p=root,fa=fa(p);
    while(p){
        // cout<<"p "<<p<<" "<<x<<" "<<val(p)<<" "<<son(p,0)<<" "<<son(p,1)<<endl;
        if(val(p)>x)fa=p,p=son(p,0);
        else p=son(p,1);
    }
    splay(fa,0);
    return fa;
}
void erase(int x){
    int pre=qq(x),hou=hj(x);
    splay(pre,0);
    splay(hou,pre);
    if(cnt(son(hou,0))>1)cnt(son(hou,0))--,si(son(hou,0))--;
    else fa(son(hou,0))=0,son(hou,0)=0;
    pu(hou);
    pu(pre);
    return ;
}
int chak(int x){
    // int pre=qq(x+1);
    // x=val(pre);
    int p=root;
    int res=0;
    while(p){
        if(val(p)==x){
            res+=si(son(p,0));
            splay(p,0);
            return res;
        }
        if(val(p)<x){
            res+=si(son(p,0))+cnt(p);
            p=son(p,1);
        }
        else p=son(p,0);
    }
    return res;
}
int kth(int x){
    int k=x+1;
    int p=root;
    while(p){
        if(si(son(p,0))+cnt(p)<k){
            k-=si(son(p,0))+cnt(p);
            p=son(p,1);
        }
        else if(si(son(p,0))>=k)p=son(p,0);
        else{
            splay(p,0);
            return val(p);
        }
    }
    return 0;
}
signed main(){
    int n=read(),m=read();
    insert(inf),insert(-inf);
    for(int i=1;i<=n;i++){
        int x=read();
        insert(x);
    }
    int last=0;
    int ans=0;
    for(int i=1;i<=m;i++){
        int pos=read(),x=read();
        x^=last;
        if(pos==1)insert(x);
        if(pos==2)erase(x);
        if(pos==3)last=chak(x),ans^=last;
        if(pos==4)last=kth(x),ans^=last;
        if(pos==5)last=val(qq(x)),ans^=last;
        if(pos==6)last=val(hj(x)),ans^=last;
    }
    cout<<ans<<endl;
    return 0;
}