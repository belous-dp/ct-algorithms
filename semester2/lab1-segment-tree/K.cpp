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

constexpr int MAXN = 1e6 + 7;
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
    int cnt, pref, suff, len, sum, push;

    Node(int len = 1, int cnt = 0, int pref = 0, int suff = 0, int sum = 0, int push = -1) : len(len), cnt(cnt),
                                                                                             pref(pref), suff(suff),
                                                                                             sum(sum), push(push)
                                                                                             {}
};

Node merge(const Node &a, const Node &b) {
    Node res = { a.len + b.len, a.cnt + b.cnt - (a.suff > 0 && b.pref > 0), a.pref, b.suff, a.sum + b.sum };
    if (a.pref == a.len)
        res.pref += b.pref;
    if (b.suff == b.len)
        res.suff += a.suff;
    return res;
}

Node tree[MAXN * 4];

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = {};
        return;
    }
    int mid = (vl + vr) / 2;
    build(v * 2, vl, mid);
    build(v * 2 + 1, mid, vr);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

Node init(int len, int val) {
    return { len, val, val * len, val * len, val * len, val };
}

void push(int v, int vl, int vr) {
    if (vr - vl > 1 && tree[v].push != -1) {
        int mid = (vl + vr) / 2;
        tree[v * 2] = init(mid - vl, tree[v].push);
        tree[v * 2 + 1] = init(vr - mid, tree[v].push);
    }
    tree[v].push = -1;
}

void update(int v, int vl, int vr, int left, int right, int val) {
    if (right <= vl || vr <= left)
        return;
    if (left <= vl && vr <= right) {
        tree[v] = init(vr - vl, val);
        return;
    }
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    update(v * 2, vl, mid, left, right, val);
    update(v * 2 + 1, mid, vr, left, right, val);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

Node get(int v, int vl, int vr, int left, int right) {
    if (vr <= left || right <= vl)
        return { 0 };
    if (left <= vl && vr <= right)
        return tree[v];
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    Node res = merge(get(v * 2, vl, mid, left, right),
                     get(v * 2 + 1, mid, vr, left, right));
    return res;
}

constexpr int ZERO = MAXN / 2;

void solve() {
    int m;
    cin >> m;
    int n = MAXN;
    build(1, 0, n);
    while (m--) {
        char t;
        cin >> t;
        bool v = t == 'B';
        int x, l;
        cin >> x >> l;
        x += ZERO;
        update(1, 0, n, x, x + l, v);
        Node res = get(1, 0, n, 0, n);
        cout << res.cnt << ' ' << res.sum << '\n';
    }
}