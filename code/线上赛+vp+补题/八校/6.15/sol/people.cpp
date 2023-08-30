#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vint;
typedef vector<vint> vvint;


int read() {
	int a = 0, b = 0; char c = getchar();
	while (c < '0' || c > '9') b ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') a = a * 10 - 48 + c, c = getchar();
	return b ? -a : a;
}

const int N = 100005;


int main() {
	freopen("people.in", "r", stdin);
	freopen("people.out", "w", stdout);
	int n = read(), k = read();
	struct seq { int c, l; }; vector<seq> a(n);
	for (int i = 0; i < n; ++i) a[i].c = read(), a[i].l = read();
	vll s(k);
	for (auto [c, l] : a) {
		if (c + l >= k) {
			s[c]++; l -= (k - c);
			s[0] += l / k, l %= k;
			s[0]++, s[l]--;
		} else s[c]++, s[c + l]--;
	}
	for (int i = 1; i < k; ++i) s[i] += s[i - 1];
	ll mn = *min_element(s.begin(), s.end()), np = 0, ex = -1;
	//cerr << ex << ' ' << np << ' ' << mn << " !!" << endl;
	for (ll &a : s) a -= mn;
	for (int i = 0; i < k; ++i) if (!s[i]) {
		int ke = 0;
		while (s[(i + ke + 1) % k]) ++ke;
		if (ex < ke) ex = ke, np = i;
	}
	for (int i = 0; i < ex; ++i) s[(np + i + 1) % k]--;
	
	
	struct segt {
		int ns, n;
		vll mn, tg;
		segt() {}
		#define ls (p << 1)
		#define rs (ls | 1)
		#define mi ((l + r) >> 1)
		void build(int p, int l, int r, const vll &a) {
			tg[p] = 0;
			if (l == r) { mn[p] = a[l - 1]; return; }
			build(ls, l, mi, a), build(rs, mi + 1, r, a);
			mn[p] = min(mn[ls], mn[rs]);
		}
		segt(const vll &a) {
			ns = 1, n = a.size(); while (ns < 2 * n) ns <<= 1;
			mn.resize(ns), tg.resize(ns);
			build(1, 1, n, a);
		}
		void pd(int p) {
			if (tg[p]) {
				tg[ls] += tg[p], tg[rs] += tg[p];
				mn[ls] += tg[p], mn[rs] += tg[p];
				tg[p] = 0;
			}
		}
		void del(int x, int y, int l, int r, int p = 1) {
			if (x <= l && r <= y) { mn[p] --, tg[p] --; return; }
			pd(p); 
			if (x <= mi) del(x, y, l, mi, ls);
			if (mi < y) del(x, y, mi + 1, r, rs);
			mn[p] = min(mn[ls], mn[rs]);
		}
		void sub(int x, int y) { del(x + 1, y + 1, 1, n); }
		int findf(int x, int l, int r, int p = 1) {
			if (x >= r || mn[p]) return -1; 
			if (l == r) return mn[p] ? -1 : l;
			pd(p);
			if (mn[ls] == 0) {
				int y = findf(x, l, mi, ls);
				if (y != -1) return y;
			}
			if (mn[rs] == 0) return findf(x, mi + 1, r, rs);
			return -1;
		}
		int qry(int x) { return findf(x + 1, 1, n) - 1; }
		int qnow(int x) {
			int l = 1, r = n, p = 1; ++x;
			while (l != r) {
				pd(p);
				if (x <= mi) p = ls, r = mi;
				else l = mi + 1, p = rs;
			}
			return mn[p];
		}
	};
	assert(s[np] == 0);
	{ vll t(k); int r = (np + 1) % k; copy(s.begin(), s.begin() + r, t.end() - r); copy(s.begin() + r, s.end(), t.begin()); t.swap(s); }
	// np + 1, np + 2, .... , 0, ..., np
	segt T(s);
	vvint cut(n, vint(3)), cs(k);
	for (int i = 0; i < n; ++i) cs[a[i].c].push_back(i);
	
	
	for (int V = 0; V < k; ++V) {
		int p = (np + 1 + V) % k;
		assert(T.qnow(k - 1) == 0);
		while (T.qnow(V)) {
			assert(cs[p].size());
			int i = cs[p].back(), nx = T.qry(V); cs[p].pop_back();
			assert(nx > 0);
			int len = min(a[i].l, nx - V);
			assert(cut[i][0] == 0);
			cut[i][0] = len, a[i].l -= len, T.sub(V, V + len - 1);
			if (a[i].l) a[i].c = (a[i].c + len) % k, cs[a[i].c].push_back(i);
		}
	}
	vint res;
	
	int spos = (np + 1) % k, epos = (np + ex + 1) % k, kpos = 0;
	ll tlen = mn * (ll)k + ex;
	ll sumlen = 0;
	for (int i = 0; i < n; ++i) sumlen += a[i].l;
	assert(sumlen == tlen);
	
	while (tlen) {
		if (!cs[spos].size()) {
			assert(spos == epos); // only if all are same
			while (1) {
				assert(kpos < n);
				int L = (spos - a[kpos].c + k) % k;
				if (a[kpos].l > L) {
					int len = a[kpos].l - L;
					tlen -= len, spos = (spos + len) % k;
					assert(cut[kpos][2] == 0);
					res.push_back(len), cut[kpos][2] = len, a[kpos].l -= len;
					break;
				}
				++kpos;
			}
		} else {
			int i = cs[spos].back(); cs[spos].pop_back();
			if (!a[i].l) continue;
			tlen -= a[i].l, spos = (spos + a[i].l) % k;
			assert(cut[i][1] == 0);
			res.push_back(a[i].l), cut[i][1] = a[i].l, a[i].l = 0;
		}
	}
	
	cout << (np + 1) % k << ' ' << mn * (ll)k + ex << '\n';
	for (int i = 0; i < n; ++i) {
		vint r;
		for (int k = 0; k < 3; ++k) if (cut[i][k]) r.push_back(cut[i][k]);
		cout << r.size() << ' '; for (int k : r) cout << k << ' '; cout << '\n';
	}
	cout << res.size() << ' '; for (int k : res) cout << k << ' '; cout << '\n';
	
	return 0;
}

