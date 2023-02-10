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

struct edge {
	int to, id, groupid;
	friend bool operator <(edge const& lhs, edge const& rhs) {
		if (lhs.to != rhs.to) {
			return lhs.to < rhs.to;
		}
		return lhs.id < rhs.id;
	}
};

void dfs(int v, int par, vector<vector<edge>> const& g,
			vector<int>& tin, vector<int>& up,
			vector<int>& comps, vector<int>& buf) {
	up[v] = tin[v] = Time++;
	for (auto e : g[v]) {
		int u = e.to;
		if (u == par) {
			continue;
		} else if (tin[u] == -1) { // not visited
			buf.push_back(e.groupid);
			dfs(u, v, g, tin, up, comps, buf);
			if (up[u] >= tin[v]) { // articulation point
				Comps++;
				while (true) {
					int gid = buf.back();
					buf.pop_back();
					comps[gid] = Comps;
					if (e.groupid == gid) {
						break;
					}
				}
			} else {
				up[v] = min(up[v], up[u]);
			}
		} else if (tin[u] < tin[v]) { // ancestor
			up[v] = min(up[v], tin[u]);
			buf.push_back(e.groupid);
		} else if (up[v] > tin[u]) { // child
			up[v] = min(up[v], up[u]);
		}
	}
}


void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<edge>> g(n);
	vector<int> edgegid;
	map<pii, int> groups;
	int gid = 0;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		int id;
		auto it = groups.find({ a, b });
		if (it != groups.end()) {
			id = it->second;
		} else {
			id = groups[{ a, b }] = groups[{ b, a }] = gid++;
		}
		g[b].push_back({ a, i, id });
		g[a].push_back({ b, i, id });
		edgegid.push_back(id);
	}
	vector<int> tin(n, -1), up(n), group_color(gid), buf;
	for (int i = 0; i < n; ++i) {
		if (tin[i] == -1) {
			dfs(i, -1, g, tin, up, group_color, buf);
		}
	}
	cout << Comps << '\n';
	for (int i = 0; i < m; ++i) {
		cout << group_color[edgegid[i]] << ' ';
	}
	cout << '\n';
}