/*
 * @Author: watering_penguin 
 * @Date: 2023-02-06 10:45:47 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-06 11:22:20
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
struct node{
    int ls,rs,sum;
    #define ls(p) tree[p].ls
    #define rs(p) tree[p].rs
    #define sum(p) tree[p].sum
}tree[N*60];
int tot,root,L,R;
int bt(){
    ++tot;
    return tot;
}
void insert(int p,int l,int r,int pos){
    // cout<<"p "<<p<<" "<<l<<" "<<r<<" "<<pos<<endl;
    sum(p)++;
    if(l==r)return ;
    int mid=(l+r)>>1;
    if(pos<=mid){
        if(!ls(p))ls(p)=bt();
        insert(ls(p),l,mid,pos);
    }
    else{
        if(!rs(p))rs(p)=bt();
        insert(rs(p),mid+1,r,pos);
    }
    return ;
}
int ask(int p,int pos,int l,int r){
    if(!sum(p))return 0;
    if(l==r)return sum(p);
    int mid=(l+r)>>1;
    if(pos<=mid)return ask(ls(p),pos,l,mid);
    else return ask(rs(p),pos,mid+1,r)+sum(ls(p));
}
int find(int p,int k,int l,int r){
    if(l==r)return l;
    int mid=(l+r)>>1;
    int num=max(0,min(R,mid)-max(L,l)+1-sum(ls(p)));
    if(k<=num)return find(ls(p),k,l,mid);
    else return find(rs(p),k-num,mid+1,r);
}
map <int,int> mp1,mp2;
int ans;
void work1(int x){
    int now=(mp1.find(x)==mp1.end())?x:mp1[x];
    ans=now-L+1-ask(root,now,-inf,inf);
    // cout<<"now "<<now<<endl;
    insert(root,-inf,inf,now);
    // cout<<"now "<<now<<endl;
    mp1[x]=--L;
    mp2[L]=x;
    return ;
}
void work2(int x){
    int now=(mp1.find(x)==mp1.end())?x:mp1[x];
    ans=now-L+1-ask(root,now,-inf,inf);
    // cout<<"now "<<now<<endl;
    insert(root,-inf,inf,now);
    // cout<<"now "<<now<<endl;
    mp1[x]=++R;
    mp2[R]=x;
    return ;
}
inline void ask(int x){
    ans=find(root,x,-inf,inf);
    ans=(mp2.find(ans)==mp2.end())?ans:mp2[ans];
    return ;
}
inline void cg(int x,int y){
    int now=(mp1.find(x)==mp1.end())?x:mp1[x];
    ans=now-L+1-ask(root,now,-inf,inf);
    mp1[y]=now;
    mp2[now]=y;
    return  ;
}
signed main(){
    int n=read(),m=read();
    L=1,R=n;
    root=bt();
    while(m--){
        int pos=read();
        if(pos==1){
            int x=read(),y=read();
            cg(x-ans,y-ans);
        }
        if(pos==2){
            int x=read();
            work1(x-ans);
        }
        if(pos==3){
            int x=read();
            work2(x-ans);
        }
        if(pos==4){
            int x=read();
            ask(x-ans);
        }
        // cout<<"ans ";
        write(ans);
        puts("");
    }
	return 0;
}
/*
*/