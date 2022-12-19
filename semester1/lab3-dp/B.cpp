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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> v[i][j];
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -INF));
    dp[1][0] = 0;
    vector<vector<pii>> par(n + 1, vector<pii>(m + 1, { -1, -1 }));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j] + v[i][j];
                par[i][j] = { i - 1, j };
            } else {
                dp[i][j] = dp[i][j - 1] + v[i][j];
                par[i][j] = { i, j - 1 };
            }
        }
    }
    cout << dp[n][m] << '\n';
    string ans;
    for (pii i = { n, m }; par[i.first][i.second].first > 0; i = par[i.first][i.second]) {
        int dx = i.first - par[i.first][i.second].first;
        //int dy = i.second - par[i.first][i.second].second;
        ans += dx == 0 ? 'R' : 'D';
    }
    ans.pop_back();
    reverse(all(ans));
    cout << ans << '\n';
}