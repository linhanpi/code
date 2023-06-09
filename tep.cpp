//#pragma GCC optimize(3)
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define db double
#define ll long long
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define vint vector <int>
#define vpii vector <pii>
 
#define pii pair <int, int>
#define pll pair <ll, ll>
#define fi first
#define se second
#define pb emplace_back
#define all(x) begin(x), end(x)
#define rev(x) reverse(all(x))
#define sor(x) sort(all(x))
#define mem(x, v, s) memset(x, v, sizeof(x[0]) * (s))
#define cpy(x, y, s) memcpy(x, y, sizeof(x[0]) * (s))
#define FileI(x) freopen(x, "r", stdin)
#define FileO(x) freopen(x, "w", stdout)
#define y1 y_chenxiaoyan_1
 
bool Mbe;
namespace IO {
	char buf[1 << 21], *p1 = buf, *p2 = buf, Obuf[1 << 24], *O = Obuf;
	#define gc getchar()
//	#define gc (p1 == p2 && (p2 = (p1 = buf) + \
		fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
	#define pc(x) (*O++ = x)
	#define flush() fwrite(Obuf, 1, O - Obuf, stdout)
	inline ll read() {
		ll x = 0; bool sgn = 0; char s = gc;
		while(!isdigit(s)) sgn |= s == '-', s = gc;
		while(isdigit(s)) x = x * 10 + s - '0', s = gc;
		return sgn ? -x : x;
	}
	template <class T>
		inline void rprint(T x) {if(x >= 10) rprint(x / 10); pc(x % 10 + '0');}
	template <class T>
		inline void print(T x) {if(x < 0) pc('-'), x = -x; rprint(x);}
} using namespace IO;
 
template <class T1, class T2> void cmin(T1 &a, T2 b){a = a < b ? a : b;}
template <class T1, class T2> void cmax(T1 &a, T2 b){a = a > b ? a : b;}
 
const int N = 2e3 + 5;
const ld eps = 1e-10;
struct DP {ld res; int x, y;} f[N];
int n, a, b;
ld ans, la, ra = 1, p[N], u[N];
int main() {
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++) cin >> p[i];
	for(int i = 1; i <= n; i++) cin >> u[i];
	for(int _a = 1; _a <= 40; _a++) {
		ld ma = (la + ra) / 2, lb = 0, rb = 1;
		for(int _b = 1; _b <= 40; _b++) {
			ld mb = (lb + rb) / 2;
			for(int i = 1; i <= n; i++) {
				ld val; f[i] = f[i - 1];
				if((val = f[i - 1].res + p[i] - ma) > f[i].res + eps) f[i] = {val, f[i - 1].x + 1, f[i - 1].y};
				if((val = f[i - 1].res + u[i] - mb) > f[i].res + eps) f[i] = {val, f[i - 1].x, f[i - 1].y + 1};
				if((val = f[i - 1].res + p[i] + u[i] - p[i] * u[i] - ma - mb) > f[i].res + eps)
					f[i] = {val, f[i - 1].x + 1, f[i - 1].y + 1};
			} if(f[n].y == b) {lb = rb = mb; break;}
			f[n].y <= b ? rb = mb : lb = mb;
		} f[n].x <= a ? (ra = ma, ans = f[n].res + a * ma + b * lb) : la = ma;
	} printf("%.9LF\n", ans);
	return flush(), 0;
}