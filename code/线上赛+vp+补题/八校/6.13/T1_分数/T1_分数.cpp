#include<bits/stdc++.h>
// #define int long long//信仰
#define ld long double
// #define uint unsigned int
// #define rint register int
#define ll unsigned long long
// #define double long double
#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define rd() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=8e6+5;
const int M=3200+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=20071027;
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
inline ll qmi(ll x,ll y,ll mod){
    ll ans=1;x%=mod;y%=mod-1;
    while(y){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}
typedef unsigned long long ull;
int n,q,ci;
int ni[20071028];
inline void niycl(){
    ni[0]=ni[1]=1;
    for(int i=2;i<mod;i++){
        ni[i]=1ull*ni[mod%i]*(mod-mod/i)%mod;
    }
    return ;
}
namespace GenHelper{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_(){
        b=((z1<<6)^z1)>>13;
        z1=((z1&4294967294U)<<18)^b;
        b=((z2<<2)^z2)>>27;
        z2=((z2&4294967288U)<<2)^b;
        b=((z3<<13)^z3)>>21;
        z3=((z3&4294967280U)<<7)^b;
        b=((z4<<3)^z4)>>12;
        z4=((z4&4294967168U)<<13)^b;
        return (z1^z2^z3^z4);
    }
}
void srand(unsigned x){
    using namespace GenHelper;
    z1=x;
    z2=(~x)^0x233333333U;
    z3=x^0x1234598766U;
    z4=(~x)+51;
    return ;
}
int read(){
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b+1;
}
int p[N];
inline void red(){
    using namespace GenHelper;
    for(int i=1;i<n;i++){
        p[i]=i;
    }
    for(int i=1;i<ci;i++){
        int a=read()%(n-1)+1,b=read()%(n-1)+1;
        swap(p[a],p[b]);
    }
    return ;
}
vector <int> fk1[M],fk2[M],fk3[M],pos;
int L[M],R[M];
int kuaichang,kuaishu;
struct fkbiao{
    inline int maxd(const int &x,const int &y){
        return p[x]>p[y]?x:y;
    }
    inline void fkycl(){
        pos.resize(n+5);
        kuaichang=sqrt(n);
	    kuaishu=n/kuaichang;
	    for(register int i=1;i<=kuaishu;++i){
            fk1[i].resize(kuaichang+5);
            fk2[i].resize(kuaichang+5);
            fk3[i].resize(kuaichang+5);
	    	L[i]=R[i-1]+1;
	    	R[i]=i*kuaichang;
	    }
	    if(R[kuaishu]!=n){
            kuaishu++;
            fk1[kuaishu].resize(kuaichang+5);
            fk2[kuaishu].resize(kuaichang+5);
            fk3[kuaishu].resize(kuaichang+5);
	    	L[kuaishu]=R[kuaishu-1]+1;
	    	R[kuaishu]=n;
	    }
	    for(register int i=1;i<=kuaishu;++i){
	    	for(int j=L[i];j<=R[i];j++){
	    		pos[j]=i;
	    		fk2[i][j-L[i]+1]=maxd(fk2[i][j-L[i]],j);
	    	}
	    	for(int j=R[i];j>=L[i];j--){
	    		fk3[i][j-L[i]+1]=maxd(fk3[i][j-L[i]+2],j);
	    	}
	    	fk1[i][i]=fk2[i][R[i]-L[i]+1];
	    	for(int j=1;j<i;j++){
	    		fk1[j][i]=maxd(fk1[j][i-1],fk1[i][i]);
	    	}
	    }
        return ;
    }
    inline int cha(int l,int r){
        if(pos[l]==pos[r]){
			int resd=0;
			for(int j=l;j<=r;j++){
				resd=maxd(resd,j);
			}
			return resd;
		}
        return maxd(fk1[pos[l]+1][pos[r]-1],maxd(fk3[pos[l]][l-L[pos[l]]+1],fk2[pos[r]][r-L[pos[r]]+1]));
    }
}fk;
#define ha(x) (x+n-1)
int rt;
int st[N],top;
vector <int> si;
vector <int> ls,rs;
struct dashu{
    inline void ycl(){
        ls.resize(n+5);
        rs.resize(n+5);
        vector <int> fa;
        fa.resize(2*n+5);
        vector <int> in;
        in.resize(n+5);
        int top=0,cur=0;
        for(int i=1;i<n;i++){
            cur=top;
            while(cur&&p[st[cur]]<p[i])cur--;
            if(cur)rs[st[cur]]=i,fa[i]=st[cur];
            if(cur<top)ls[i]=st[cur+1],fa[st[cur+1]]=i;
            st[++cur]=i;
            top=cur;
        }
        int tot=n-1;
        for(int i=1;i<n;i++){
            in[i]=2;
            if(!ls[i])ls[i]=++tot,fa[tot]=i;
            if(!rs[i])rs[i]=++tot,fa[tot]=i;
        }
        queue <int> q;
        for(int i=n;i<=2*n-1;i++){
            q.push(i);
        }
        while(!q.empty()){
            int now=q.front();
            q.pop();
            if(now<=n-1)si[now]=1ull*si[ls[now]]*ni[si[rs[now]]]%mod;
            in[fa[now]]--;
            if(!in[fa[now]])q.push(fa[now]);
        }
        return ;
    }
}datree;
vector <bool> dep;
struct youshu{
    vector <int> deep;
    inline void ycl(){
        top=0;
        deep.resize(2*n+5);
        dep.resize(n+5);
        for(register int i=1;i<n;++i){
            while(top&&p[st[top]]<p[i])--top;
            if(top){
                dep[i]=dep[st[top]]^1;
                deep[i]=1ull*deep[st[top]]*((dep[i]&1)?ni[si[ls[i]]]:max(1,si[ls[i]]))%mod;
            }
            else{
                deep[i]=si[ls[i]];
            }
            st[++top]=i;
        }
        for(register int i=2;i<=n;++i){
            deep[ha(i)]=1ull*deep[i-1]*(((dep[i-1]&1)^1)?ni[si[ha(i)]]:si[ha(i)])%mod;
        }
        return ;
    }
}ytree;
struct zuoshu{
    vector <int> deep;
    inline void ycl(){
        top=0;
        deep.resize(2*n+5);
        for(register int i=n-1;i;--i){
            while(top&&p[st[top]]<p[i])--top;
            if(top){
                deep[i]=1ull*deep[st[top]]*ni[si[rs[i]]]%mod;
            }
            else{
                deep[i]=ni[si[rs[i]]];
            }
            st[++top]=i;
        }
        for(register int i=1;i<n;++i){
            deep[ha(i)]=1ull*deep[i]*si[ha(i)]%mod;
        }
        return ;
    }
}ztree;
int main(){
    niycl();
    n=rd(),q=rd(),ci=rd();int seed=rd(),type=rd();
    srand(seed);
    red();
    si.resize(2*n+5);
	for(register int i=1;i<=n;++i) si[ha(i)]=read()%mod;
    datree.ycl();
    ytree.ycl();
    if(1){vector <int> vv;swap(vv,ls);}
    ztree.ycl();
    if(1){vector <int> vv;swap(vv,rs);}
    if(1){vector <int> vv;swap(vv,si);}
    fk.fkycl();
	int l,r,lastans=0;
	ull final_ans=0;
	for(register int t=1;t<=q;++t){
		l=read()%(n-1)+1,r=read()%(n-1)+1;
        if(l>r)swap(l,r);
        r++;
		ll ansnow=0;
		int root=fk.cha(l,r-1);
        ll ansz=1ull*ztree.deep[ha(l)]*ni[ztree.deep[root]]%mod;
        ll ansy=1ull*ytree.deep[ha(r)]*ni[ytree.deep[root]]%mod;
        if(dep[root])ansy=ni[ansy];
		ansnow=ansz*ansy%mod;
        if(type==0)printf("%llu\n",ansnow);
		lastans=ansnow;
		final_ans^=1ull*t*ansnow;
	}
	if(type==1)printf("%llu\n",final_ans);
	return 0;
}
