#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vint;
typedef vector<vint> vvint;


int read() {
	int a = 0, b = 0; char c = getchar();
	while (c < '0' || c > '9') b ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') a = a * 10 - 48 + c, c = getchar();
	return b ? -a : a;
}

const int N = 203;

int nx, ny, px[N], py[N];
struct pir {
	int x, y;
	pir(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	pir operator + (const pir &b) const { return pir(x + b.x, y + b.y); }
	pir operator - (const pir &b) const { return pir(x - b.x, y - b.y); }
	bool operator == (const pir &b) const { return x == b.x && y == b.y; }
	bool operator != (const pir &b) const { return x != b.x || y != b.y; }
};
typedef vector<pir> vpir;
const pir D[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
int b[N][N][4];

void pre() {
	int n = read();
	struct seg { int xa, ya, xb, yb; } a[N];
	for (int i = 1; i <= n; ++i) {
		int xa = read(), ya = read(), xb = read(), yb = read();
		a[i] = {xa, ya, xb, yb};
		px[++nx] = xa, px[++nx] = xb, py[++ny] = ya, py[++ny] = yb;
	}
	sort(px + 1, px + nx + 1), sort(py + 1, py + ny + 1);
	nx = unique(px + 1, px + nx + 1) - px - 1, ny = unique(py + 1, py + ny + 1) - py - 1;
	auto Q = [&](int x[], int nx, int v) { return lower_bound(x + 1, x + 1 + nx, v) - x; };
	for (int i = 1; i <= n; ++i) {
		auto [xa, ya, xb, yb] = a[i];
		xa = Q(px, nx, xa), xb = Q(px, nx, xb), ya = Q(py, ny, ya), yb = Q(py, ny, yb);
		if (xa > xb) swap(xa, xb); if (ya > yb) swap(ya, yb);
		if (xa == xb) {
			for (int i = ya; i < yb; ++i) {
				b[xa][i][0] = b[xa][i + 1][2] = 1;
			}
		} else {
			for (int i = xa; i < xb; ++i) {
				b[i][ya][1] = b[i + 1][ya][3] = 1;
			}
		}
	}
}

int id[N][N][4], cnt;
void solve() {
	vpir o;
	for (int i = 1; i <= nx; ++i) for (int j = 1; j <= ny; ++j) {
		int s = 0; for (int k = 0; k < 4; ++k) if (b[i][j][k]) s ^= 1;
		if (s) o.push_back({i, j});
	}
	if (o.size() > 2) { cout << 0 << '\n'; return; }
	auto exi = [&](pir a, int i) { return !id[a.x][a.y][i] && b[a.x][a.y][i]; };
	auto nxd = [&](pir a) {
		int d = -1; for (int i = 0; i < 4; ++i) if (exi(a, i) && !exi(a, i ^ 2)) d = i;
		return d;
	};
	pir S;
	vector<vpir> c(1);
	auto findp = [&](pir a) {
		if (!S.x) S = a; vpir cx;
		int d = nxd(a), cnt = c.size();
		while (1) {
			cx.push_back(a);
			if (!exi(a, d)) { d = nxd(a); };
			if (d == -1) break;
			pir b = a + D[d];
			id[a.x][a.y][d] = id[b.x][b.y][d ^ 2] = cnt;
			a = b;
		}
		c.push_back(cx);
	};
	if (o.size()) findp(o[0]);
	for (int i = 1; i <= nx; ++i) for (int j = 1; j <= ny; ++j) {
		if (nxd({i, j}) != -1) findp({i, j});
	}
	int cnt = c.size() - 1;
	vint pa(cnt + 1); iota(pa.begin(), pa.end(), 0);
	function<int(int)> find = [&](int i) { return pa[i] == i ? i : pa[i] = find(pa[i]); };
	
	auto tmerg = [&](pir t) {
		vint cc; auto [x, y] = t;
		for (int i = 0; i < 4; ++i) if (id[x][y][i]) cc.push_back(find(id[x][y][i]));
		sort(cc.begin(), cc.end()); cc.erase(unique(cc.begin(), cc.end()), cc.end());
		assert(cc.size() <= 2);
		if (cc.size() == 2) {
			int A = cc[0], B = cc[1];
			if (c[B].back() != c[B][0]) swap(A, B);
			
			assert(c[B].back() == c[B][0]); // B is cycle
			pa[B] = A;
			c[B].pop_back();
			for (int i = 0; i < c[B].size(); ++i) {
				if (c[B][i] == t) {
					vpir rs(c[B].size());
					copy(c[B].begin() + i + 1, c[B].end(), rs.begin());
					copy(c[B].begin(), c[B].begin() + i + 1, rs.begin() + c[B].size() - i - 1);
					c[B].swap(rs); break;
				}
			}
			for (int i = 0; i < c[A].size(); ++i) {
				if (c[A][i] == t) {
					vpir rs(c[A].size() + c[B].size());
					copy(c[A].begin(), c[A].begin() + i + 1, rs.begin());
					copy(c[B].begin(), c[B].end(), rs.begin() + i + 1);
					copy(c[A].begin() + i + 1, c[A].end(), rs.begin() + i + 1 + c[B].size());
					c[A].swap(rs); vpir().swap(c[B]); break;
				}
			}
			for (int i = 1; i < c[A].size(); ++i) assert(c[A][i].x == c[A][i - 1].x || c[A][i].y == c[A][i - 1].y);
		}
	};
	
	for (pir t : o) tmerg(t);
	for (int i = 1; i <= nx; ++i) for (int j = 1; j <= ny; ++j) tmerg({i, j});
	
	vpir ans;
	int cct = 0; for (int i = 1; i <= cnt; ++i) if (find(i) == i) ++cct, ans = c[i];
	if (cct > 1) { cout << 0 << '\n'; return; }
	
	
	for (int i = 1; i < ans.size(); ++i) assert(ans[i].x == ans[i - 1].x || ans[i].y == ans[i - 1].y);
	
	vpir pt;
	pt.push_back(ans[0]);
	for (int i = 1; i + 1 < ans.size(); ++i) {
		if ((ans[i].x == ans[i - 1].x) ^ (ans[i].x == ans[i + 1].x)) pt.push_back(ans[i]);
	}
	pt.push_back(ans.back());
	cerr << o.size() << endl;
	cout << pt.size() << '\n';
	for (int i = 0; i < pt.size(); ++i)
		cout << px[pt[i].x] << ' ' << py[pt[i].y] << '\n';
}

int main() {
	freopen("bot.in", "r", stdin);
	freopen("bot.out", "w", stdout);
	pre();
	solve();
	
	
	return 0;
}
