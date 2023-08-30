#include <bits/stdc++.h>

namespace IO {
	template <class Stream>
	Stream& fmtbase(Stream& out, const char* format) {
		for (; *format; format++) {
			if (*format == '{' && *(format + 1) == '}') {
				throw std::invalid_argument("Error Number of Parameters!");
			}
			
			out << *format;
		}
		
		return out;
	}
	
	template <class Stream, class Fst, class... Nxt>
	Stream& fmtbase(Stream& out, const char* format, const Fst& value, const Nxt&... nxt) {
		for (; *format; format++) {
			if (*format == '{' && *(format + 1) == '}') {
				out << value;
				return fmtbase(out, format + 2, nxt...);
			} 
			
			out << *format;
		}
		
		throw std::invalid_argument("Error Number of Parameters!");
	}
	
	template <class... Ps>
	std::string to_string(const char* format, const Ps&... ps) {
		std::stringstream ss;
		fmtbase(ss, format, ps...);
		return ss.str();
	}

	template <class... Ps>
	std::ostream& fmtout(const char* format, const Ps&... ps) {
		return fmtbase(std::cout, format, ps...);
	}
	
	template <class... Ps>
	std::ostream& fmterr(const char* format, const Ps&... ps) {
		return fmtbase(std::cerr, format, ps...);
	}
	
	std::istream& allin() {
		return std::cin;
	}
	
	template <class Fst, class ... Nxt>
	std::istream& allin(Fst& fst, Nxt&... nxt) {
		std::cin >> fst;
		return allin(nxt...);
	}
	
	template <class Iter>
	std::istream& rangin(Iter begin, Iter end) {
		while (begin != end) {
			std::cin >> *begin;
			begin++;
		}
		
		return std::cin;
	}
	
	namespace Fast {
		bool sync = false;
		
		char buf[1 << 23];
		char *p1 = buf, *p2 = buf;
		
		void sync_with_ios(bool s) {
			sync = s;
		}
		
		char getchar() {
			if (sync) {
				return (char) std::cin.get();
			}
			else {
				if (p1 == p2) {
					p1 = buf;
					p2 = p1 + fread(buf, 1, 1 << 22, stdin);
				}
				
				if (p1 == p2) {
					return EOF;
				}
				else {
					char res = *p1;
					p1++;
					return res;
				}
			}
		}
		
		void read() { }
		
		template <class T, class... U>
		void read(T& x, U&... us) {
			x = 0;
			T pos = 1;
			
			char c = getchar();
			while (!isdigit(c)) {
				if (c == '-') {
					pos = -1;
				}
				
				c = getchar();
			}
			
			while (isdigit(c)) {
				x = 10 * x + c - '0';
				c = getchar();
			}
			
			x *= pos;
			read(us...);
		}
		
		template <class T>
		void write(const T& t) {
			if (t > 10) {
				write(t / 10);
			}
			
			std::cout << (int) (t % 10);
		}
	}
}

namespace Solve {
	#define int long long

	using namespace IO;

	using ll = long long;
	using ul = unsigned long long;
	using db = double;
	using ld = long double;
	using ui = unsigned int;
	using ib = __int128;
	using ub = __uint128_t;

	int const INF = std::numeric_limits<int>::max();
	int const NINF = std::numeric_limits<int>::min();
	ll const LINF = std::numeric_limits<ll>::max();
	ll const LNINF = std::numeric_limits<ll>::min();
	ld const EPS = 1e-6;

	template <class T>
	inline int isz(const T& v) {
		return v.size();
	}

	std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	ll rnd(ll l, ll r) {
		return std::uniform_int_distribution<ll>(l, r)(mt);
	}

    int const N = 1e5 + 10;
	int const L = 55;
	int const B = (N + L - 1) / L + 10;

	struct SegmentTree {
		struct Node {
			int ls, rs;
			int v, t;
			int id;
		};

		Node nd[60 * N + 1];
		int tot;

		int create(int id) {
			tot++;
			nd[tot] = {};
			nd[tot].id = id;
			assert(tot <= 60 * N);
			return tot;
		}

		void tag(int x, int t, int rl, int rr) {
			nd[x].t += t;
			nd[x].v += t * (rr - rl + 1);
		}

		void pushup(int x, int rl, int rr) {
			nd[x].v = nd[nd[x].ls].v + nd[nd[x].rs].v;
			nd[x].v += (rr - rl + 1) * nd[x].t;
		}

		void modify(int& x, int l, int r, int t, int rl, int rr, int id) {
			if (!x) {
				x = create(id);
			}
			else if (nd[x].id != id) {
				int t = create(id);
				nd[t].ls = nd[x].ls;
				nd[t].rs = nd[x].rs;
				nd[t].v = nd[x].v;
				nd[t].t = nd[x].t;
				x = t;
			}

			if (rl >= l && rr <= r) {
				tag(x, t, rl, rr);
			}
			else {
				int mid = (rl + rr) >> 1;

				if (l <= mid) {
					modify(nd[x].ls, l, r, t, rl, mid, id);
				}

				if (r > mid) {
					modify(nd[x].rs, l, r, t, mid + 1, rr, id);
				}

				pushup(x, rl, rr);
			}
		}

		int prod(int x, int l, int r, int t, int rl, int rr) {
			if (!x) {
				return (int) t * (std::min(r, rr) - std::max(l, rl) + 1);
			}
			else if (rl >= l && rr <= r) {
				return nd[x].v + (rr - rl + 1) * t;
			}
			else {
				t += nd[x].t;
				int mid = (rl + rr) >> 1;
				int ans = 0;

				if (l <= mid) {
					ans += prod(nd[x].ls, l, r, t, rl, mid);
				}
				
				if (r > mid) {
					ans += prod(nd[x].rs, l, r, t, mid + 1, rr);
				}

				return ans;
			}
		}

		int merge(int x, int y, int rl, int rr, int id) {
			if (!x || !y) {
				return x + y;
			}
			else {
				int t = create(id);
				nd[t].v = nd[x].v + nd[y].v;
				nd[t].t = nd[x].t + nd[y].t;
				if (rl != rr) {
					int mid = (rl + rr) >> 1;
					nd[t].ls = merge(nd[x].ls, nd[y].ls, rl, mid, id);
					nd[t].rs = merge(nd[x].rs, nd[y].rs, mid + 1, rr, id);
				}

				return t;
			}
		}
	};

	struct Query {
		int l, r, id;
	};

	struct Seg {
		int x, l, r;
	};

	SegmentTree T;
	int son[N + 1][2];
	int h[N + 1];
	int pmi[N + 1];
	int pmx[N + 1];
	int tmi[N + 1];
	int tmx[N + 1];
	int rts[N + 1];
	int ans[N + 1];
	int rt;
	int n, q;
	int bv[N + 1];
	int bel[N + 1];
	int tol[B + 1];
	int tor[B + 1];
	int btot;
	int cnt[N + 1];
	std::vector<Seg> ss[N + 1];
	Query qs[N + 1];
	std::vector<int> add[N + 1];
	std::vector<int> del[N + 1];
	int vis[N + 1];

	void build() {
		std::vector<int> stk;
		for (int i = 1; i <= n; i++) {
			while (isz(stk) > 1 && h[stk[isz(stk) - 2]] < h[i]) {
				son[stk[isz(stk) - 2]][1] = stk[isz(stk) - 1];
				stk.pop_back();
			}

			if (isz(stk) && h[stk.back()] < h[i]) {
				son[i][0] = stk.back();
				stk.pop_back();
			}

			stk.push_back(i);
		}

		while (isz(stk) > 1) {
			son[stk[isz(stk) - 2]][1] = stk[isz(stk) - 1];
			stk.pop_back();
		}

		rt = stk[0];
	}

	void dfs(int x) {
		pmi[x] = pmx[x] = tmi[x] = tmx[x] = x;

		if (son[x][0]) {
			dfs(son[x][0]);
			pmi[x] = pmi[son[x][0]];
			rts[x] = T.merge(rts[x], rts[son[x][0]], 1, n, x);
			T.modify(rts[x], pmi[son[x][0]], pmx[son[x][0]], 1, 1, n, x);
			ss[x].push_back({ 1, pmi[son[x][0]], pmx[son[x][0]] });
		}

		if (son[x][1]) {
			dfs(son[x][1]);
			pmx[x] = pmx[son[x][1]];
			rts[x] = T.merge(rts[x], rts[son[x][1]], 1, n, x);
			T.modify(rts[x], pmi[son[x][1]], pmx[son[x][1]], 1, 1, n, x);
			ss[x].push_back({ 1, pmi[son[x][1]], pmx[son[x][1]] });
		}

		for (int t = 0; t < 2; t++) {
			int v = son[son[x][!t]][t];
			int c = 1;
			while (v) {
				T.modify(rts[x], tmi[v], tmx[v], -c, 1, n, x);
				ss[x].push_back({ -c, tmi[v], tmx[v] });
				tmi[x] = std::min(tmi[x], tmi[v]);
				tmx[x] = std::max(tmx[x], tmx[v]);

				v = son[v][t];
				c++;
			}
		}
	}

	void build(int x) {
		for (int i = tol[x]; i <= tor[x]; i++) {
			cnt[pmi[i]]++;
			cnt[pmx[i] + 1]--;
		}

		for (int i = 1; i <= n; i++) {
			cnt[i] += cnt[i - 1];
			if (cnt[i]) {
				for (auto& v : ss[i]) {
					bv[v.l] += (int) cnt[i] * v.x;
					bv[v.r + 1] -= (int) cnt[i] * v.x;
				}
			}
		}

		for (int i = 1; i <= n; i++) {
			bv[i] += bv[i - 1];
		}

		for (int i = 1; i <= n; i++) {
			bv[i] += bv[i - 1];
		}
	}

	void main() {
		std::cin >> n >> q;
		for (int i = 1; i <= n; i++) {
			std::cin >> h[i];
		}

		build();
		dfs(rt);

		for (int i = 1; i <= n; i++) {
			bel[i] = (i + L - 1) / L;
			if (!tol[bel[i]]) {
				tol[bel[i]] = i;
			}
			
			tor[bel[i]] = i;
		}
		btot = bel[n];
		
		for (int i = 1; i <= q; i++) {
			int l1, r1, l2, r2;
			std::cin >> l1 >> r1 >> l2 >> r2;

			qs[i] = { l1, r1 };

			if (bel[l2] == bel[r2]) {
				for (int j = l2; j <= r2; j++) {
					ans[i] += T.prod(rts[j], l1, r1, 0, 1, n);
				}
			}
			else {
				for (int j = l2; j <= tor[bel[l2]]; j++) {
					ans[i] += T.prod(rts[j], l1, r1, 0, 1, n);
				}

				for (int j = tol[bel[r2]]; j <= r2; j++) {
					ans[i] += T.prod(rts[j], l1, r1, 0, 1, n);
				}

				add[bel[l2] + 1].push_back(i);
				del[bel[r2]].push_back(i);
			}
		}

		for (int i = 1; i <= btot; i++) {
			build(i);

			for (auto& v : add[i]) {
				vis[v]++;
			}

			for (auto& v : del[i]) {
				vis[v]--;
			}

			for (int j = 1; j <= q; j++) {
				if (vis[j]) {
					ans[j] += bv[qs[j].r] - bv[qs[j].l - 1];
				}
			}

			for (int j = 1; j <= n; j++) {
				cnt[j] = 0;
				bv[j] = 0;
			}
		}

		for (int i = 1; i <= q; i++) {
			fmtout("{}\n", ans[i]);
		}
	}
	
	void init() {

	}

	void clear() {

	}
}

signed main() {
#ifndef ONLINE_JUDGE
	auto input_file = freopen("pepper.in", "r", stdin);
	auto output_file = freopen("pepper.out", "w", stdout);
#endif
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	int t = 1;
	// std::cin >> t;

	Solve::init();
	
	for (int id = 1; id <= t; id++) {
		Solve::main();
		Solve::clear();
	}

#ifndef ONLINE_JUDGE
	std::cout.flush();
	fclose(input_file);
	fclose(output_file);
#endif
	
	return 0;
}
