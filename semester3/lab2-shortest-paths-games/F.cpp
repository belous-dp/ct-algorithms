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

constexpr int MAXN = 1e5 + 7;
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

vector<pii> g[MAXN];
ll dist_from_a[MAXN], dist_from_b[MAXN], dist_from_c[MAXN];

void dijkstra(int s, int n, ll dist[MAXN]) {
    priority_queue<pli> q; // dist, vertex
    q.push({ 0, s });
    fill(dist, dist + MAXN, INF1);
    dist[s] = 0;
    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
        if (-d > dist[v]) {
            continue;
        }
        for (auto [u, w] : g[v]) {
            if (dist[u] > -d + w) {
                dist[u] = -d + w;
                q.push({ -dist[u], u });
            }
        }
    }
}

ll get_dist(ll d1, ll d2) {
    return (d1 == INF1 || d2 == INF1) ? INF1 : (d1 + d2);
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a - 1].push_back({ b - 1, w });
        g[b - 1].push_back({ a - 1, w });
    }
    int a, b, c;
    cin >> a >> b >> c;
    a--; b--; c--;
    dijkstra(a, n, dist_from_a);
    dijkstra(b, n, dist_from_b);
    dijkstra(c, n, dist_from_c);
    ll ans = INF1;
    ans = min(ans, get_dist(dist_from_a[b], dist_from_b[c]));
    ans = min(ans, get_dist(dist_from_a[c], dist_from_c[b]));
    ans = min(ans, get_dist(dist_from_b[a], dist_from_a[c]));
    cout << (ans == INF1 ? -1 : ans) << '\n';
}