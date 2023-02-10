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

constexpr int MAXN = 4e5 + 7;
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
    int max, add, y;

    Node(int max = 0, int y = 0, int add = 0) : max(max), add(add), y(y) {}
};

Node tree[MAXN * 4];

Node merge(const Node &l, const Node &r) {
    Node res;
    if (l.max >= r.max)
        res = { l.max, l.y };
    else
        res = { r.max, r.y };
    return res;
}

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v].y = vl;
        return;
    }
    int mid = (vl + vr) / 2;
    build(v * 2, vl, mid);
    build(v * 2 + 1, mid, vr);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void push(int v, int vl, int vr) {
    if (vr - vl > 1) {
        tree[v * 2].max += tree[v].add;
        tree[v * 2].add += tree[v].add;
        tree[v * 2 + 1].max += tree[v].add;
        tree[v * 2 + 1].add += tree[v].add;
    }
    tree[v].add = 0;
}

void update(int v, int vl, int vr, int left, int right, int val) {
    if (right <= vl || vr <= left)
        return;
    if (left <= vl && vr <= right) {
        tree[v].max += val;
        tree[v].add += val;
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
        return {};
    if (left <= vl && vr <= right)
        return tree[v];
    push(v, vl, vr);
    int mid = (vl + vr) / 2;
    Node res = merge(get(v * 2, vl, mid, left, right),
                     get(v * 2 + 1, mid, vr, left, right));
    return res;
}

struct Event {
    int x, y1, y2, close;
    bool operator <(const Event &other) const {
        if (x != other.x)
            return x < other.x;
        return close < other.close;
    }
};

struct Point {
    int x, y, val;
};

constexpr int ZERO = MAXN / 2;

void solve() {
    int m;
    cin >> m;
    vector<Event> events;
    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y1 += ZERO;
        y2 += ZERO;
        events.push_back({ x1, y1, y2, -1 });
        events.push_back({ x2, y1, y2, 1 });
    }
    sort(all(events));
    build(1, 0, MAXN);
    Point ans = { 0, 0, -INF };
    for (int i = 0; i < m * 2; ++i) {
        update(1, 0, MAXN, events[i].y1, events[i].y2 + 1, -events[i].close);
//        if (events[i].close == -1 && events[i + 1].close == 1) {
            Node res = get(1, 0, MAXN, 0, MAXN);
            if (res.max > ans.val)
                ans = { events[i].x, res.y, res.max };
//        }
    }
    cout << ans.val << '\n' << ans.x << ' ' << ans.y - ZERO << '\n';
}