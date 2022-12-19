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
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    for (auto &i : v)
        for (auto &j : i)
            cin >> j;
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<pii>> par(1 << n, vector<pii>(n, { -1, -1 }));
    dp[0].assign(n, 0);
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                int from = i ^ (1 << j);
                for (int k = 0; k < n; ++k) {
                    int nval = dp[from][k] + (from == 0 ? 0 : v[k][j]);
                    if (nval < dp[i][j]) {
                        dp[i][j] = nval;
                        par[i][j] = { from, k };
                    }
                }
            }
        }
    }
    int best = 0;
    for (int i = 1; i < n; ++i)
        if (dp[(1 << n) - 1][i] < dp[(1 << n) - 1][best])
            best = i;
    cout << dp[(1 << n) - 1][best] << '\n';
    vector<int> ans;
    for (pii i = { (1 << n) - 1, best }; par[i.first][i.second].first != -1; i = par[i.first][i.second])
        ans.push_back(i.second + 1);
    reverse(all(ans));
    for (int i : ans)
        cout << i << ' ';
    cout << '\n';
}