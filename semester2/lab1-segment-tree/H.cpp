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
    ll sum, val, add;

    Node(ll sum = 0, ll val = -1, ll add = 0) : sum(sum), val(val), add(add) {}
};

Node tree[MAXN * 4];

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = {};
        return;
    }
    int mid = (vl + vr) / 2;
    build(v * 2, vl, mid);
    build(v * 2 + 1, mid, vr);
}

void push(int v, int vl, int vr) {
    if (vr - vl > 1) {
        int mid = (vl + vr) / 2;
        if (tree[v].val != -1) {
//            assert(tree[v].add == 0);
            tree[v * 2].sum = tree[v].val * (mid - vl);
            tree[v * 2].val = tree[v].val;
            tree[v * 2].add = 0;
            tree[v * 2 + 1].sum = tree[v].val * (vr - mid);
            tree[v * 2 + 1].val = tree[v].val;
            tree[v * 2 + 1].add = 0;
            tree[v].val = -1;
        }
        tree[v * 2].sum += tree[v].add * (mid - vl);
        tree[v * 2].add += tree[v].add;
        tree[v * 2 + 1].sum += tree[v].add * (vr - mid);
        tree[v * 2 + 1].add += tree[v].add;
        tree[v].add = 0;
    }
}

void assign(int v, int vl, int vr, int left, int right, int val) {
    if (right <= vl || vr <= left)
        return;
    if (left <= vl && vr <= right) {
        tree[v] = { (ll)val * (vr - vl), val, 0 };
        return;
    }
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    assign(v * 2, vl, mid, left, right, val);
    assign(v * 2 + 1, mid, vr, left, right, val);
    tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
}

void add(int v, int vl, int vr, int left, int right, int val) {
    if (right <= vl || vr <= left) {
        return;
    }
    push(v, vl, vr);
    if (left <= vl && vr <= right) {
        tree[v].sum += (ll)val * (vr - vl);
        tree[v].add += val;
        return;
    }
    int mid = (vl + vr) / 2;
    add(v * 2, vl, mid, left, right, val);
    add(v * 2 + 1, mid, vr, left, right, val);
    tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
}

ll get(int v, int vl, int vr, int left, int right) {
    if (vr <= left || right <= vl)
        return 0;
    if (left <= vl && vr <= right)
        return tree[v].sum;
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    ll res = get(v * 2, vl, mid, left, right) +
            get(v * 2 + 1, mid, vr, left, right);
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
            assign(1, 0, n, l, r, v);
        } else if (t == '2') {
            int l, r, v;
            cin >> l >> r >> v;
            add(1, 0, n, l, r, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << get(1, 0, n, l, r) << '\n';
        }
    }
}