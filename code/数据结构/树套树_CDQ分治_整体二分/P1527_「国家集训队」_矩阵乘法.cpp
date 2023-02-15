/*
 * @Author: watering_penguin 
 * @Date: 2023-02-11 15:12:10 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-11 16:36:27
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
const int N=5e2+5;
const int M=6e4+5;
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
int c[N][N];
int n;
void add(int x,int y,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=n;j+=lowbit(j)){
            c[i][j]+=v;
        }
    }
    return ;
}
inline int pre(int x,int y){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        for(int j=y;j;j-=lowbit(j)){
            res+=c[i][j];
        }
    }
    return res;
}
inline int cha(int l1,int r1,int l2,int r2){
    return pre(l2,r2)-pre(l1-1,r2)-pre(l2,r1-1)+pre(l1-1,r1-1);
}
struct node{
    int op,x1,y1,x2,y2,i,v;
}Q[N*N+M],tl[N*N+M],tr[N*N+M];
int ans[M];
void ztef(int st,int en,int l,int r){
    // cout<<st<<" "<<en<<" "<<l<<" "<<r<<endl;
    if(l==r){
        for(int i=st;i<=en;i++)if(Q[i].op)ans[Q[i].i]=l;
        return ;
    }
    int mid=(l+r)>>1;
    int L=0,R=0,sl=0,sr=0;
    for(int i=st;i<=en;i++){
        if(!Q[i].op){
            if(Q[i].v>mid)tr[++R]=Q[i];
            else{
                add(Q[i].x1,Q[i].y1,1);
                tl[++L]=Q[i];
            }
        }
        else{
            int res=cha(Q[i].x1,Q[i].y1,Q[i].x2,Q[i].y2);
            // cout<<"l "<<l<<" "<<r<<" "<<Q[i].op<<" "<<Q[i].x1<<" "<<Q[i].y1<<" "<<Q[i].x2<<" "<<Q[i].y2<<" "<<Q[i].v<<" "<<res<<'\n';
            if(res<Q[i].v){
                Q[i].v-=res;
                sr=1;
                tr[++R]=Q[i];
            }
            else{
                sl=1;
                tl[++L]=Q[i];
            }
        }
    }
    // cout<<st<<" "<<en<<" "<<L<<" "<<R<<endl;
    for(int i=st;i<=en;i++){
        if(!Q[i].op&&Q[i].v<=mid)add(Q[i].x1,Q[i].y1,-1);
    }
    for(int i=1;i<=L;i++)Q[st+i-1]=tl[i];
    for(int i=L+1;i<=L+R;i++)Q[st+i-1]=tr[i-L];
    if(sl)ztef(st,st+L-1,l,mid);
    if(sr)ztef(st+L,en,mid+1,r);
    return ;
}
signed main(){
    n=read();
    int q=read();
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            Q[++cnt]={0,i,j,0,0,0,read()};
        }
    }
    for(int i=1;i<=q;i++){
        int x1=read(),y1=read(),x2=read(),y2=read(),k=read();
        Q[++cnt]={1,x1,y1,x2,y2,i,k};
    }
    ztef(1,cnt,0,1e9);
    for(int i=1;i<=q;i++){
        write(ans[i]);
        puts("");
    }
    return 0;
}