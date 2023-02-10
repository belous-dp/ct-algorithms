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

int vp, vf;
ld a;

ld f(ld x) {
    return sqrtl((1. - a) * (1. - a) + x * x) * vp +
        sqrtl(a * a + (1. - x) * (1. - x)) * vf;
}

void solve() {
    cin >> vf >> vp >> a;
    ld left = 0, right = 1;
    for (int i = 0; i < 100; ++i) {
        ld m1 = left + (right - left) / 3;
        ld m2 = right - (right - left) / 3;
        if (f(m1) < f(m2))
            right = m2;
        else
            left = m1;
    }
    cout << fixed << setprecision(5) << left << '\n';
}