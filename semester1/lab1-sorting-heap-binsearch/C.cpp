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

ll merge_sort(vector<int> &v, int left, int right) {
    if (right - left == 1)
        return 0;
    int mid = (left + right) / 2;
    ll res = 0;
    res += merge_sort(v, left, mid);
    res += merge_sort(v, mid, right);
    vector<int> tmp;
    for (int p1 = left, p2 = mid; p1 < mid || p2 < right;) {
        if (p1 < mid && (p2 == right || v[p1] < v[p2])) {
            tmp.push_back(v[p1++]);
        } else {
            tmp.push_back(v[p2++]);
            if (p1 < mid)
                res += mid - p1;
        }
    }
    for (int i = left; i < right; ++i)
        v[i] = tmp[i - left];
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int &i : v)
        cin >> i;
    cout << merge_sort(v, 0, n);
    //for (int i : v)
        //cout << i << ' ';
}