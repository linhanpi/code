#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, X = 39989, Y = 1e9;
int n, cnt, mx[X << 2];
double k[N], b[N];
double get(int x, int id) {return k[id] * x + b[id];}
int get(int a, int c, int x) {
	double b = get(x, a), d = get(x, c);
	return b == d ? min(a, c) : b > d ? a : c;
}
void modify(int l, int r, int x, int v) {
	int m = l + r >> 1;
	if(get(m, v) > get(m, mx[x])) swap(mx[x], v);
	if(get(l, v) > get(l, mx[x])) modify(l, m, x << 1, v);
	else if(get(r, v) > get(r, mx[x])) modify(m + 1, r, x << 1 | 1, v);
}
void modify(int l, int r, int ql, int qr, int x, int v) {
	if(ql <= l && r <= qr) return modify(l, r, x, v);
	int m = l + r >> 1;
	if(ql <= m) modify(l, m, ql, qr, x << 1, v);
	if(m < qr) modify(m + 1, r, ql, qr, x << 1 | 1, v);
}
int query(int l, int r, int x, int p) {
	if(l == r) return mx[x];
	int m = l + r >> 1;
	if(p <= m) return get(query(l, m, x << 1, p), mx[x], p);
	return get(query(m + 1, r, x << 1 | 1, p), mx[x], p);
}
int main() {
	cin >> n;
	for(int i = 1, las = 0; i <= n; i++) {
		int op, c, d, e, f;
		scanf("%d %d", &op, &c), c = (c + las - 1) % X + 1;
		if(op == 0) printf("%d\n", las = query(1, X, 1, c));
		else {
			scanf("%d %d %d", &d, &e, &f), e = (e + las - 1) % X + 1;
			d = (d + las - 1) % Y + 1, f = (f + las - 1) % Y + 1;
			if(c > e) swap(c, e), swap(d, f);
			if(c == e) b[++cnt] = max(d, f);
			else k[++cnt] = (double)(f - d) / (e - c), b[cnt] = d - c * k[cnt];
			modify(1, X, c, e, 1, cnt);
		}
	}
	return 0;
}