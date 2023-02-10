/*
 * @Author: watering_penguin 
 * @Date: 2023-02-10 09:54:33 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-10 11:40:04
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
const int inf=0x3f3f3f3f;
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
int a[N],d[N];
struct node{
    int l,r,i;
}no[N];
int pos[N],L[N],R[N],kuaichang,kuaishu;
bool operator <(const node &x,const node &y){
    if(pos[x.l]==pos[y.l])return x.r<y.r;
    return x.l<y.l;
}
int st[N],ed[N],sst[N],res,ans[N];
void add(int x,int k){
    if(k){
        st[a[x]]=min(st[a[x]],x);
        ed[a[x]]=max(ed[a[x]],x);
        res=max(res,ed[a[x]]-st[a[x]]);
    }
    else{
        ed[a[x]]=max(ed[a[x]],x);
        res=max(res,ed[a[x]]-x);
    }
    return ;
}
int baoli(int l,int r){
    int res=0;
    for(int i=l;i<=r;i++){
        sst[a[i]]=inf;
    }
    for(int i=l;i<=r;i++){
        sst[a[i]]=min(sst[a[i]],i);
        res=max(res,i-sst[a[i]]);
    }
    return res;
}
signed main(){
    int n=read(),m=read();
    kuaichang=sqrt(n),kuaishu=n/kuaichang;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=0;i<=n;i++)d[i+1]=a[i];
    sort(d+1,d+n+2);
    int len=unique(d+1,d+n+2)-d-1;
    for(int i=n+1;i>=1;i--){
        a[i]=lower_bound(d+1,d+len+1,a[i-1])-d;
    }
    n++;
    for(int i=1;i<=kuaishu;i++){
        L[i]=R[i-1]+1;
        R[i]=i*kuaichang;
    }
    if(R[kuaishu]!=n){
        kuaishu++;
        L[kuaishu]=R[kuaishu-1]+1;
        R[kuaishu]=n;
    }
    for(int i=1;i<=kuaishu;i++){
        for(int j=L[i];j<=R[i];j++){
            pos[j]=i;
        }
    }
    for(int i=1;i<=m;i++){
        no[i].l=read(),no[i].r=read()+1,no[i].i=i;
    }
    sort(no+1,no+m+1);
    for(int i=1,j=1,l=0,r=0;i<=kuaishu;i++){
        r=R[i];
        res=0;
        memset(st,0x3f,sizeof(st));
        memset(ed,0,sizeof(ed));
        while(pos[no[j].l]==i){
            l=R[i]+1;
            if(no[j].r-no[j].l<=kuaichang){
                // cout<<no[j].l<<" "<<no[j].r<<endl;
                ans[no[j].i]=baoli(no[j].l,no[j].r);
                j++;
                continue;
            }
            while(r<no[j].r)add(++r,1);
            int tmp=res;
            while(l>no[j].l)add(--l,0);
            ans[no[j].i]=res;
            res=tmp;
            while(l<=R[i]){
                if(l==ed[a[l]])ed[a[l]]=0;
                l++;
            }
            j++;
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}