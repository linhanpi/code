/*
 * @Author: watering_penguin 
 * @Date: 2023-02-18 14:55:00 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-02-18 16:59:32
 */
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
const int mod=1e9+7;
const double eps=1e-6;
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
struct node{
    int l,r;
    mutable int v;
    node(int _l=0,int _r=0,int _v=0){
        l=_l,r=_r,v=_v;
    }
};
bool operator < (const node &x,const node &y){
    return x.l<y.l;
}
set <node> s;
auto split(int pos){
    auto it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos){
        return it;
    }
    it--;
    if(it->r<pos)return s.end();
    int l=it->l;
    int r=it->r;
    int v=it->v;
    s.erase(it);
    s.insert(node(l,pos-1,v));
    return s.insert(node(pos,r,v)).first;
}
void add(int l,int r,int k){
    auto itr=split(r+1),itl=split(l);
    for(auto it=itl;it!=itr;it++){
        it->v+=k;
    }
    return ;
}
void ass(int l,int r,int x){
    auto itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,x));
    return ;
}
struct rk{
    int num,cnt;
    rk(int _num=0,int _cnt=0){
        num=_num,cnt=_cnt;
    }
};
bool operator <(const rk &x,const rk &y){
    return x.num<y.num;
}
int kth(int l,int r,int k){
    auto itr=split(r+1),itl=split(l);
    vector <rk> v;
    for(auto it=itl;it!=itr;++it){
        v.push_back(rk(it->v,it->r-it->l+1));
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        if(v[i].cnt<k)k-=v[i].cnt;
        else return v[i].num;
    }
    return v.end()->num;
}
int cha(int l,int r,int x,int mod){
    auto itr=split(r+1),itl=split(l);
    int ans=0;
    for(auto it=itl;it!=itr;++it){
        ans=(ans+qmi(it->v,x,mod)*(it->r-it->l+1)%mod)%mod;
    }
    return ans;
}
int seed;
int rnd() {
    int ret=seed;
    seed=(seed*7+13)%mod;
    return ret;
}
int a[N];
signed main(){
    int n=read(),m=read();
    seed=read();
    int vmax=read();
    for(int i=1;i<=n;i++){
        a[i]=(rnd()%vmax)+1;
        s.insert(node(i,i,a[i]));
    }
    for(int i=1;i<=m;i++){
        int op,l,r,x,y;
        op=(rnd()%4)+1;
        l=(rnd()%n)+1;
        r=(rnd()%n)+1;
        if(l>r)swap(l,r);
        if(op==3){
            x=(rnd()%(r-l+1))+1;
        }
        else{
            x=(rnd()%vmax)+1;
        }
        if(op==4){
            y=(rnd()%vmax)+1;
        }
        if(op==1){
            add(l,r,x);
        }
        else if(op==2){
            ass(l,r,x);
        }
        else if(op==3){
            write(kth(l,r,x));
            puts("");
        }
        else{
            write(cha(l,r,x,y));
            puts("");
        }
    }
    return 0;
}
