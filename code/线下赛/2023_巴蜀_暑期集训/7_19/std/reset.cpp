#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define pii pair<int, int>
#define ld long double
#define all(a) (a).begin(), (a).end()

#define int long long

signed main() {
	freopen("reset.in", "r", stdin);
	freopen("reset.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, q;
	cin >> n >> q;
	vector<int> w(n);
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
	}
	sort(all(w));

	vector<vector<pii>> stacks = {{{0, 0}}};
	bool state = 0; // start
	int pref_sum = 0;
	for (int i = 0; i < w.size(); ++i) {
		if (w[i] > pref_sum + 1) break; // nothing changes after

		if (state == 0) {
			if (2 * w[i] - pref_sum - 2 <= 0) {
				stacks.push_back({{0, pref_sum + w[i]}});
			} else {
				state = 1;
			}
		}
		if (state == 1) {
			auto tmp = stacks.back();
			if (tmp.back().first >= w[i] - 1) {
				tmp.back().first += w[i];
			} else {
				tmp.push_back({(pii){w[i] * 2 - 1, pref_sum - w[i] + 1}});
			}
			stacks.push_back(tmp);
		}
		pref_sum += w[i];
	}
	int z;
	cin >> z;

	int u = 0;
	for (int i = 0; i < q; ++i) {
		int a, b, j;
		cin >> j >> a >> b;
		int k = j - u * z;
		a -= u * z;
		b -= u * z;
		if (a < b) swap(a, b);
		int st_ind = min((int)stacks.size() - 1, (int)(upper_bound(all(w), k) - w.begin()));
		int pt_ind = upper_bound(all(stacks[st_ind]), (pii){a, -1}) - stacks[st_ind].begin();

		bool ans = 0;

		if (pt_ind != stacks[st_ind].size()) {
			ans |= (b <= stacks[st_ind][pt_ind].second);
		}
		if (pt_ind > 0) {
			ans |= (a + b <= stacks[st_ind][pt_ind - 1].first + stacks[st_ind][pt_ind - 1].second);
		}
		cout << (ans ? "Yes" : "No") << '\n';
		u += (i + 1) * ans;
	}

	return 0;
}
