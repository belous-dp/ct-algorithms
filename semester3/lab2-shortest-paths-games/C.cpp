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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (auto& i : g) {
        for (int& j : i) {
            cin >> j;
        }
    }
    vector<int> dist(n, INF), par(n, -1);
    dist[0] = 0;
    int k = 0, updated;
    for (; k < n; ++k) {
        updated = -1;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (g[u][v] != 100000 && dist[v] > dist[u] + g[u][v]) {
                    dist[v] = dist[u] + g[u][v];
                    par[v] = u;
                    updated = v;
                }
            }
        }
        if (updated == -1) {
            break;
        }
    }
    if (k < n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int on_cycle = updated;
    for (int i = 0; i < n; ++i, on_cycle = par[on_cycle]);
    vector<int> cycle = { on_cycle };
    for (int v = par[on_cycle]; v != on_cycle; v = par[v]) {
        cycle.push_back(v);
    }
    cout << cycle.size() << '\n';
    reverse(all(cycle));
    for (int i : cycle) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}