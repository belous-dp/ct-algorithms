#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define mp make_pair
#define all(x) x.begin(), x.end()
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
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q = 1;
    if (multi_test) cin >> q;
    while (q--) solve();
}

/*-------------------------------------------------------------------------------------------------------*/

struct Set {
    int rnk = 0, par = -1, mn = INF, mx = -INF, sz = 1;
} sets[MAXN];

int find_set(int v) {
    if (v == sets[v].par)
        return v;
    return sets[v].par = find_set(sets[v].par);
}

void unite_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sets[a].rnk < sets[b].rnk)
            swap(a, b);
        sets[b].par = a;
        sets[a].mn = min(sets[a].mn, sets[b].mn);
        sets[a].mx = max(sets[a].mx, sets[b].mx);
        sets[a].sz += sets[b].sz;
        if (sets[a].rnk == sets[b].rnk)
            sets[a].rnk++;
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i <= n; ++i)
        sets[i].par = sets[i].mn = sets[i].mx = i;
    string t;
    while (cin >> t) {
        if (t == "get") {
            int x;
            cin >> x;
            x = find_set(x);
            cout << sets[x].mn << ' ' << sets[x].mx << ' ' << sets[x].sz << '\n';
        } else {
            int a, b;
            cin >> a >> b;
            unite_sets(a, b);
        }
    }
}