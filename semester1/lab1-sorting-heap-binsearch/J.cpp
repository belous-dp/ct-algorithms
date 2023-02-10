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

int n, k;
vector<int> v, w;

bool check(ld x) {
    vector<ld> z;
    for (int i = 0; i < n; ++i)
        z.push_back(v[i] - x * w[i]);
    nth_element(z.begin(), z.begin() + (n - k), z.end());
    //sort(all(z));
    ld sum = 0;
    for (int i = n - 1; n - i - 1 < k; --i)
        sum += z[i];
    return sum >= 0;
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        v.push_back(a);
        w.push_back(b);
    }
    ld left = 0, right = INF;
    for (int i = 0; i < 100; ++i) {
        ld mid = (left + right) / 2;
        if (check(mid))
            left = mid;
        else
            right = mid;
    }
    vector<pair<ld, int>> z;
    for (int i = 0; i < n; ++i)
        z.push_back({ v[i] - left * w[i], i });
    nth_element(z.begin(), z.begin() + (n - k), z.end());
    //sort(all(z));
    for (int i = n - 1; n - i - 1 < k; --i)
        cout << z[i].second + 1 << ' ';
}