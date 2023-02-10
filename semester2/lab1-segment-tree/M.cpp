#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define multi_test 0

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

constexpr int MAXN = 130;
constexpr ll MOD = 1e9 + 7;
constexpr int INF = 1e9 + 5;
constexpr ll INF1 = 2e18;

void solve();

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q = 1;
    if (multi_test) cin >> q;
    while (q--) solve();
}

/*-------------------------------------------------------------------------------------------------------*/

int tree[MAXN][MAXN][MAXN];

void add(int x, int y, int z, int delta) {
    for (int i = x; i < MAXN; i |= i + 1)
        for (int j = y; j < MAXN; j |= j + 1)
            for (int k = z; k < MAXN; k |= k + 1)
                tree[i][j][k] += delta;
}

int sum(int x, int y, int z) {
    int res = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
                res += tree[i][j][k];
    return res;
}

int get(int x1, int y1, int z1, int x2, int y2, int z2) {
//    cout << "s1: " << sum(x2, y2, z2) << endl;
//    cout << "s2: " << -sum(x1 - 1, y2, z2) << endl;
//    cout << "s3: " << -sum(x2, y1 - 1, z2) << endl;
//    cout << "s4: " << sum(x1 - 1, y1 - 1, z2) << endl;
//    cout << "s5: " << -sum(x2, y2, z1 - 1) << endl;
//    cout << "s6: " << sum(x1 - 1, y2, z1 - 1) << endl;
//    cout << "s7: " << sum(x2, y1 - 1, z1 - 1) << endl;
//    cout << "s8: " << -sum(x1 - 1, y1 - 1, z1 - 1) << endl;
    return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) + sum(x1 - 1, y1 - 1, z2) -
           sum(x2, y2, z1 - 1) + sum(x1 - 1, y2, z1 - 1) + sum(x2, y1 - 1, z1 - 1) - sum(x1 - 1, y1 - 1, z1 - 1);
}

void solve() {
    int n;
    cin >> n;
    int t;
    cin >> t;
    while (t != 3) {
        if (t == 1) {
            int x, y, z, d;
            cin >> x >> y >> z >> d;
            add(x, y, z, d);
        } else {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << get(x1, y1, z1, x2, y2, z2) << '\n';
        }
        cin >> t;
    }
}