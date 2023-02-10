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

void dfs(int v, int col, vector<vector<int>> const& g, vector<int>& used, vector<int>& topsort) {
    used[v] = col;
    for (int u : g[v]) {
        if (used[u] == 0) {
            dfs(u, col, g, used, topsort);
        }
    }
    topsort.push_back(v);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), revg(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        revg[b - 1].push_back(a - 1);
    }
    vector<int> topsort, used(n);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, 1, g, used, topsort);
        }
    }
    reverse(all(topsort));
    used.assign(n, 0);
    int ncomp = 0;
    vector<int> thrash;
    for (int i : topsort) {
        if (!used[i]) {
            dfs(i, ++ncomp, revg, used, thrash);
        }
    }
    int ans = 0;
    vector<vector<int>> cond(ncomp);
    set<pii> edges;
    for (int i = 0; i < n; ++i) {
        for (int j : g[i]) {
            if (used[i] != used[j]) {
                cond[used[i]].push_back(used[j]);
                edges.insert({ used[i], used[j] });
            }
        }
    }
    cout << edges.size() << '\n';
}
