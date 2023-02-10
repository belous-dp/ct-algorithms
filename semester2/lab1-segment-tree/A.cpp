#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define mp make_pair
#define all(x) (x).begin(), (x).end()
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q = 1;
    if (multi_test) cin >> q;
    while (q--) solve();
}

/*-------------------------------------------------------------------------------------------------------*/

int arr[MAXN];
ll tree[MAXN * 4];

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = arr[vl];
        return;
    }
    int mid = (vl + vr) / 2;
    build(v * 2, vl, mid);
    build(v * 2 + 1, mid, vr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

void update(int v, int vl, int vr, int id, int val) {
    if (id < vl || vr <= id)
        return;
    if (vr - vl == 1) {
        tree[v] = val;
        return;
    }
    int mid = (vl + vr) / 2;
    update(v * 2, vl, mid, id, val);
    update(v * 2 + 1, mid, vr, id, val);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

ll sum(int v, int vl, int vr, int left, int right) {
    if (vr <= left || right <= vl)
        return 0;
    if (left <= vl && vr <= right)
        return tree[v];
    int mid = (vl + vr) / 2;
    return sum(v * 2, vl, mid, left, right) + sum(v * 2 + 1, mid, vr, left, right);
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    build(1, 0, n);
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == '1') {
            int x, v;
            cin >> x >> v;
            update(1, 0, n, x, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << sum(1, 0, n, l, r) << '\n';
        }
    }
}