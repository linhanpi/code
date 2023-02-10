/*
 * @Author: watering_penguin 
 * @Date: 2023-02-09 15:31:51 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-10 11:31:47
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
int a[N],b[N];
struct node{
    int l,r,i;
}no[N];
int bl[N],L[N],R[N],kuaichang,kuaishu;
bool operator <(const node &x,const node &y){
    if(bl[x.l]==bl[y.l]){
        return x.r<y.r;
    }
    return x.l<y.l;
}
int cnt[N],res,ans[N];
inline void add(int x){
    cnt[a[x]]++;
    res=max(res,cnt[a[x]]*b[a[x]]);
    return ;
}
int tong[N];
inline int baoli(int l,int r){
    int ans=0;
    for(int i=l;i<=r;i++)++tong[a[i]];
    for(int i=l;i<=r;i++)ans=max(ans,tong[a[i]]*b[a[i]]);
    for(int i=l;i<=r;i++)--tong[a[i]];
    return ans;
}
signed main(){
    int n=read(),q=read();
    kuaichang=sqrt(n),kuaishu=n/kuaichang;
    for(int i=1;i<=n;i++)a[i]=b[i]=read();
    sort(b+1,b+n+1);
    int len=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+len+1,a[i])-b;
    }
    for(int i=1;i<=q;i++){
        no[i].l=read(),no[i].r=read(),no[i].i=i;
    }
    for(int i=1;i<=kuaishu;i++){
        L[i]=R[i-1]+1;
        R[i]=i*kuaichang;
    }
    if(R[kuaishu]<n){
        kuaishu++;
        L[kuaishu]=R[kuaishu-1]+1;
        R[kuaishu]=n;
    }
    for(int i=1;i<=kuaishu;i++){
        for(int j=L[i];j<=R[i];j++){
            bl[j]=i;
        }
    }
    sort(no+1,no+q+1);
    int l=0,r=0;
    for(int i=1,j=1;i<=kuaishu;i++){
        memset(cnt,0,sizeof(cnt));
        r=R[i];
        res=0;
        while(bl[no[j].l]==i){
            l=R[i]+1;
            if(no[j].r-no[j].l<=kuaichang){
                ans[no[j].i]=baoli(no[j].l,no[j].r);
                ++j;
                continue;
            }
            while(r<no[j].r)add(++r);
            int tmp=res;
            while(l>no[j].l)add(--l);
            ans[no[j].i]=res;
            res=tmp;
            while(l<=R[i])--cnt[a[l++]];
            ++j;
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
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