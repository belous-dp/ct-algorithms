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

int rnk[MAXN], par[MAXN], sum[MAXN];

pii find_set(int v) {
    if (v == par[v])
        return { v, sum[v] };
    pii res = find_set(par[v]);
    par[v] = res.first;
    sum[v] += res.second - sum[res.first];
    return { par[v], sum[v] + sum[res.first] };
}

void unite_sets(int a, int b) {
    a = find_set(a).first;
    b = find_set(b).first;
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        par[b] = a;
        sum[b] -= sum[a];
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}

void solve() {
    for (int i = 0; i < MAXN; ++i)
        par[i] = i;

    int n, m;
    cin >> n >> m;
    while (m--) {
        string t;
        cin >> t;
        if (t == "join") {
            int x, y;
            cin >> x >> y;
            unite_sets(x, y);
        } else if (t == "add") {
            int x, v;
            cin >> x >> v;
            x = find_set(x).first;
            sum[x] += v;
        } else {
            int x;
            cin >> x;
            cout << find_set(x).second << '\n';
        }
    }
}