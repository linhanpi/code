#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define ull unsigned int
// #define uint unsigned int
// #define rint register int
// #define ll int
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
const int base=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
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
int lastans;
struct dian{
	int x,y;
	bool operator <(const dian &a)const{return x!=a.x?x<a.x:y<a.y;}
	dian operator -(const dian &a)const{return (dian){x-a.x,y-a.y};}
	int operator *(const dian &a)const{return x*a.y-y*a.x;}
};
struct xds_data{
    vector <dian> st[2];
}a[N<<2];
int size[N],n;
char st[5];
int calc(int p,int x,int y){
	int o=0;
	if(y<0){
        x=-x,y=-y,o=1;
    }
	int l=0,r=a[p].st[o].size()-1;
	while(l<r){
		int mid=(l+r)>>1;
		if(-x*(a[p].st[o][mid+1].x-a[p].st[o][mid].x)>=y*(a[p].st[o][mid+1].y-a[p].st[o][mid].y))r=mid;
		else l=mid+1;
	}
	return x*a[p].st[o][l].x+y*a[p].st[o][l].y;
}
int query(int p,int l,int r,int ql,int qr,int x,int y){
	if(l>=ql&&r<=qr){
        return calc(p,x,y);
    }
	int mid=(l+r)>>1;
	if(qr<=mid){
        return query(p<<1,l,mid,ql,qr,x,y);
    }
	else if(ql>mid){
        return query(p<<1|1,mid+1,r,ql,qr,x,y);
    }
	else{
        return max(query(p<<1,l,mid,ql,mid,x,y),query(p<<1|1,mid+1,r,mid+1,qr,x,y));
    }
}
vector <dian> tmp;
void build(int p,int len){
	for(int o=0;o<=1;o++){
        tmp.clear();
		auto i=a[p<<1].st[o].begin(),j=a[p<<1|1].st[o].begin();
		for(;i!=a[p<<1].st[o].end()||j!=a[p<<1|1].st[o].end();){
            if(i==a[p<<1].st[o].end()||(j!=a[p<<1|1].st[o].end()&&*j<*i)){
                tmp.push_back(*j++);
            }
			else{
                tmp.push_back(*i++);
            }
        }
		int top=0;
		for(auto i=tmp.begin();i!=tmp.end();++i){
			while(top>1&&((a[p].st[o][top-1]-a[p].st[o][top-2])*(*i-a[p].st[o][top-1]))>=0){
                --top,a[p].st[o].pop_back();
            }
			a[p].st[o].push_back(*i);
            ++top;
		}
	}
    return ;
}
void update(int p,int l,int r,int q,int x,int y){
	if(l==r){
        a[p].st[0].push_back({x,y});
        a[p].st[1].push_back({-x,-y});
        ++size[p];
        return;
    }
	int mid=(l+r)>>1;
	if(q<=mid){
        update(p<<1,l,mid,q,x,y);
    }
	else{
        update(p<<1|1,mid+1,r,q,x,y);
    }
	++size[p];
    if(size[p]==r-l+1){
        build(p,r-l+1);
    }
}
void jm(int &x){
	x^=(lastans&0x7fffffff);
}
signed main(){
	int enc=0;
    n=read();
    scanf("%s",st+1);
    if(st[1]!='E'){
        enc=1;
    }
	int nn=0;
	for(int i=1;i<=n;i++){
		scanf("%s",st+1);
		if(st[1]=='Q'){
			int x=read(),y=read(),l=read(),r=read();
			if(enc){
                jm(x);
                jm(y);
                jm(l);
                jm(r);
            }
            cout<<(lastans=query(1,1,n,l,r,x,y))<<endl;
		}
		else{
			int x=read(),y=read();
			if(enc){
                jm(x);
                jm(y);
            }
			update(1,1,n,++nn,x,y);
		}
	}
    return 0;
}