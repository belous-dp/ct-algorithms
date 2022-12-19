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

string best(string a, string b) {
    return (a.size() > b.size() ? a : b);
}

void solve() {
    map<char, char> open = { {')', '('}, {']', '['}, {'}', '{'} };
    string s;
    cin >> s;
    s = '\0' + s;
    int n = s.size();
    vector<vector<string>> dp(n, vector<string>(n));
    for (int r = 1; r < n; ++r) {
        for (int l = r - 1; l >= 1; --l) {
            if (s[l] == open[s[r]]) {
                dp[l][r] = best(dp[l][r], s[l] + dp[l + 1][r - 1] + s[r]);
            }
            for (int k = l + 1; k < r; ++k) {
                if (s[k] == open[s[r]] && k + 1 <= r - 1) {
                    dp[l][r] = best(dp[l][r], dp[l][k - 1] + s[k] + dp[k + 1][r - 1] + s[r]);
                }
                //dp[l][r] = best(dp[l][r], dp[l][k]);
                //dp[l][r] = best(dp[l][r], dp[k][r]);
                //dp[l][r] = best(dp[l][r], dp[l][k - 1] + dp[k + 1][r]);
                dp[l][r] = best(dp[l][r], dp[l][k] + dp[k + 1][r]);
                dp[l][r] = best(dp[l][r], dp[l][k - 1] + dp[k][r]);
            }
        }
    }
    cout << dp[1][n - 1] << '\n';
}