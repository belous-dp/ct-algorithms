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
#define all(x) (x).begin(), (x).end()
#define multi_test 0

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

constexpr int MAXN = 3e5 + 7;
constexpr ll MOD = 1e9;
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

mt19937 rnd(42);

struct node {
    int key, priority;
    ll sum;
    node* left;
    node* right;
    node() = default;
    node(int key) : key(key), priority(rnd()), sum(key), left(nullptr), right(nullptr) { }
};
using pnode = node*;

void split(pnode root, int key, pnode& left, pnode& right) {
    if (!root)
        left = right = nullptr;
    else if (root->key <= key) {
        split(root->right, key, root->right, right);
        root->sum -= right ? right->sum : 0;
        left = root;
    } else {
        split(root->left, key, left, root->left);
        root->sum -= left ? left->sum : 0;
        right = root;
    }

}

pnode merge(const pnode l, const pnode r) {
    if (!l || !r)
        return l ? l : r;
    pnode res = nullptr;
    if (l->priority > r->priority) {
        res = l;
        res->right = merge(res->right, r);
    } else {
        res = r;
        res->left = merge(l, res->left);
    }
    res->sum = (res->left ? res->left->sum : 0) + res->key + (res->right ? res->right->sum : 0);
    return res;
}

pnode find(const pnode root, int key) {
    if (!root)
        return nullptr;
    else if (root->key == key)
        return root;
    return find(root->key > key ? root->left : root->right, key);
}

void insert(pnode& root, pnode t) {
    if (find(root, t->key))
        return;
    if (!root) {
        root = t;
    } else if (root->priority > t->priority) {
        t->sum += root->sum;
        split(root, t->key, t->left, t->right);
        root = t;
    } else if (root->key < t->key) {
        insert(root->right, t);
        root->sum = (root->left ? root->left->sum : 0) + root->key + (root->right ? root->right->sum : 0);
    } else {
        insert(root->left, t);
        root->sum = (root->left ? root->left->sum : 0) + root->key + (root->right ? root->right->sum : 0);
    }
}

ll sum(pnode& root, int from, int to) {
    if (!root)
        return 0;
    pnode l = nullptr, m = nullptr;
    split(root, from - 1, l, m);
    pnode r = nullptr;
    if (m)
        split(m, to, m, r);
    ll res = m ? m->sum : 0;
    root = merge(l, m);
    root = merge(root, r);
    return res;
}

void solve() {
    int unused;
    cin >> unused;
    string s;
    ll last_res = 0;
    pnode root = nullptr;
    while (cin >> s) {
        if (s[0] == '+') {
            int key;
            cin >> key;
            insert(root, new node((key + last_res) % MOD));
            last_res = 0;
        } else {
            int l, r;
            cin >> l >> r;
            last_res = sum(root, l, r);
            cout << last_res << '\n';
        }
    }
}