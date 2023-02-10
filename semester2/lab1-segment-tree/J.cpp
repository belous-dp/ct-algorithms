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

struct Node {
    int min;

    Node(int min = INF) : min(min) {}
};

Node tree[MAXN * 4];

void update(int v, int vl, int vr, int id, int val) {
    if (id < vl || vr <= id)
        return;
    if (vr - vl == 1) {
        tree[v].min = val;
        return;
    }
    int mid = (vl + vr) / 2;
    update(v * 2, vl, mid, id, val);
    update(v * 2 + 1, mid, vr, id, val);
    tree[v].min = min(tree[v * 2].min, tree[v * 2 + 1].min);
}

int get(int v, int vl, int vr, int left, int right, int val) {
    if (vr <= left || right <= vl)
        return 0;
    if (vr - vl == 1) {
        bool res = tree[v].min <= val;
        if (res)
            tree[v] = {};
        return res;
    }
    int mid = (vl + vr) / 2;
    int res = 0;
    if (tree[v * 2].min <= val)
        res += get(v * 2, vl, mid, left, right, val);
    if (tree[v * 2 + 1].min <= val)
        res += get(v * 2 + 1, mid, vr, left, right, val);
    tree[v].min = min(tree[v * 2].min, tree[v * 2 + 1].min);
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        char t;
        cin >> t;
        if (t == '1') {
            int x, v;
            cin >> x >> v;
            update(1, 0, n, x, v);
        } else {
            int l, r, p;
            cin >> l >> r >> p;
            cout << get(1, 0, n, l, r, p) << '\n';
        }
    }
}