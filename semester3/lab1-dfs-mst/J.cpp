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

int par[MAXN], rnk[MAXN];

int get_set(int x) {
    if (par[x] == x) {
        return x;
    }
    return par[x] = get_set(par[x]);
}

void unite_sets(int a, int b) {
    a = get_set(a);
    b = get_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b]) {
            swap(a, b);
        }
        par[b] = a;
        if (rnk[a] == rnk[b]) {
            ++rnk[a];
        }
    }
}

struct edge {
    int a, b, w;
    friend bool operator <(edge const& lhs, edge const& rhs) {
        return lhs.w < rhs.w;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({ a - 1, b - 1, w });
    }
    for (int i = 0; i < n; ++i) {
        par[i] = i;
    }
    sort(all(edges));
    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        edge const& e = edges[i];
        if (get_set(e.a) != get_set(e.b)) {
            unite_sets(e.a, e.b);
            ans += e.w;
        }
    }
    cout << ans << '\n';
}