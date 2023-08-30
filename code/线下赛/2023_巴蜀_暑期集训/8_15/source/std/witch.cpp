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

	template <int M>
	struct ModInt {
		static int const MOD = M;
		
		int v;
		
		ModInt() : v(0) { }
		
		ModInt(long long v) {
			if (-MOD <= v && v < 2 * MOD) {
				if (v >= MOD) {
					v -= MOD;
				}
				else if (v < 0) {
					v += MOD;
				}
			}
			else {
				v %= MOD;
				if (v < 0) {
					v += MOD;
				}
			}
			
			this->v = v;
		}
			
		ModInt operator++(signed) {
			auto t = *this;
			operator+=(1);
			return t;
		}
		
		ModInt& operator++() {
			operator+=(1);
			return *this;
		}
		
		ModInt operator--(signed) {
			auto t = *this;
			operator-=(1);
			return t;
		}
		
		ModInt& operator--() {
			operator-=(1);
			return *this;
		}
		
		ModInt& operator+=(const ModInt& rhs) {
			v = v + rhs.v >= MOD ? v + rhs.v - MOD : v + rhs.v;
			return *this;
		}
		
		friend ModInt operator+(const ModInt& lhs, const ModInt& rhs) {
			ModInt res = lhs;
			res += rhs;
			
			return res;
		}
		
		ModInt& operator-=(const ModInt& rhs) {
			v = v - rhs.v < 0 ? v - rhs.v + MOD : v - rhs.v;
			return *this;
		}
		
		friend ModInt operator-(const ModInt& lhs, const ModInt& rhs) {
			ModInt res = lhs;
			res -= rhs;
			
			return res;
		}
		
		ModInt& operator*=(const ModInt& rhs) {
			v = 1ll * v * rhs.v % MOD;
			return *this;
		}
		
		friend ModInt operator*(const ModInt& lhs, const ModInt& rhs) {
			ModInt res = lhs;
			res *= rhs;
			
			return res;
		}
		
		ModInt fpow(long long p) const {		
			if (p < 0) {
				return fpow(-p).inv();
			}
			else if (!p) {
				return 1;
			}
			else if (p == 1) {
				return *this;
			}
			else if (p == 2) {
				return *this * *this;
			}
			else {
				return fpow(p / 2).fpow(2) * fpow(p % 2);
			}
		}
		
		friend bool operator==(const ModInt& a, const ModInt& b) {
			return a.v == b.v;
		}
		
		friend bool operator!=(const ModInt& a, const ModInt& b) {
			return a.v != b.v;
		}
		
		friend ModInt operator-(const ModInt& a) {
			ModInt res;
			if (a.v == 0) {
				return 0;
			}
			
			res.v = MOD - a.v;
			return res;
		}
		
		ModInt inv() const {
			return fpow(MOD - 2);
		}
		
		ModInt operator/=(const ModInt& rhs) {
			// O(log MOD)
			return operator*=(rhs.inv());
		}
		
		friend ModInt operator/(const ModInt& lhs, const ModInt& rhs) {
			ModInt res = lhs;
			res /= rhs;
			
			return res;
		}
		
		bool is_square() const {
			return v == 0 || fpow((MOD - 1) / 2).v == 1;
		}
		
		ModInt sqrt() const {
			static std::mt19937 mt(42334435);
			static ModInt isq;
			
			assert(is_square());
			
			struct Complex {
				ModInt a, b;
				
				Complex operator*(const Complex& rhs) const {
					return { a * rhs.a + isq * b * rhs.b, a * rhs.b + b * rhs.a };
				}
				
				Complex fpow(int n) {
					if (!n) {
						return { 1, 0 };
					}
					else if (n == 1) {
						return *this;
					}
					else if (n == 2) {
						return operator*(*this);
					}
					else {
						return fpow(n / 2).fpow(2) * fpow(n % 2);
					}
				}
			};
			
			if (v == 0) {
				return 0;
			}
			
			ModInt b;
			while (true) {
				b = mt() % MOD;
				if (!(b * b - *this).is_square()) {
					break;
				}
			}
			
			isq = b * b - *this;
			
			Complex c = { b, 1 };
			auto res = c.fpow((MOD + 1) / 2).a;
			return std::min(res.v, MOD - res.v);
		}
	};

	template <int MOD>
	std::istream& operator>>(std::istream& in, ModInt<MOD>& mint) {
		long long v;
		in >> v;
		mint = ModInt<MOD>(v);
		
		return in;
	}

	template <int MOD>
	std::ostream& operator<<(std::ostream& out, const ModInt<MOD>& mint) {
		return out << mint.v;
	}

	template <class T, int B>
	struct FastPow {
		T baby[B + 1];
		T gaint[B + 1];
		
		FastPow(T b) {
			baby[0] = 1;
			for (int i = 1; i <= B; i++) {
				baby[i] = baby[i - 1] * b;
			}
			
			gaint[0] = 1;
			for (int i = 1; i <= B; i++) {
				gaint[i] = gaint[i - 1] * baby[B];
			}
		}
		
		T get(int n) {
			return gaint[n / B] * baby[n % B];
		}
	};

	int const MOD = 998244353;

	template <int M>
	const int ModInt<M>::MOD;

	using Mint = ModInt<MOD>;

	int const N = 1e5 + 10;

	using Val = std::array<std::array<std::array<Mint, 2>, 2>, 2>;

	Val vplus(Val a, const Val& b) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					a[i][j][k] += b[i][j][k];
				}
			}
		}

		return a;
	}

	Val vsub(Val a, const Val& b) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					a[i][j][k] -= b[i][j][k];
				}
			}
		}

		return a;
	}

	struct SegmentTree {
		struct Node {
			int ls, rs;
			Val v;
		};

		Node nd[20 * N + 1];
		int tot;

		int create() {
			tot++;
			nd[tot] = {};
			return tot;
		}

		void update(int& x, int p, Val v, int rl, int rr) {
			if (!x) {
				x = create();
			}

			if (rl == rr) {
				nd[x].v = vplus(nd[x].v, v);
			}
			else {
				int mid = (rl + rr) >> 1;

				if (p <= mid) {
					update(nd[x].ls, p, v, rl, mid);
				}
				else {
					update(nd[x].rs, p, v, mid + 1, rr);
				}

				pushup(x);
			}
		}

		void pushup(int x) {
			nd[x].v = vplus(nd[nd[x].ls].v, nd[nd[x].rs].v);
		}

		Val prod(int x, int l, int r, int rl, int rr) {
			if (l > r) {
				return {};
			}

			if (!x) {
				return {};
			}

			if (rl >= l && rr <= r) {
				return nd[x].v;
			}
			else {
				int mid = (rl + rr) >> 1;

				if (r <= mid) {
					return prod(nd[x].ls, l, r, rl, mid);
				}
				else if (l > mid) {
					return prod(nd[x].rs, l, r, mid + 1, rr);
				}
				else {
					return vplus(prod(nd[x].ls, l, r, rl, mid), prod(nd[x].rs, l, r, mid + 1, rr));
				}
			}
		}

		int merge(int x, int y) {
			if (!x || !y) {
				return x + y;
			}
			else {
				nd[x].v = vplus(nd[x].v, nd[y].v);
				nd[x].ls = merge(nd[x].ls, nd[y].ls);
				nd[x].rs = merge(nd[x].rs, nd[y].rs);
				return x;
			}
		}
	};

	struct Node {
		int x, v;
	};

	int n;
	SegmentTree seg;
	std::vector<Node> tree[N + 1];
	int dep[N + 1];
	int prt[N + 1];
	Val f[N + 1];
	int rt[N + 1];

	void dfs(int x, int fa) {
		prt[x] = fa;

		for (auto& to : tree[x]) {
			if (to.x != fa) {
				dep[to.x] = dep[x] + to.v;
				dfs(to.x, x);
			}
		}
	}

	void solve(int x, int i) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					f[x][i][j][k] = 0;
				}
			}
		}

		rt[x] = 0;

		f[x][0][0][0] = 1;
		f[x][0][1][0] = 1;
		f[x][1][0][0] = 1;
		f[x][1][0][1] = 1;

		int d = dep[x] & ((1 << (i + 1)) - 1);
		for (auto& to : tree[x]) {
			if (to.x == prt[x]) {
				continue;
			}

			solve(to.x, i);

			Val t = f[x];
		
			auto t1 = seg.prod(rt[to.x], (1 << i) + d, (1 << (i + 1)) - 1, 0, (1 << (i + 1)) - 1);
			t1 = vplus(t1, seg.prod(rt[to.x], std::max(0, d - (1 << i)), d - 1, 0, (1 << (i + 1)) - 1));

			auto t2 = vsub(seg.prod(rt[to.x], 0, (1 << (i + 1)) - 1, 0, (1 << (i + 1)) - 1), t1);

			for (int p = 0; p < 2; p++) {
				for (int q = 0; q < 2; q++) {
					for (int a = 0; a < 2; a++) {
						for (int b = 0; b + p < 2; b++) {
							for (int c = 0; c + q < 2; c++) {
								t[a][b + p][c + q] += t1[a ^ 1][p][q] * f[x][a][b][c];
								t[a][b + p][c + q] += t2[a][p][q] * f[x][a][b][c];
							}
						}
					}
				}
			}

			rt[x] = seg.merge(rt[x], rt[to.x]);
			f[x] = t;
		}

		seg.update(rt[x], d, f[x], 0, (1 << (i + 1)) - 1);	
	}

	Mint solve(int i) {
		seg.tot = 0;
		solve(1, i);

		Mint ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += f[i][0][1][1];
		}

		return ans;
	}

	void main() {
		std::cin >> n;
		for (int i = 2; i <= n; i++) {
			int u, v, w;
			std::cin >> u >> v >> w;
			tree[u].push_back({ v, w });
			tree[v].push_back({ u, w });
		}

		dfs(1, 0);

		Mint ans = 0;
		for (int i = 0; i <= 20; i++) {
			ans += solve(i) * (1 << i);
		}

		fmtout("{}\n", ans);
	}

	void init() {
		
	}

	void clear() {

	}
}

signed main() {
#ifndef ONLINE_JUDGE
	auto input_file = freopen("witch.in", "r", stdin);
	auto output_file = freopen("witch.out", "w", stdout);
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
