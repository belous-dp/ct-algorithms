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
    vector<int> v, ans, check;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        while (!v.empty() && v.back() < x) {
            check.push_back(v.back());
            v.pop_back();
            ans.push_back(0);
        }
        v.push_back(x);
        ans.push_back(1);
    }
    while (!v.empty()) {
        check.push_back(v.back());
        v.pop_back();
        ans.push_back(0);
    }
    for (int i = 1; i < n; ++i)
        if (check[i - 1] > check[i]) {
            cout << "impossible";
            return;
        }
    for (int i : ans)
        cout << (i ? "push\n" : "pop\n");
}