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

constexpr int MAXN = 3e5 + 7;
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

struct Node {
    int cnt;

    Node(int cnt = 0) : cnt(cnt) {}
};

Node merge(const Node &a, const Node &b) {
    return { a.cnt + b.cnt };
}

Node init(bool val) {
    return { val };
}

bool arr[MAXN];
Node tree[MAXN * 4];

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = init(arr[vl]);
        return;
    }
    int mid = (vl + vr) / 2;
    build(v * 2, vl, mid);
    build(v * 2 + 1, mid, vr);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void update(int v, int vl, int vr, int id) {
    if (id < vl || vr <= id)
        return;
    if (vr - vl == 1) {
        tree[v] = init(!tree[v].cnt);
        return;
    }
    int mid = (vl + vr) / 2;
    update(v * 2, vl, mid, id);
    update(v * 2 + 1, mid, vr, id);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

int get(int v, int vl, int vr, int k) {
    if (vr - vl == 1)
        return vl;
    int mid = (vl + vr) / 2;
    if (tree[v * 2].cnt >= k)
        return get(v * 2, vl, mid, k);
    return get(v * 2 + 1, mid, vr, k - tree[v * 2].cnt);
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    build(1, 0, n);
    while (m--) {
        char t;
        cin >> t;
        if (t == '1') {
            int x;
            cin >> x;
            update(1, 0, n, x);
        } else {
            int k;
            cin >> k;
            cout << get(1, 0, n, k + 1) << '\n';
        }
    }
}