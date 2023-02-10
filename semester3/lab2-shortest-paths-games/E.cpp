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
constexpr ll INF1 = 4e18 + 5;

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
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int, ll>>> g(n);
    while (m--) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        g[a - 1].push_back({ b - 1, w });
    }
    vector<ll> dist(n, INF1);
    dist[--s] = 0;
    vector<bool> used(n); // after the last iteration means
                          // whether the vertex is accessible
                          // from a cycle of negative weight
    for (int k = 0; k < n; ++k) {
        used.assign(n, false);
        for (int u = 0; u < n; ++u) {
            if (dist[u] == INF1) {
                continue;
            }
            for (auto [v, w] : g[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    used[v] = true;
                }
            }
        }
        cout << "step " << k << ". updated: ";
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                cout << i + 1 << ' ';
            }
        }
        cout << '\n';
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, _] : g[u]) {
            if (!used[v]) {
                used[v] = true;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            cout << "-\n";
        } else if (dist[i] == INF1) {
            cout << "*\n";
        } else {
            cout << dist[i] << '\n';
        }
    }
    cout << '\n';
}