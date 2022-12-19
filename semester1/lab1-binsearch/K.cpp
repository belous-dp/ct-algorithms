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

bool check(ll sum, int n, int k, const vector<int> &v) {
    ll curSum = 0;
    int curPos = 0;
    for (int i = 0; i < k && curPos < n; ++i) {
        while (curPos < n && curSum + v[curPos] <= sum)
            curSum += v[curPos++];
        curSum = 0;
    }
    return curPos == n;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int &i : v)
        cin >> i;
    ll left = 0, right = INF1;
    while (left + 1 < right) {
        ll mid = (left + right) / 2;
        if (check(mid, n, k, v))
            right = mid;
        else
            left = mid;
    }
    cout << right << '\n';
}