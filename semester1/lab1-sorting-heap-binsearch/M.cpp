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

int n;
ll k;
vector<int> a, b;

ll cnt(ll x) {
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        int left = 0, right = n;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (b[mid] > x - a[i])
                right = mid;
            else
                left = mid;
        }
        if (b[left] <= x - a[i])
            left++;
        res += left;
    }
    return res;
}

void solve() {
    cin >> n >> k;
    a.resize(n);
    for (int &i : a)
        cin >> i;
    sort(all(a));
    b.resize(n);
    for (int &i : b)
        cin >> i;
    sort(all(b));
    ll left = 0, right = INF1;
    while (left + 1 < right) {
        ll mid = (left + right) / 2;
        if (cnt(mid) >= k)
            right = mid;
        else
            left = mid;
    }
    cout << right << '\n';
}