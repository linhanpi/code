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

	int const MOD = 998244353;

	template <int M>
	const int ModInt<M>::MOD;

	using Mint = ModInt<MOD>;

	int const N = 2e7;

	int n;
	int minf[N + 1];
	int mp[N + 1];
	int mu[N + 1];
	int d[N + 1];
	int sd[N + 1];
	int smu[N + 1];
	std::vector<int> prs;

	Mint f(int n) {
		Mint ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += sd[i] * d[n - i];
		}

		return ans;
	}

	Mint F(int n) {
		Mint ans = 0;
		for (int d = 1; d <= n; d++) {
			int j = std::min(n, n / (n / d));
			ans += (smu[j] - smu[d - 1]) * f(n / d);
			d = j;
		}

		return ans;
	}

	void main() {
		std::cin >> n;

		auto t = F(n);
		fmtout("{}\n", t * 2 + Mint(n) * n);
	}

	void init() {
		minf[1] = mu[1] = d[1] = mp[1] = 1;
		for (int i = 2; i <= N; i++) {
			if (!minf[i]) {
				minf[i] = i;
				mu[i] = -1;
				d[i] = 2;
				mp[i] = i;
				prs.push_back(i);
			}

			for (auto& v : prs) {
				if (i * v > N) {
					break;
				}

				minf[i * v] = v;
				if (v == minf[i]) {
					mp[i * v] = v * mp[i];
					mu[i * v] = 0;
					d[i * v] = (1 + d[mp[i]]) * d[i / mp[i]];
					break;
				}
				else {
					mu[i * v] = -mu[i];
					mp[i * v] = v;
					d[i * v] = 2 * d[i];
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			sd[i] = sd[i - 1] + d[i];
			smu[i] = smu[i - 1] + mu[i];
		}
	}

	void clear() {

	}
}

signed main() {
	auto input_file = freopen("jigsaw.in", "r", stdin);
	auto output_file = freopen("jigsaw.out", "w", stdout);
	
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

	std::cout.flush();
	fclose(input_file);
	fclose(output_file);
	
	return 0;
}
