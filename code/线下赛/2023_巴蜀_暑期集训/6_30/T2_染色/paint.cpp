#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned long long
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
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=1e6+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int basecond=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}
struct sgt{
	int mx[N<<2],add[N<<2];
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	void pu(int p){
		mx[p]=max(mx[ls(p)],mx[rs(p)]);
        return ;
	}
	void build(){
		memset(mx,0,sizeof(mx));
		memset(add,0,sizeof(add));
        return ;
	}
	void down(int x,int l,int r){
		if(add[x]){
			int d=add[x],mid=l+r>>1;
			add[ls(x)]+=d;
			add[rs(x)]+=d;
			mx[ls(x)]+=d;
			mx[rs(x)]+=d;
			add[x]=0;
		}
        return ;
	}
	void update(int p,int l,int r,int ql,int qr,int d){
		if(ql>qr) return;
		if(l>=ql && r<=qr){
			mx[p]+=d;
			add[p]+=d;
			return;
		}
		down(p,l,r);
		int mid=l+r>>1;
		if(ql<=mid) update(ls(p),l,mid,ql,qr,d);
		if(qr>mid) update(rs(p),mid+1,r,ql,qr,d);
		pu(p);
        return ;
	}
	int query(){
		return mx[1];
	}
}tr;
int W,H,n;
pii p[N];
int ans;
pii stk1[N],stk2[N];
int top1,top2;
void work(){
	tr.build();
	top1=top2=0;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		int lst=i-1;
		if(p[i].second<=H/2){
			while(top1 && p[i].second>stk1[top1].second){
				tr.update(1,1,n,stk1[top1].first,lst,stk1[top1].second-p[i].second);
				lst=stk1[top1].first-1;
				--top1;
			}
			stk1[++top1]={lst+1,p[i].second};
		}
		else{
			while(top2 && p[i].second<stk2[top2].second){
				tr.update(1,1,n,stk2[top2].first,lst,p[i].second-stk2[top2].second);
				lst=stk2[top2].first-1;
				--top2;
			}
			stk2[++top2]={lst+1,p[i].second};
		}
		stk1[++top1]={i,0};
		stk2[++top2]={i,H};
		tr.update(1,1,n,i,i,H-p[i].first);
		ans=max(ans,tr.query()+p[i+1].first);
	}
    return ;
}
signed main(){
//	freopen("paint.in","r",stdin);
//	freopen("paint.out","w",stdout);
	W=read(),H=read(),n=read();
	for(int i=1;i<=n;i++){
        p[i].first=read(),p[i].second=read();
    }
	p[++n]={0,0};
	p[++n]={W,H};
	work();
	swap(W,H);
	for(int i=1;i<=n;i++){
        swap(p[i].first,p[i].second);
    }
	work();
	cout<<ans*2<<endl;
	return 0;
}
/*
10 10 4
1 6
4 1
6 9
9 4
*/ 