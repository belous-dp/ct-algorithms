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

constexpr int MAXN = 1e3 + 1;
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

void dfs(int v, int col, int tank_size, vector<vector<pii>> const& g, vector<int>& used, vector<int>& topsort) {
    used[v] = col;
    for (auto p : g[v]) {
        int u = p.first, w = p.second;
        if (used[u] == 0 && w <= tank_size) {
            dfs(u, col, tank_size, g, used, topsort);
        }
    }
    topsort.push_back(v);
}

vector<int> csc(int tank_size, vector<vector<pii>> const& g, vector<vector<pii>> const& revg) {
    int n = g.size();
    vector<int> topsort, used(n);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, 1, tank_size, g, used, topsort);
        }
    }
    reverse(all(topsort));
    used.assign(n, 0);
    int ncomp = 0;
    vector<int> thrash;
    for (int i : topsort) {
        if (!used[i]) {
            dfs(i, ++ncomp, tank_size, revg, used, thrash);
        }
    }
    return used;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<pii>> g(n), revg(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int d;
            cin >> d;
            if (i != j) {
                g[i].push_back({ j, d });
                revg[j].push_back({ i, d });
            }
        }
    }
    int left = -1, right = INF;
    vector<bool> used(n);
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        vector<int> const& comps = csc(mid, g, revg);
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            ok &= comps[i] == 1;
        }
        if (ok) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cout << right << '\n';
}