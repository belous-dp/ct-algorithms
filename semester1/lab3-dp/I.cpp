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

constexpr int MAXN = 12;
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

int mod(int a, int m) {
    if (a >= m)
        return a - m;
    return a;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> v(m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == 'X')
                v[j] ^= 1 << i;
        }
    v.push_back(0);

    vector<vector<int>> last(2 << n, vector<int>(n));
    last[0].assign(n, 1);
    for (int j = 0; j < m; ++j) {
        vector<vector<int>> next(2 << n, vector<int>(n));
        for (int i = 0; i < n - 1; ++i)
            for (int p = 0; p < (2 << n); ++p) {
                if (((p & (2 << i) - 1) & (v[j + 1] & (2 << i) - 1)) != (v[j + 1] & (2 << i) - 1) ||
                    ((p >> i + 1) & (v[j] >> i + 1)) != (v[j] >> i + 1))
                    continue;
                int cnt = 0;
                if (p & (2 << i)) {
                    cnt++;
                } else {
                    if (!(p & (1 << i)))
                        cnt++;
                    if (!(p & (1 << i + 2)))
                        cnt++;
                }
                next[p ^ (2 << i)][i + 1] += last[p][i] * cnt;
            }
        for (int p = 0; p < (2 << n); ++p) {
            if (((p & (2 << n - 1) - 1) & (v[j + 1] & (2 << n - 1) - 1)) != (v[j + 1] & (2 << n - 1) - 1) ||
                ((p >> n) & (v[j] >> n)) != (v[j] >> n))
                continue;
            int cnt = 0;
            if (p & (1 << n)) {
                next[(p ^ (1 << n)) << 1][0] += last[p][n - 1];
            } else {
                if (!(p & (1 << n - 1)))
                    next[(p ^ (1 << n - 1)) << 1][0] += last[p][n - 1];
            }
        }
        last = next;
    }
    cout << last[0][0] << '\n';
}