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
int Comps = 0;

void dfs(int v, int par, vector<vector<pii>> const& g,
				vector<int>& tin, vector<int>& up,
				vector<int>& buf, vector<int>& comp) {
	up[v] = tin[v] = Time++;
	buf.push_back(v);
	for (pii p : g[v]) {
		int u = p.first, id = p.second;
		if (id == par) {
			continue;
		} else if (tin[u] == -1) {
			dfs(u, id, g, tin, up, buf, comp);
			up[v] = min(up[v], up[u]);
		} else {
			up[v] = min(up[v], tin[u]);
		}
	}
	if (up[v] == tin[v]) { // pv is a bridge
		int compid = ++Comps;
		int u = -1;
		do {
			u = buf.back();
			comp[u] = compid;
			buf.pop_back();
		} while (u != v);
	}
}


void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<pii>> g(n);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		g[a - 1].push_back({ b - 1, i });
		g[b - 1].push_back({ a - 1, i });
	}
	vector<int> tin(n, -1), up(n), ans(n), buf;
	for (int i = 0; i < n; ++i) {
		if (tin[i] == -1) {
			dfs(i, -1, g, tin, up, buf, ans);
		}
	}
	cout << Comps << '\n';
	for (int i : ans) {
		cout << i << ' ';
	}
	cout << '\n';
}