#include<bits/stdc++.h>
// #define int long long//信仰
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
const int N=5e6+5;
const int M=1e2+5;
const int inf=INT_MAX;
const int base=131;
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
int maxn[N];
char s[N],t[N];
int len,zf;
int sa[N],tong[N],rk[N],h[N],tp[N];
void pu(int p){
    maxn[p]=min(maxn[lson],maxn[rson]);
    return ;
}
void bd(int p,int l,int r){
    if(l==r){
        maxn[p]=h[l];
        return ;
    }
    int mid=(l+r)>>1;
    bd(lson,l,mid);
    bd(rson,mid+1,r);
    pu(p);
    return ;
}
void add(int p,int l,int r,int pos,int x){
    if(l==r){
        maxn[p]=min(maxn[p],x);
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)add(lson,l,mid,pos,x);
    else add(rson,mid+1,r,pos,x);
    pu(p);
    return ;
}
int cha(int p,int l,int r,int ql,int qr){
    if(ql>qr)return 0;
    if(ql<=l&&r<=qr){
        return maxn[p];
    }
    int mid=(l+r)>>1;
    int ans=inf;
    if(ql<=mid)ans=min(ans,cha(lson,l,mid,ql,qr));
    if(qr>mid)ans=min(ans,cha(rson,mid+1,r,ql,qr));
    return ans;
}
void jspai(){
    for(int i=0;i<=zf;i++)tong[i]=0;
    for(int i=1;i<=len;i++)tong[rk[i]]++;
    for(int i=1;i<=zf;i++)tong[i]+=tong[i-1];
    for(int i=len;i>=1;i--)sa[tong[rk[tp[i]]]--]=tp[i];
    return ;
}
signed main(){
	int T=read();
    while(T--){
        scanf("%s",s+1);
        int n=strlen(s+1);
        len=n;
        s[++len]='Z';
        scanf("%s",s+len+1);
        int m=strlen(s+len+1);
        len+=m;
        for(int i=1;i<=len;i++){
            tp[i]=i;
            rk[i]=s[i]-'A'+1;
        }
        zf=26;
        jspai();
        for(int w=1,p=0;p<len;zf=p,w<<=1){
            p=0;
            for(int i=1;i<=w;i++)tp[++p]=len-w+i;
            for(int i=1;i<=len;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
            jspai();
            swap(tp,rk);
            rk[sa[1]]=p=1;
            for(int i=2;i<=len;i++){
                rk[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
            }
        }
        for(int i=1,k=0;i<=len;i++){
            if(rk[i]==1)continue;
            if(k)k--;
            while(s[i+k]==s[sa[rk[i]-1]+k])++k;
            h[rk[i]]=k;
        }
        bd(1,1,len);
        int ans=0;
        for(int i=1;i+m-1<=n;i++){
            int tot=0;
            for(int j=1;j<=m&&tot<=3;){
                if(s[i+j-1]!=s[n+j+1]){
                    ++tot,j++;
                    if(tot>3)break;
                }
                else{
                    j+=cha(1,1,len,min(rk[i+j-1],rk[n+j+1])+1,max(rk[i+j-1],rk[n+j+1]));
                }
            }
            if(tot<=3)ans++;
        }
        cout<<ans<<endl;
    }
	return 0;
}
