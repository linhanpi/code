#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int MOD = 998244353;

int binpow(int x, int n) {
	int res = 1;
	while (n) {
		if (n % 2 == 1) {
			res = (res * x) % MOD;
		}
		x = (x * x) % MOD;
		n /= 2;
	}
	return res;
}

namespace fft {

int gen = 363395222;

void init() {
	for (int i = 1;; ++i) {
		if (binpow(i, (1 << (18 - 1))) == MOD - 1) {
			gen = i;
			break;
		}
	}
}

const int MAXT = 18, MAXN = (1 << MAXT);
int rev[MAXN];
int roots[MAXN];
int rt;

void build(int t = MAXT) {
	rt = gen;
	for (int i = t; i < MAXT; ++i) {
		rt = (rt * rt) % MOD;
	}
	roots[0] = 1;
	for (int i = 1; i < (1 << t); ++i) {
		roots[i] = (roots[i - 1] * rt) % MOD;
	}
	for (int i = 0; i < (1 << t) / 2; ++i) {
		rev[2 * i] = rev[i] / 2;
		rev[2 * i + 1] = rev[i] / 2 + (1 << t) / 2;
	}
}

void fft(vector<int> &val, int t = MAXT) {
	for (int i = 0; i < (1 << t); ++i) {
		if (i < rev[i]) {
			swap(val[i], val[rev[i]]);
		}
	}
	for (int n = 2; n <= (1 << t); n *= 2) {
		for (int s = 0; s < (1 << t); s += n) {
			for (int i = 0; i < n / 2; ++i) {
				int v0 = val[s + i];
				int v1 = val[s + i + n / 2];
				int x = (v1 * roots[i * ((1 << t) / n)]) % MOD;
				val[s + i] = (v0 + x) % MOD;
				val[s + i + n / 2] = (v0 - x + MOD) % MOD;
			}
		}
	}
}

void inv_fft(vector<int> &val, int t = MAXT) {
	fft(val, t);
	reverse(val.begin() + 1, val.end());
	int k = (1 - MOD) / (1 << t);
	k = (k % MOD + MOD) % MOD;
	for (int i = 0; i < (1 << t); ++i) {
		val[i] = (k * val[i]) % MOD;
	}
}
} // namespace fft

vector<int> operator*(const vector<int> &a, const vector<int> &b) {
	int t = 0;
	while ((1 << t) < (int)a.size() + (int)b.size()) {
		t++;
	}
	vector<int> af((1 << t), 0);
	fft::build(t);
	for (int i = 0; i < (int)a.size(); ++i) {
		af[i] = a[i];
	}
	vector<int> bf((1 << t), 0);
	for (int i = 0; i < (int)b.size(); ++i) {
		bf[i] = b[i];
	}
	fft::fft(af, t);
	fft::fft(bf, t);
	vector<int> cf((1 << t), 0);
	for (int i = 0; i < (1 << t); ++i) {
		cf[i] = (af[i] * bf[i]) % MOD;
	}
	fft::inv_fft(cf, t);
	vector<int> c((int)a.size() + (int)b.size() - 1);
	for (int i = 0; i < (int)c.size(); ++i) {
		c[i] = cf[i];
	}
	for (auto &elem : c) {
		elem = (elem % MOD + MOD) % MOD;
	}
	return c;
}

const int MAXK = 18;
vector<int> f[MAXK][MAXK][2];

int fact[1 << MAXK], invf[1 << MAXK];

void init_fact() {
	fact[0] = 1;
	for (int i = 1; i < (1 << MAXK); ++i) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	invf[(1 << MAXK) - 1] = binpow(fact[(1 << MAXK) - 1], MOD - 2);
	for (int i = (1 << MAXK) - 1; i > 0; --i) {
		invf[i - 1] = (invf[i] * i) % MOD;
	}
}

int C(int n, int k) {
	if (k < 0 || k > n) return 0;
	int ans = (invf[k] * invf[n - k]) % MOD;
	return (ans * fact[n]) % MOD;
}

vector<int> get_binom(int n) {
	n = max(n, (int64_t)0);
	vector<int> ans(n + 1);
	for (int i = 0; i <= n; ++i) {
		ans[i] = C(n, i);
	}
	return ans;
}

int32_t main() {
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	// cerr << binpow(fft::gen, (1 << 19)) << "\n";

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> MOD;
	fft::init();
	init_fact();
	for (int t = 0; t < MAXK - 1; ++t) {
		auto res = get_binom((1 << t) - 2);
		f[t][t + 1][0].resize((1 << (t + 1)), 0);
		for (int i = 0; i < (int)res.size(); ++i) {
			f[t][t + 1][0][i + (1 << t)] = res[i];
		}
		f[t][t + 1][1] = f[t][t + 1][0];
		for (int k = t + 1; k < MAXK - 1; ++k) {
			f[t][k + 1][0].resize((1 << (k + 1)), 0);
			for (int i = 0; i < (1 << k); ++i) {
				f[t][k + 1][0][i + (1 << k)] = f[t][k][0][i];
			}
			auto res = get_binom((1 << k) - 1);
			res = f[t][k][1] * res;
			for (int i = 0; i < (int)res.size(); ++i) {
				f[t][k + 1][0][i] += res[i];
			}
			f[t][k + 1][1] = f[t][k + 1][0];
			for (int i = 0; i < (1 << k); ++i) {
				f[t][k + 1][1][i + (1 << k)] += f[t][k][1][i];
			}
			for (int i = 0; i < (int)res.size(); ++i) {
				f[t][k + 1][1][i + 1] += res[i];
			}
			for (int i = 0; i < (1 << (k + 1)); ++i) {
				f[t][k + 1][0][i] %= MOD;
				f[t][k + 1][1][i] %= MOD;
			}
		}
	}

	int tst;
	cin >> tst;
	while (tst--) {
		int k, n, p;
		cin >> k >> n >> p;
		int t = 0;
		while (p % 2 == 0) {
			p /= 2;
			++t;
		}
		if (p != 1) {
			cout << "0\n";
			continue;
		}
		if (t == k) {
			if (n == (1 << t)) {
				cout << "1\n";
			} else {
				cout << "0\n";
			}
			continue;
		}
		if (n == (1 << k)) {
			cout << "0\n";
			continue;
		}
		cout << f[t][k][1][n] << "\n";
	}
	return 0;
}
