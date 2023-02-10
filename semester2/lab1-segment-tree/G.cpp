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
    int min, val;

    Node(int min = INF, int val = -1) : min(min), val(val) {}
};

Node merge(const Node &a, const Node &b) {
    return { min(a.min, b.min) };
}

Node init(int val) {
    return { val };
}

int arr[MAXN];
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

void push(int v, int vl, int vr) {
    if (vr - vl > 1 && tree[v].val != -1) {
        tree[v * 2].min = tree[v].val;
        tree[v * 2].val = tree[v].val;
        tree[v * 2 + 1].min = tree[v].val;
        tree[v * 2 + 1].val = tree[v].val;
    }
    tree[v].val = -1;
}

void update(int v, int vl, int vr, int left, int right, int val) {
    if (right <= vl || vr <= left)
        return;
    if (left <= vl && vr <= right) {
        tree[v].min = val;
        tree[v].val = val;
        return;
    }
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    update(v * 2, vl, mid, left, right, val);
    update(v * 2 + 1, mid, vr, left, right, val);
    tree[v].min = min(tree[v * 2].min, tree[v * 2 + 1].min);
}

int get(int v, int vl, int vr, int left, int right) {
    if (vr <= left || right <= vl)
        return INF;
    if (left <= vl && vr <= right)
        return tree[v].min;
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    int res = min(get(v * 2, vl, mid, left, right),
                 get(v * 2 + 1, mid, vr, left, right));
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    build(1, 0, n);
    while (m--) {
        char t;
        cin >> t;
        if (t == '1') {
            int l, r, v;
            cin >> l >> r >> v;
            update(1, 0, n, l, r, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << get(1, 0, n, l, r) << '\n';
        }
    }
}