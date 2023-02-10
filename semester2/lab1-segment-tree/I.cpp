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
#include <array>

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

int r;

struct Matrix {
    int m11, m12, m21, m22;

    Matrix(int m11 = 1, int m12 = 0, int m21 = 0, int m22 = 1) : m11(m11), m12(m12), m21(m21), m22(m22) {}

    Matrix(const array<int, 4> &arr) : m11(arr[0]), m12(arr[1]), m21(arr[2]), m22(arr[3]) {}

    Matrix mult(const Matrix &other) const {
        return { (m11 * other.m11 + m12 * other.m21) % r,
                 (m11 * other.m12 + m12 * other.m22) % r,
                 (m21 * other.m11 + m22 * other.m21) % r,
                 (m21 * other.m12 + m22 * other.m22) % r };
    }
};

array<int, 4> arr[MAXN];
Matrix tree[MAXN * 4];

void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
        tree[v] = { arr[vl] };
        return;
    }
    int mid = (vl + vr) / 2;
    build(v * 2, vl, mid);
    build(v * 2 + 1, mid, vr);
    tree[v] = tree[v * 2].mult(tree[v * 2 + 1]);
}

Matrix get(int v, int vl, int vr, int left, int right) {
    if (vr <= left || right <= vl)
        return {};
    if (left <= vl && vr <= right)
        return tree[v];
    int mid = (vl + vr) / 2;
    Matrix res = get(v * 2, vl, mid, left, right).mult(
                       get(v * 2 + 1, mid, vr, left, right));
    return res;
}

void solve() {
    int n, m;
    cin >> r >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int &j : arr[i])
            cin >> j;
    build(1, 0, n);
    while (m--) {
        int l, r;
        cin >> l >> r;
        Matrix res = get(1, 0, n, l - 1, r);
        cout << res.m11 << ' ' << res.m12 << '\n';
        cout << res.m21 << ' ' << res.m22 << '\n';
        cout << '\n';
    }
}