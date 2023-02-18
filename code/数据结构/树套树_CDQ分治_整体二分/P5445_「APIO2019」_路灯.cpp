#include<bits/stdc++.h>
#define int long long
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
const int N=12e5+5;
const int M=6e4+5;
const int mo=7000007;
const int inf=1e16+9;
const int base=131;
const int mod=998244353;
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
int n,q;
int c1[N],c2[N];
void add(int *c,int x,int y){
    for(int i=x+1;i<=n+1;i+=lowbit(i)){
        c[i]+=y;
    }
    return ;
}
int cha(int *c,int x){
    int res=0;
    for(int i=x+1;i;i-=lowbit(i)){
        res+=c[i];
    }
    return res;
}
struct node{
    int op,a,b,t,i;
}Q[N];
int ans[N];
bool operator <(const node &x,const node &y){
    if(x.b!=y.b)return x.b>y.b;
    return x.a<y.a;
}
void cdq(int l,int r){
    if(l==r)return ;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    sort(Q+l,Q+mid+1);
    sort(Q+mid+1,Q+r+1);
    int i=l,j=mid+1;
    for(;j<=r;j++){
        while(i<=mid&&Q[i].b>=Q[j].b){
            if(!Q[i].op){++i;continue;}
            add(c1,Q[i].a,Q[i].i);
            add(c2,Q[i].a,Q[i].i*Q[i].t);
            ++i;
        }
        if(!Q[j].op){
            ans[Q[j].i]+=Q[j].t*cha(c1,Q[j].a-1)-cha(c2,Q[j].a-1);
        }
    }
    for(int k=l;k<i;k++){
        if(Q[k].op){
            add(c1,Q[k].a,-Q[k].i);
            add(c2,Q[k].a,-Q[k].i*Q[k].t);
        }
    }
    return ;
}
int cnt;
set <int> st;
char ch[N];
int a[N];
signed main(){
    n=read()+1,q=read();
    scanf("%s",ch+1);
    for(int i=1;i<n;i++)a[i]=ch[i]-'0';
    for(int i=0;i<=n;i++){
        if(!a[i]){
            if(st.size())Q[++cnt]={1,*st.rbegin(),i,0,1};
            st.insert(i);
        }
    }
    int tot=0;
    for(int i=1;i<=q;i++){
        scanf("%s",ch+1);
        int p=read();
        if(ch[1]=='t'){
            if(!(a[p]^=1)){
                auto it=st.insert(p).first;
                if(it!=st.begin()){
                    Q[++cnt]={1,*prev(it),p,i,1};
                    if(it!=--st.end())Q[++cnt]={1,*prev(it),*next(it),i,-1};
                }
                if(it!=--st.end())Q[++cnt]={1,p,*next(it),i,1};
            }
            else{
                auto it=st.lower_bound(p);
                if(it!=st.begin()){
                    Q[++cnt]={1,*prev(it),p,i,-1};
                    if(it!=--st.end())Q[++cnt]={1,*prev(it),*next(it),i,1};
                }
                if(it!=--st.end())Q[++cnt]={1,p,*next(it),i,-1};
                st.erase(it);
            }
        }
        else{
            int k=read();
            Q[++cnt]={0,p,k,i,++tot};
        }
    }
    // for(int i=1;i<=cnt;i++){
    //     cout<<Q[i].op<<" "<<Q[i].a<<" "<<Q[i].b<<" "<<Q[i].t<<" "<<Q[i].i<<endl;
    // }
    // cout<<1<<endl;
    cdq(1,cnt);
    for(int i=1;i<=tot;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}