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
constexpr ld EPS = 1e-8;

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

struct point {
    int x, y;
};

double dist(point const& a, point const& b) {
    return sqrtl((a.x - b.x) * (a.x - b.x) +
                 (a.y - b.y) * (a.y - b.y));
}

int cmp(double a, double b) {
    if (fabsl(a - b) < EPS) {
        return 0;
    }
    return a < b ? -1 : 1;
}

void solve() {
    int n;
    cin >> n;
    vector<point> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }
    vector<double> dist_to_mst(n);
    for (int j = 0; j < n; ++j) {
        double new_dist = dist(pts[j], pts[0]);
        dist_to_mst[j] = new_dist;
    }
    dist_to_mst[0] = -1;
    double ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        double best_dist = INF;
        int best_id = 0;
        for (int j = 0; j < n; ++j) {
            if (cmp(dist_to_mst[j], -1) != 0 && cmp(dist_to_mst[j], best_dist) < 0) {
                best_dist = dist_to_mst[j];
                best_id = j;
            }
        }
        ans += best_dist;
        dist_to_mst[best_id] = -1;
        for (int j = 0; j < n; ++j) {
            double new_dist = dist(pts[j], pts[best_id]);
            if (cmp(dist_to_mst[j], -1) != 0 && cmp(new_dist, dist_to_mst[j]) < 0) {
                dist_to_mst[j] = new_dist;
            }
        }
    }
    cout << fixed << setprecision(8) << ans << '\n';
}