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
    string a, b;
    cin >> a >> b;
    a = ' ' + a;
    b = ' ' + b;
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n, vector<int>(m, INF));
    dp[0][0] = 0;
    for (int i = 1; i < n; ++i)
        dp[i][0] = i;
    for (int j = 1; j < m; ++j)
        dp[0][j] = j;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j) {
            int x = a[i] != b[j];
            dp[i][j] = dp[i - 1][j - 1] + x;
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
        }
    cout << dp[n - 1][m - 1] << '\n';
}