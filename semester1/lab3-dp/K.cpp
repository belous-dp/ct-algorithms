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

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> w(n);
    for (int &i : w)
        cin >> i;
    vector<pii> dp(1 << n, { INF, INF });
    dp[0] = { 0, INF };
    vector<int> par(1 << n, -1);
    for (int mask = 0; mask < (1 << n); ++mask)
        for (int i = 0; i < n; ++i)
            if ((mask >> i) & 1) {
                pii p = dp[mask ^ (1 << i)];
                if (p.second + w[i] > s) {
                    p.first++;
                    p.second = w[i];
                } else {
                    p.second += w[i];
                }
                if (p < dp[mask]) {
                    dp[mask] = p;
                    par[mask] = mask ^ (1 << i);
                }
            }
    cout << dp[(1 << n) - 1].first << '\n';
    vector<vector<int>> ans;
    vector<int> v;
    for (int i = (1 << n) - 1; par[i] != -1; i = par[i]) {
        int cur = __builtin_ctz(i ^ par[i]);
        v.push_back(cur);
        if (dp[par[i]].second + w[cur] > s) {
            ans.push_back(v);
            v.clear();
        }
    }
    assert((int)ans.size() == dp[(1 << n) - 1].first);
    for (auto &i : ans) {
        cout << i.size() << ' ';
        for (int j : i)
            cout << j + 1 << ' ';
        cout << '\n';
    }
}