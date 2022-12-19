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
constexpr ll MOD = 1e9;
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

int add(int a, int b) {
    if (a + b >= MOD)
        return a + b - MOD;
    return a + b;
}

void solve() {
    vector<int> dp(10, 1);
    dp[0] = dp[8] = 0;
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        vector<int> next(10);
        int x;
        x = add(dp[4], dp[6]);
        next[0] = add(x, next[0]);

        x = add(dp[6], dp[8]);
        next[1] = add(x, next[1]);

        x = add(dp[7], dp[9]);
        next[2] = add(x, next[2]);

        x = add(dp[4], dp[8]);
        next[3] = add(x, next[3]);

        x = add(dp[3], dp[9]);
        x = add(x, dp[0]);
        next[4] = add(x, next[4]);

        x = add(dp[1], dp[7]);
        x = add(x, dp[0]);
        next[6] = add(x, next[6]);

        x = add(dp[2], dp[6]);
        next[7] = add(x, next[7]);

        x = add(dp[1], dp[3]);
        next[8] = add(x, next[8]);

        x = add(dp[2], dp[4]);
        next[9] = add(x, next[9]);

        dp = next;
    }

    int ans = 0;
    for (int i = 0; i < 10; ++i)
        ans = add(ans, dp[i]);
    cout << ans << '\n';
}