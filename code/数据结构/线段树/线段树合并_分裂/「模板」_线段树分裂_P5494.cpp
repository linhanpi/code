/*
 * @Author: watering_penguin 
 * @Date: 2023-02-03 21:49:51 
 * @Last Modified by:   watering_penguin 
 * @Last Modified time: 2023-02-03 21:49:51 
 */
#include<bits/stdc++.h>
// #define int long long
#define ll long long
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
const int N=2e5+5;
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
struct st{
    int ls,rs;
    long long sum;
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
    #define sum(p) tree[p].sum
}tree[N<<5];
int top,toot,st[N<<5];
void shan(int x){
    st[++top]=x;
    // ls(x)=rs(x)=sum(x)=0;
    return ;
}
int bt(){
    int tot=top?st[top--]:++toot;
    ls(tot)=rs(tot)=sum(tot)=0;
    return tot;
}
void pu(int p){
    if(!ls(p)&&!rs(p))sum(p)=0;
    else if(!ls(p))sum(p)=sum(rs(p));
    else if(!rs(p))sum(p)=sum(ls(p));
    else sum(p)=sum(ls(p))+sum(rs(p));
    return ;
}
int a[N];
void bd(int p,int l,int r){
    if(l==r){
        sum(p)=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    ls(p)=bt();
    rs(p)=bt();
    bd(ls(p),l,mid);
    bd(rs(p),mid+1,r);
    pu(p);
    return ;
}
void add(int p,int l,int r,int pos,int x){
    if(l==r){
        sum(p)+=x;
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        if(!ls(p))ls(p)=bt();
        add(ls(p),l,mid,pos,x);
    }
    else{
        if(!rs(p))rs(p)=bt();
        add(rs(p),mid+1,r,pos,x);
    }
    pu(p);
    return ;
}
int kth(int p,int l,int r,int k){
    if(l==r){
        return l;
    }
    int mid=(l+r)>>1;
    if(sum(ls(p))>=k)return kth(ls(p),l,mid,k);
    else return kth(rs(p),mid+1,r,k-sum(ls(p)));
}
long long ask(int p,int l,int r,int L,int R){
    if(R<l||r<L)return 0;
    if(L<=l&&r<=R){
        return sum(p);
    }
    int mid=(l+r)>>1;
    long long res=0;
    if(L<=mid&&ls(p))res+=ask(ls(p),l,mid,L,R);
    if(R>mid&&rs(p))res+=ask(rs(p),mid+1,r,L,R);
    return res;
}
int hb(int p,int q,int l,int r){
    if(!p||!q)return p+q;
    if(l==r){
        sum(p)+=sum(q);
        shan(q);
        return p;
    }
    int mid=(l+r)>>1;
    ls(p)=hb(ls(p),ls(q),l,mid);
    rs(p)=hb(rs(p),rs(q),mid+1,r);
    pu(p);
    shan(q);
    return p;
}
void fl(int p,int &q,long long k){
    // cout<<"p "<<p<<" "<<q<<" "<<k<<endl;
    if(p==0)return ;
    q=bt();
    long long v=sum(ls(p));
    if(k>v)fl(rs(p),rs(q),k-sum(ls(p)));
    else swap(rs(p),rs(q));
    if(v>k)fl(ls(p),ls(q),k);
    sum(q)=sum(p)-k;
    sum(p)=k;
    return ;
}
int root[N],cnt=1;
signed main(){
    // freopen("P5494_11.in","r",stdin);
    int n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    root[1]=bt();
    bd(root[1],1,n);
    while(m--){
        int opt=read();
        if(opt==0){
            int p=read(),x=read(),y=read();
            long long k1=ask(root[p],1,n,1,y),k2=ask(root[p],1,n,x,y);
            // cout<<"k1 k2 "<<k1<<" "<<k2<<endl;
            fl(root[p],root[++cnt],k1-k2);
            // cout<<"111\n";
            int tmp=0;
            fl(root[cnt],tmp,k2);
            // cout<<"222\n";
            root[p]=hb(root[p],tmp,1,n);
            // cout<<"333\n"<<endl;
        }
        else if(opt==1){
            int p=read(),t=read();
            root[p]=hb(root[p],root[t],1,n);
        }
        else if(opt==2){
            int p=read(),x=read(),q=read();
            add(root[p],1,n,q,x);
        }
        else if(opt==3){
            int p=read(),x=read(),y=read();
            write(ask(root[p],1,n,x,y));
            puts("");
        }
        else{
            int p=read(),k=read();
            if(sum(root[p])<k){
                puts("-1");
                continue;
            }
            write(kth(root[p],1,n,k));
            puts("");
        }
    }
	return 0;
}
/*
*/