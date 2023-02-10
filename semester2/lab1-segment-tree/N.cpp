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

struct Node {
    constexpr static int NEUTRAL = 0;
    int sum;
    Node* left;
    Node* right;

    Node(int sum = NEUTRAL, Node* left = nullptr, Node* right = nullptr) : sum(sum), left(left), right(right) {}

    void build(int vl, int vr) {
        if (vr - vl == 1)
            return;
        int mid = (vl + vr) / 2;
//        assert(!left);
        left = new Node();
        left->build(vl, mid);
//        assert(!right);
        right = new Node();
        right->build(mid, vr);
    }

    Node* update(int vl, int vr, int id) {
        if (vr <= id || id < vl)
            return nullptr;
        if (vr - vl == 1)
            return new Node(sum + 1);
        int mid = (vl + vr) / 2;
        Node* pl = left->update(vl, mid, id);
        Node* pr = right ? right->update(mid, vr, id) : nullptr;
        int sl = pl ? pl->sum : left->sum; // sum in left subtree
        int sr = right ? right->sum : NEUTRAL; // sum in right subtree
        sr = pr ? pr->sum : sr;
        return new Node(sl + sr, pl ? pl : left, pr ? pr : right);
    }

};

int kth(Node* tl, Node* tr, int vl, int vr, int k) {
//    assert(tr->sum - tl->sum >= k);
    if (vr - vl == 1) {
//        assert(tr->left == nullptr);
        return vl;
    }
//    assert(tl->left != nullptr);
    int delta = tr->left->sum - tl->left->sum; // delta in left subtree
    int mid = (vl + vr) / 2;
    if (delta >= k) // then left subtree contains >= k elements in sorted order
        return kth(tl->left, tr->left, vl, mid, k);
    return kth(tl->right, tr->right, mid, vr, k - delta);
}

void solve() {
    int n;
    cin >> n;
    int l, m;
    vector<int> a(n);
    cin >> a[0] >> l >> m;
    for (int i = 1; i < n; ++i)
        a[i] = (a[i - 1] * 1LL * l + m) % MOD;
    vector<int> b = a;
    sort(all(b));
    b.resize(unique(all(b)) - b.begin());
    for (int& i : a)
        i = lower_bound(all(b), i) - b.begin();

    vector<Node*> trees(n + 1);
    trees[0] = new Node();
    trees[0]->build(0, n);
    for (int i = 0; i < n; ++i)
        trees[i + 1] = trees[i]->update(0, n, a[i]);

    int groups;
    cin >> groups;
    ll ans = 0;
    for (int g = 0; g < groups; ++g) {
        int q, x, lx, mx, y, ly, my, k, lk, mk;
        cin >> q >> x >> lx >> mx >> y >> ly >> my >> k >> lk >> mk;
        int i, j;
        for (int gg = 0; gg < q; ++gg) {
            if (gg > 0) {
                x = ((i - 1) * 1LL * lx + mx) % n + 1;
                y = ((j - 1) * 1LL * ly + my) % n + 1;
            }
            i = min(x, y);
            j = max(x, y);
            if (gg > 0)
                k = ((k - 1) * 1LL * lk + mk) % (j - i + 1) + 1;
            ans += b[kth(trees[i - 1], trees[j], 0, n, k)];
        }
    }
    cout << ans << '\n';
}