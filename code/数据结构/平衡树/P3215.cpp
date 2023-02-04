/*
 * @Author: watering_penguin 
 * @Date: 2023-02-04 14:03:47 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-04 16:45:55
 */
#include<bits/stdc++.h>
//#define int long long
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
const int M=1e8+5;
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
struct node{
    int a,b;
    node(int a_=0,int b_=0){
        a=a_,b=b_;
    }
};
int son[N][2],si[N],rk[N],val[N];
int qmax[N],qmin[N],hmax[N],hmin[N];
int fg[N],sw[N],fan[N],sum[N];
int root,tot;
int bt(){
    ++tot;
    rk[tot]=rand();
    si[tot]=1;
    qmax[tot]=hmax[tot]=0;
    qmin[tot]=hmin[tot]=inf;
    return tot;
}
void pdsw(int now){
    swap(son[now][0],son[now][1]);
    swap(qmax[now],hmax[now]);
    swap(qmin[now],hmin[now]);
    sw[now]^=1;
    return ;
}
void pdfg(int now,int k){
    if(k>0){
        val[now]=k,fg[now]=k;
        sum[now]=val[now]*si[now];
        qmax[now]=hmax[now]=sum[now];
        qmin[now]=hmin[now]=0;
    }
    if(k<0){
        val[now]=k,fg[now]=k;
        sum[now]=val[now]*si[now];
        qmax[now]=hmax[now]=0;
        qmin[now]=hmin[now]=sum[now];
    }
    // cout<<"now "<<now<<" "<<val[now]<<" "<<sum[now]<<" "<<fg[now]<<endl;

    return ;
}
void pdfan(int now){
    val[now]=-val[now];
    sum[now]=-sum[now];
    swap(qmax[now],qmin[now]);
    qmin[now]=-qmin[now],qmax[now]=-qmax[now];
    swap(hmax[now],hmin[now]);
    hmin[now]=-hmin[now],hmax[now]=-hmax[now];
    fan[now]^=1;
    fg[now]=-fg[now];
    return ;
}
void pu(int now){
    sum[now]=sum[son[now][0]]+sum[son[now][1]]+val[now];
    si[now]=si[son[now][0]]+si[son[now][1]]+1;
    qmax[now]=max(qmax[son[now][0]],sum[son[now][0]]+val[now]+qmax[son[now][1]]);
    qmin[now]=min(qmin[son[now][0]],sum[son[now][0]]+val[now]+qmin[son[now][1]]);
    hmax[now]=max(hmax[son[now][1]],sum[son[now][1]]+val[now]+hmax[son[now][0]]);
    hmin[now]=min(hmin[son[now][1]],sum[son[now][1]]+val[now]+hmin[son[now][0]]);
    return ;
}
void pd(int now){
    if(fan[now]){
        if(son[now][0])pdfan(son[now][0]);
        if(son[now][1])pdfan(son[now][1]);
        fan[now]=0;
    }
    if(fg[now]){
        if(son[now][0])pdfg(son[now][0],fg[now]);
        if(son[now][1])pdfg(son[now][1],fg[now]);
        fg[now]=0;
    }
    if(sw[now]){
        if(son[now][0])pdsw(son[now][0]);
        if(son[now][1])pdsw(son[now][1]);
        sw[now]=0;
    }
    return ;
}
int hb(int now1,int now2){
    if(!now1||!now2)return now1+now2;
    pd(now1);
    pd(now2);
    if(rk[now1]<rk[now2]){
        // pd(now1);
        son[now1][1]=hb(son[now1][1],now2);
        pu(now1);
        return now1;
    }
    else{
        // pd(now2);
        son[now2][0]=hb(now1,son[now2][0]);
        pu(now2);
        return now2;
    }
}
node fl(int now,int k){
    if(!now)return node(0,0);
    pd(now);
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
int a[N];
int bd(int l,int r){
    if(l==r){
        int p=bt();
        sum[p]=val[p]=a[l];
        if(val[p]==1){
            qmax[p]=hmax[p]=1;
        }
        else qmin[p]=hmin[p]=-1;
        return p;
    }
    int mid=(l+r)>>1;
    return hb(bd(l,mid),bd(mid+1,r));
}
void Re(int a,int b,int c){
    node t1=fl(root,b+1);
    node t2=fl(t1.a,a);
    pdfg(t2.b,c);
    // cout<<"c "<<c<<endl;
    root=hb(hb(t2.a,t2.b),t1.b);
    return ;
}
void Sw(int a,int b){
    node t1=fl(root,b+1);
    node t2=fl(t1.a,a);
    pdsw(t2.b);
    root=hb(hb(t2.a,t2.b),t1.b);
    return ;
}
void In(int a,int b){
    node t1=fl(root,b+1);
    node t2=fl(t1.a,a);
    pdfan(t2.b);
    root=hb(hb(t2.a,t2.b),t1.b);
    return ;
}
int Qu(int a,int b){
    node t1=fl(root,b+1);
    node t2=fl(t1.a,a);
    int res=ceil(1.0*(qmax[t2.b])/2)+ceil(1.0*(abs(hmin[t2.b]))/2);
    root=hb(hb(t2.a,t2.b),t1.b);
    return res;
}
void pt(int now){
	pd(now);
	if(son[now][0]){
		pt(son[now][0]);
	}
	cout<<(val[now]==-1)?'(':')';
	if(son[now][1]){
		pt(son[now][1]);
	}
}
char Q[N];
signed main(){
    srand(time(0));
    int n=read(),q=read();
    for(int i=1;i<=n;i++){
        char ch;cin>>ch;
        if(ch=='(')a[i]=-1;
        else a[i]=1;
    }
    root=bd(1,n);
    while(q--){
        scanf("%s",Q+1);
        if(Q[1]=='R'){
            int l=read(),r=read(),x;char ch;cin>>ch;
            if(ch=='(')x=-1;
            else x=1;
            Re(l,r,x);
        }
        if(Q[1]=='S'){
            int l=read(),r=read();
            Sw(l,r);
        }
        if(Q[1]=='I'){
            int l=read(),r=read();
            In(l,r);
        }
        if(Q[1]=='Q'){
            int l=read(),r=read();
            write(Qu(l,r));
            puts("");
        }
        // pt(root);
        // puts("");
    }
	return 0;
}
/*
*/