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

void dfs(int v, int col, vector<vector<int>> const& g, vector<int>& used, vector<int>& topsort) {
    used[v] = col;
    for (int u : g[v]) {
        if (used[u] == -1) {
            dfs(u, col, g, used, topsort);
        }
    }
    topsort.push_back(v);
}

void solve() {
    int n, m;
    cin >> n >> m;
    map<string, int> names;
    vector<string> inames(n);
    for (int i = 0; i < n; ++i) {
        cin >> inames[i];
        if (!names.count(inames[i])) {
            names[inames[i]] = names.size();
        }
    }
    vector<vector<int>> g(2 * n), revg(2 * n);
    while (m--) {
        string from, to;
        cin >> from >> to >> to;
        bool neg1 = from[0] == '-';
        bool neg2 = to[0] == '-';
        int a = names[from.substr(1)] * 2 + neg1;
        int b = names[to.substr(1)] * 2 + neg2;
        //cout << a << ' ' << b << endl;
        g[a].push_back(b);
        revg[b].push_back(a);
        a -= neg1;
        neg1 ^= 1;
        a += neg1;
        b -= neg2;
        neg2 ^= 1;
        b += neg2;
        //cout << a << ' ' << b << endl;
        g[b].push_back(a);
        revg[a].push_back(b);
    }
    vector<int> topsort, used(2 * n, -1);
    for (int i = 0; i < 2 * n; ++i) {
        if (used[i] == -1) {
            dfs(i, 1, g, used, topsort);
        }
    }
    reverse(all(topsort));
    used.assign(2 * n, -1);
    int ncomp = 0;
    vector<int> thrash;
    for (int i : topsort) {
        if (used[i] == -1) {
            dfs(i, ncomp++, revg, used, thrash);
        }
    }
    
    vector<vector<int>> cond(ncomp);
    for (int i = 0; i < 2 * n; ++i) {
        //cout << used[i] << '\n';
        for (int j : g[i]) {
            if (used[i] != used[j]) {
                cond[used[i]].push_back(used[j]);
            }
        }
        if (i % 2 == 0 && used[i] == used[i + 1]) {
            cout << "-1\n";
            return;
        }
       
    }
    vector<int> used2(ncomp, -1);
    topsort.clear();
    for (int i = 0; i < ncomp; ++i) {
        if (used2[i] == -1) {
            dfs(i, 1, cond, used2, topsort);
        }
    }
    reverse(all(topsort));
    vector<int> itopsort(ncomp);
    for (int i = 0; i < ncomp; ++i) {
        itopsort[topsort[i]] = i;
    }
    vector<string> ans;
    for (int i = 0; i < 2 * n; i += 2) {
        if (itopsort[used[i]] > itopsort[used[i + 1]]) {
            ans.push_back(inames[i / 2]);
        }
    }
    cout << ans.size() << '\n';
    for (auto s : ans) {
        cout << s << '\n';
    }
}
