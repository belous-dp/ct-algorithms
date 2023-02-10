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
constexpr ll MOD = 1e9;
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

const ll NEUTRAL = 0;

struct Node {
    ll sum;
    Node * left, * right;
    Node(ll sum_ = NEUTRAL, Node * left_ = nullptr, Node * right_ = nullptr) :
            sum(sum_), left(left_), right(right_) {
    }
    void build(int v, int vl, int vr) {
        if (vr - vl == 1) {
            sum = NEUTRAL;
            return;
        }
        int mid = (vl + vr) / 2;
        if (!left)
            left = new Node();
        left->build(v * 2, vl, mid);
        if (!right)
            right = new Node();
        right->build(v * 2 + 1, mid, vr);
        sum = left->sum + right->sum;
    }
    Node * update(int v, int vl, int vr, int id) {
        if (vr <= id || id < vl)
            return nullptr;
        if (vr - vl == 1)
            return new Node(sum + 1);
        int mid = (vl + vr) / 2;
        Node * pl = left ? left->update(v * 2, vl, mid, id) : nullptr;
        Node * pr = right ? right->update(v * 2 + 1, mid, vr, id) : nullptr;
        ll sl = NEUTRAL, sr = NEUTRAL;
        if (pl)
            sl = pl->sum;
        else if (left)
            sl = left->sum;
        if (pr)
            sr = pr->sum;
        else if (right)
            sr = right->sum;
        return new Node(sl + sr, pl ? pl : left, pr ? pr : right);
    }
};

int kth(Node * tl, Node * tr, int vl, int vr, int k) {
    if (vr - vl == 1)
        return vl;
    int delta = NEUTRAL;
    if (tl->left)
        delta = tr->left->sum - tl->left->sum;
    if (delta >= k)
        return kth(tl->left, tr->left, vl, (vl + vr) / 2, k);
    return kth(tl->right, tr->right, (vl + vr) / 2, vr, k - delta);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int l, m;
    cin >> a[0] >> l >> m;
    for (int i = 1; i < n; ++i)
        a[i] = (a[i - 1] * 1LL * l + m) % MOD;
    vector<int> b = a;
    sort(all(b));
    b.resize(unique(all(b)) - b.begin());
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(all(b), a[i]) - b.begin();
    vector<Node *> trees(n + 1);
    trees[0] = new Node();
    trees[0]->build(1, 0, n);
    for (int i = 1; i <= n; ++i)
        trees[i] = trees[i - 1]->update(1, 0, n, a[i - 1]);
    int numGroup;
    cin >> numGroup;
    ll ans = 0;
    for (int ng = 0; ng < numGroup; ++ng) {
        int q, x, lx, mx, y, ly, my, k, lk, mk;
        cin >> q >> x >> lx >> mx >> y >> ly >> my >> k >> lk >> mk;
        int i, j;
        for (int qq = 1; qq <= q; ++qq) {
            if (qq > 1) {
                x = ((i - 1) * 1LL * lx + mx) % n + 1;
                y = ((j - 1) * 1LL * ly + my) % n + 1;
            }
            i = min(x, y);
            j = max(x, y);
            if (qq > 1)
                k = ((k - 1) * 1LL * lk + mk) % (j - i + 1) + 1;
            ans += b[kth(trees[i - 1], trees[j], 0, n, k)];
        }
    }
    cout << ans;
}