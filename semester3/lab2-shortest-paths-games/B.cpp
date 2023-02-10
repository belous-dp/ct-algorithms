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
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a - 1].push_back({ b - 1, w });
        g[b - 1].push_back({ a - 1, w });
    }
    priority_queue<pii> q; // dist, vertex
    q.push({ 0, 0 });
    for (int i = 1; i < n; ++i) {
        q.push({ -INF, i });
    }
    vector<int> dist(n, INF);
    dist[0] = 0;
    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
        for (auto [u, w] : g[v]) {
            if (dist[u] > -d + w) {
                dist[u] = -d + w;
                q.push({ -dist[u], u });
            }
        }
    }
    for (int i : dist) {
        cout << i << ' ';
    }
    cout << '\n';
}