#include<bits/stdc++.h>
#define int unsigned long long//信仰
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
const int N=1e6+5;
const int M=1e2+5;
const int inf=INT_MAX;
const int base=27;
const int mod=1e4+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
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
struct node{
    int a,b;
    node(int a_,int b_){
        a=a_,b=b_;
    }
};
char s[N];
int son[N][2],val[N],sum[N],rk[N],si[N],l[N];
int tot,root;
inline int bt(){
    ++tot;
    son[tot][0]=son[tot][1]=val[tot]=0;
    si[tot]=1;
    // rk[tot]=ran_int(1,1145141919);
    rk[tot]=rand();
    return tot;
}
inline void pu(int now){
    si[now]=si[son[now][0]]+si[son[now][1]]+1;
    sum[now]=sum[son[now][1]]+val[now]*l[si[son[now][1]]]+sum[son[now][0]]*l[si[son[now][1]]+1];
}
node fl(int now,int k){
    if(!now)return node(0,0);
    if(si[son[now][0]]+1<k){
        node t=fl(son[now][1],k-si[son[now][0]]-1);
        son[now][1]=t.a;
        pu(now);
        return node(now,t.b);
    }
    else{
        node t=fl(son[now][0],k);
        son[now][0]=t.b;
        pu(now);
        return node(t.a,now);
    }
}
int hb(int p,int q){
    if(!p||!q)return p+q;
    if(rk[p]<rk[q]){
        son[p][1]=hb(son[p][1],q);
        pu(p);
        return p;
    }
    else{
        son[q][0]=hb(p,son[q][0]);
        pu(q);
        return q;
    }
}
inline int cha(int l,int r){
    node t1=fl(root,r+1);
    node t2=fl(t1.a,l);
    int res=sum[t2.b];
    root=hb(hb(t2.a,t2.b),t1.b);
    return res;
}
inline int bd(int l,int r){
    if(l>r)return 0;
    if(l==r){
        int p=bt();
        val[p]=s[l]-'a';
        pu(p);
        return p;
    }
    int mid=(l+r)>>1;
    int p=bt();
    son[p][0]=bd(l,mid-1);
    son[p][1]=bd(mid+1,r);
    val[p]=s[mid]-'a';
    pu(p);
    return p;
}
void ycl(){
    l[0]=1;
    for(int i=1;i<=N-5;i++){
        l[i]=l[i-1]*base;
    }
    return ;
}
bool ck(int x,int y,int mid){
    return cha(x,x+mid-1)==cha(y,y+mid-1);
}
void gai(int x,char k){
    node t1=fl(root,x+1);
    node t2=fl(t1.a,x);
    val[t2.b]=k-'a';
    pu(t2.b);
    root=hb(hb(t2.a,t2.b),t1.b);
    return ;
}
void insert(int x,char k){
    node t1=fl(root,x+1);
    int p=bt();
    val[p]=k-'a';
    pu(p);
    root=hb(hb(t1.a,p),t1.b);
    return ;
}
signed main(){
	ycl();
    scanf("%s",s+1);
    int n=strlen(s+1);
    root=bd(1,n);
    int q=read();
    while(q--){
        char op;cin>>op;
        if(op=='Q'){
            int x=read(),y=read();
            if(x>y)swap(x,y);
            int l=0,r=n-y+1;
            while(l<r){
                int mid=(l+r+1)>>1;
                if(ck(x,y,mid))l=mid;
                else r=mid-1;
            }
            cout<<l<<endl;
        }
        else if(op=='R'){
            int x=read();char ch;cin>>ch;
            gai(x,ch);
        }
        else{
            n++;
            int x=read();char ch;cin>>ch;
            insert(x,ch);
        }
    }
	return 0;
}
