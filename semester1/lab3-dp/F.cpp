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
    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> v[i];
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
    vector<vector<pii>> par(n + 1, vector<pii>(n + 1, { -1, -1 }));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (v[i] > 100 && j > 0 && dp[i - 1][j - 1] + v[i] < dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + v[i];
                par[i][j] = { i - 1, j - 1 };
            } else if (v[i] <= 100 && dp[i - 1][j] + v[i] < dp[i][j]) {
                dp[i][j] = dp[i - 1][j] + v[i];
                par[i][j] = { i - 1, j };
            }
            if (j + 1 <= n && dp[i - 1][j + 1] < dp[i][j]) {
                dp[i][j] = dp[i - 1][j + 1];
                par[i][j] = { i - 1, j + 1 };
            }
        }
    }
    int best = 0;
    for (int i = 0; i <= n; ++i)
        if (dp[n][i] <= dp[n][best])
            best = i;
    cout << dp[n][best] << '\n' << best << ' ';
    vector<int> ans;
    for (pii i = { n, best }; par[i.first][i.second].first != -1; i = par[i.first][i.second])
        if (i.second < par[i.first][i.second].second)
            ans.push_back(i.first);
    cout << ans.size() << '\n';
    reverse(all(ans));
    for (int &i : ans)
        cout << i << ' ';
    cout << '\n';
}