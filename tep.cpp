#include <bits/stdc++.h>
using namespace std;

//#pragma GCC optimize(2)

#define ll long long
#define int long long
#define LD long double

#define PII pair <int, int>
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define rep(i, x, y) for (register int i = x; i <= y; ++ i )
#define per(i, x, y) for (register int i = x; i >= y; -- i )

inline int read() {
    int s = 0, w = 1; char c = getchar();
    while (! isdigit(c)){ if (c == '-') w = -1; c = getchar();}
    while (isdigit(c)){ s = (s << 3) + (s << 1) + (c ^ 48); c = getchar();}
    return s * w;
}
inline void write(register int x) {
    if (x < 0){
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar((char)(x % 10 + '0'));
}
inline void write_(register int x) {
    write(x);
    putchar(' ');
}
inline void writeline(register int x) {
    write(x);
    putchar('\n');
}

inline void chkmax(int &x, register int y) { if (y > x) x = y;}
inline void chkmin(int &x, register int y) { if (y < x) x = y;}

inline int ksm(register int a, register int b, register int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

inline int gcd(register int a, register int b) {
	if (a < b) swap(a, b);
	if (! b) return a;
	return gcd(b, a % b);
}

inline int exgcd(register int a, register int b, int &x, int &y) {
	if (! b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

#define inv1 invByKsm
#define inv2 invByExgcd

inline int invByKsm(register int x, register int p) {
	return ksm(x, p - 2, p);
}
inline int invByExgcd(register int x, register int p) {
	exgcd(x, p, x, *new int);
	return (x%p+p)%p;
}

const int N=1e5+5;
const int INF=1e16;

int n,q,L;
vector<int> g[N];
int fa[N],w[N][5];

int f[N][5];
int TMP[N];
void dfs(int x){
	if(f[x][1]>-1e12) return;
	int sum=0;
	for(auto y:g[x]){
		dfs(y);
		int tmp=-INF;
		rep(k,1,L){
			chkmax(tmp,f[y][k]);
		}
		TMP[y]=tmp;
		sum+=tmp;
	}
	f[x][1]=sum+w[x][1];
	rep(k,2,L){
		for(auto y:g[x]){
			chkmax(f[x][k],f[y][k-1]+sum-TMP[y]+w[x][k]);
		} 
	}
}

signed main() {
//	freopen("decompose.in","r",stdin);
//	freopen("decompose.out","w",stdout);
	
	n=read(),q=read(),L=read();
	rep(i,2,n){
		int x=read();
		g[x].pb(i);
		fa[i]=x;
	}
	rep(i,1,n) rep(j,1,L) w[i][j]=read();
	
	memset(f,-0x3f,sizeof f);
	
	while(q--){
		int x=read();
		rep(i,1,L) w[x][i]=read();
		for(int now=x;now;now=fa[now]) memset(f[now],-0x3f,sizeof f[now]);
		dfs(1);
		int ans=-INF;
		rep(i,1,L) chkmax(ans,f[1][i]);
		writeline(ans);
	}
	
	return 0;
}