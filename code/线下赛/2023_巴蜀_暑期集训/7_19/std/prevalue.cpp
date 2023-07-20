#include "bits/stdc++.h"

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define all(a) (a).begin(), (a).end()

using namespace std;

using ll = long long;
using str = string;

using vi = vector<int>;
using vpi = vector<pair<int, int>>;

const int INFi = 2e9;
const ll INF = 2e18;

struct SegTree {
	struct Node {
		ll mx;
		ll upd;

		void flip() {
			if (mx < 0) mx += INFi;
			else mx -= INFi;
		}

		void apply(ll x) {
			mx += x;
			upd += x;
		}

		void combine(const Node &a, const Node &b) { mx = max(a.mx, b.mx) + upd; }

		Node() : mx(-INFi), upd(0) {}
	};

	vector<Node> t;
	int n;

	SegTree(int sz) {
		n = sz;
		t.resize(n * 4);
	}

	void push(int v) {
		if (!t[v].upd) return;
		t[v << 1].apply(t[v].upd);
		t[v << 1 | 1].apply(t[v].upd);
		t[v].upd = 0;
	}

	void upd(int v, int l, int r, int lq, int rq, ll x) {
		if (lq >= r || l >= rq) return;
		if (lq <= l && r <= rq) {
			t[v].apply(x);
			return;
		}
		push(v);
		upd(v << 1, l, (l + r) >> 1, lq, rq, x);
		upd(v << 1 | 1, (l + r) >> 1, r, lq, rq, x);
		t[v].combine(t[v << 1], t[v << 1 | 1]);
	}

	void upd(int lq, int rq, ll x) { upd(1, 0, n, lq, rq, x); }

	ll get(int v, int l, int r, int lq, int rq) {
		if (l >= rq || lq >= r) return -INF;
		if (lq <= l && r <= rq) return t[v].mx;
		push(v);
		return max(get(v << 1, l, (l + r) >> 1, lq, rq), get(v << 1 | 1, (l + r) >> 1, r, lq, rq)) +
		       t[v].upd;
	}

	ll get(int lq, int rq) { return get(1, 0, n, lq, rq); }

	void flip(int v, int l, int r, int i) {
		if (l + 1 == r) {
			t[v].flip();
			return;
		}
		int mid = (l + r) / 2;
		if (i < mid) flip(v << 1, l, mid, i);
		else flip(v << 1 | 1, mid, r, i);
		t[v].combine(t[v << 1], t[v << 1 | 1]);
	}

	void flip(int i) { flip(1, 0, n, i); }
};

void smart() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	rep(i, n) a[i]--;
	vpi upd_up(n), upd_down(n);
	vi p_up(n), p_down(n);

	{
		vi up(n, 0);
		for (int i = n - 1; i >= 0; --i) {
			int pos = lower_bound(all(up), -a[i]) - up.begin();
			upd_up[i] = {-up[pos], a[i]};
			p_up[i] = -up[pos - 1];
			up[pos] = -a[i];
		}
	}
	{
		vi down(n, n);
		for (int i = n - 1; i >= 0; --i) {
			int pos = lower_bound(all(down), a[i]) - down.begin();
			upd_down[i] = {a[i] + 1, down[pos] + 1};
			p_up[i] = down[pos - 1];
			down[pos] = a[i];
		}
	}
	SegTree seg_up(n), seg_down(n);
	for (auto &[l, r] : upd_up) seg_up.upd(l, r, 1);
	for (auto &[l, r] : upd_down) seg_down.upd(l, r, 1);

	int ans = 0;
	set<int> was = {-1, n};
	vi value_up(n), value_down(n);
	int pos = 0, type = 0, l, r;
	rep(i, n) {
		int x = a[i];
		seg_up.upd(upd_up[i].first, upd_up[i].second, -1);
		seg_down.upd(upd_down[i].first, upd_down[i].second, -1);
		int R = *was.lower_bound(x);
		int L = *prev(was.lower_bound(x));
		{
			// x - is anti-record
			int result = seg_down.get(x, x + 1) + INFi; // need + INFi because not flipped
			result += max(0ll, seg_up.get(R, n));
			result += 1;
			if (ans < result) {
				ans = result;
				pos = i;
				type = -1;
				r = R;
				l = L;
			}
		}
		{
			// x - is record
			int result = seg_up.get(x, x + 1) + INFi; // need + INFi because not flipped
			result += max(0ll, seg_down.get(0, L + 1));
			result += 1;
			if (ans < result) {
				ans = result;
				pos = i;
				type = 1;
				r = R;
				l = L;
			}
		}
		value_down[x] = (R == n ? 0 : value_down[R]) + 1;
		value_up[x] = (L == -1 ? 0 : value_up[L]) + 1;
		seg_down.flip(x);
		if (R != n) seg_down.upd(R, R + 1, 1);
		seg_down.upd(x, x + 1, value_up[x] + value_down[x] - 1);

		seg_up.flip(x);
		if (L != -1) seg_up.upd(L, L + 1, 1);
		seg_up.upd(x, x + 1, value_up[x] + value_down[x] - 1);

		if (ans < value_down[x] + value_up[x] - 1) {
			ans = value_down[x] + value_up[x] - 1;
			pos = i;
			type = 0;
			l = L;
			r = R;
		}
		was.insert(x);
	}
	cout << ans << '\n';
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

signed main() {
	freopen("prevalue.in", "r", stdin);
	freopen("prevalue.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout << setprecision(15) << fixed;
	int t;
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		smart();
	}
	// stress();
	return 0;
}
