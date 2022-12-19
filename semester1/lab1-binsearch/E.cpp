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
    vector<int> v(n);
    for (int &i : v)
        cin >> i;
    sort(all(v));
    int k;
    cin >> k;
    while (k--) {
        int l, r;
        cin >> l >> r;
        if (v.back() < l || r < v[0]) {
            cout << "0 ";
            continue;
        }
        int left = -1, right = n - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (v[mid] >= l)
                right = mid;
            else
                left = mid;
        }
        if (v.back() < r) {
            cout << n - right << ' ';
            continue;
        }
        int tmp = right;
        left = 0, right = n;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (v[mid] > r)
                right = mid;
            else
                left = mid;
        }
        cout << right - tmp << ' ';
    }
}