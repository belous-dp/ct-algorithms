#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define mp make_pair
#define all(x) x.begin(), x.end()
#define multi_test 0

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

constexpr int MAXN = 3e5 + 7;
constexpr ll MOD = 1e9 + 7;
constexpr int INF = 1e9 + 5;
constexpr ll INF1 = 2e18;

void solve();

signed main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int q = 1;
	if (multi_test) cin >> q;
	while (q--) solve();
}

/*-------------------------------------------------------------------------------------------------------*/

int Time = 0;

int dfs(int v, int par, vector<vector<int>> const& g,
	vector<int>& tin, vector<int>& up, vector<int>& art_pts) {
	up[v] = tin[v] = Time++;
	bool is_art_pt = false;
	int num_children = 0;
	for (int u : g[v]) {
		/*if (u == par) {
			continue;
		} else */
		if (tin[u] == -1) {
			num_children++;
			dfs(u, v, g, tin, up, art_pts);
			if (up[u] >= tin[v]) {
				is_art_pt = true;
			} else {
				up[v] = min(up[v], up[u]);
			}
		} else {
			up[v] = min(up[v], tin[u]);
		}
	}
	if (is_art_pt) {
		art_pts.push_back(v);
	}
	return num_children;
}


void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		g[b - 1].push_back(a - 1);
		g[a - 1].push_back(b - 1);
	}
	vector<int> tin(n, -1), up(n), ans;
	for (int i = 0; i < n; ++i) {
		if (tin[i] == -1) {
			if (dfs(i, -1, g, tin, up, ans) == 1) {
				assert(ans.back() == i);
				ans.pop_back();
			}
		}
	}
	sort(all(ans));
	cout << ans.size() << '\n';
	for (int i : ans) {
		cout << i + 1 << ' ';
	}
	cout << '\n';
}