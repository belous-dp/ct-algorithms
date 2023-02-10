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

void top_sort(int v, vector<vector<int>> const& g, vector<bool>& used, vector<int>& topsort) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            top_sort(u, g, used, topsort);
        }
    }
    topsort.push_back(v);
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> g(n), revg(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        revg[b - 1].push_back(a - 1);
    }
    vector<int> topsort;
    vector<bool> used(n);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            top_sort(i, revg, used, topsort);
        }
    }
    reverse(all(topsort));
    vector<int> color(n, 1); // 0 -- lose, 1 -- draw, 2 -- win
    for (int i = 0; i < n; ++i) {
        if (g[i].empty()) {
            color[i] = 0;
        }
    }
    for (int v : topsort) {
        if (color[v] != 1) {
            continue;
        }
        bool lose = true;
        bool win = false;
        for (int u : g[v]) {
            lose &= color[u] == 2;
            win |= color[u] == 0;
        }
        assert(win != lose);
        color[v] = lose ? 0 : 2;
    }
    cout << (color[s - 1] == 2 ? "First" : "Second") << " player wins\n";
}