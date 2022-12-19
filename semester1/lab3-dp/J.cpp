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

int n, m;

bool ok(int x) {
    for (int i = 0; i < n - 1; ++i)
        if (((x >> i) & 0x3) == 0x3)
            return false;
    return true;
}

void solve() {
    cin >> n >> m;
    if (n > m)
        swap(n, m);
    vector<int> last(1 << n, 1);
    for (int i = 1; i < m; ++i) {
        vector<int> cur(1 << n);
        for (int j = 0; j < (1 << n); ++j)
            for (int k = 0; k < (1 << n); ++k)
                if (ok(j & k) && ok(~j & ~k)) {
                    cur[j] += last[k];
                }
        last = cur;
    }
    int sum = 0;
    for (int i : last)
        sum += i;
    cout << sum << '\n';
}