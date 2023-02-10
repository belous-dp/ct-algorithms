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

void dfs(int v, vector<vector<int>> const& g, vector<int>& used, vector<int>& topsort) {
    used[v] = 1;
    for (int u : g[v]) {
        if (used[u] == 1) {
            cout << "-1\n";
            exit(0);
        } else if (used[u] == 0) {
            dfs(u, g, used, topsort);
        }
    }
    topsort.push_back(v);
    used[v] = 2;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
    }
    vector<int> topsort, used(n);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, g, used, topsort);
        }
    }
    reverse(all(topsort));
    for (int i : topsort) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}