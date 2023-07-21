#include <bits/stdc++.h>
using namespace std;

//#pragma GCC optimize(3)

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
	return (x % p + p) % p;
}
const int mod=10000000007;
int n,m,k;
int f[2][305][305];
void solve(){
	n=read(),m=read(),k=read();
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	rep(now,1,k){
		int t=now&1;
		memset(f[t],0,sizeof(f[t]));
		rep(i,1,n){
			rep(j,1,m){
				rep(iPre,0,i-1){
					rep(jPre,0,j-1){
						(f[t][i][j]+=f[t^1][iPre][jPre]*min(i-iPre,j-jPre)%mod)%=mod;
					}
				}
			}
		}
	}
	writeline(f[k&1][n][m]);
}
signed main(){
	// freopen("question.in","r",stdin);
	// freopen("question.out","w",stdout); 
	int T=read();
	while(T--) solve();
    return 0;
}
/*
5
2 2 2
3 3 2
4 4 2
5 3 3
5 5 3
*/