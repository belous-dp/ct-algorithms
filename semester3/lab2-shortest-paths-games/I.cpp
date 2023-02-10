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
#define multi_test 1

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

void dfs(int v, vector<vector<int>> const& g, vector<bool>& used, vector<int>& lose_deg, vector<int>& state) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            if (state[v] == 0) { // lose
                state[u] = 2; // win
                dfs(u, g, used, lose_deg, state);
            } else if (state[v] == 2) { // win
                lose_deg[u]--;
                if (lose_deg[u] == 0) {
                    state[u] = 0; // lose
                    dfs(u, g, used, lose_deg, state);
                }
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), revg(n);
    vector<int> out_deg(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        revg[b - 1].push_back(a - 1);
        out_deg[a - 1]++;
    }
    vector<int> state(n, 1); // 0 -- lose, 1 -- draw, 2 -- win
    for (int i = 0; i < n; ++i) {
        if (g[i].empty()) {
            state[i] = 0;
        }
    }
    vector<bool> used(n);
    for (int i = 0; i < n; ++i) {
        if (!used[i] && g[i].empty()) {
            dfs(i, revg, used, out_deg, state);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (state[i] == 0) {
            cout << "SECOND\n";
        } else if (state[i] == 2) {
            cout << "FIRST\n";
        } else {
            cout << "DRAW\n";
        }
    }
    cout << '\n';
}