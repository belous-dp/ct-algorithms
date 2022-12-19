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
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 1; i < n - 1; ++i)
        cin >> v[i];
    vector<pii> dp(n, { -INF, -1 });
    dp[0].first = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = max(i - k, 0); j < i; ++j) {
            if (dp[i].first < dp[j].first + v[i]) {
                dp[i] = { dp[j].first + v[i], j };
            }
        }
    }
    cout << dp[n - 1].first << '\n';
    vector<int> ans = { n - 1 };
    for (int i = dp[n - 1].second; i != -1; i = dp[i].second)
        ans.push_back(i);
    cout << ans.size() - 1 << '\n';
    reverse(all(ans));
    for (int i : ans)
        cout << i + 1 << ' ';
    cout << '\n';
}