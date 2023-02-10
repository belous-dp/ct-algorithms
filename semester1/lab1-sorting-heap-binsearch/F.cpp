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
    vector<ll> v(n);
    for (ll &i : v)
        cin >> i;
    //sort(all(v));
    while (k--) {
        ll x;
        cin >> x;
        int left = 0, right = n - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (x < v[mid])
                right = mid;
            else
                left = mid;
        }
        if (abs(v[left] - x) <= abs(v[right] - x))
            cout << v[left] << '\n';
        else
            cout << v[right] << '\n';
    }
}