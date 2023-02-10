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

mt19937 rnd(42);

struct node {
    int key, priority;
    int val;
    int size, add;
    node* left;
    node* right;
    node(int key, int val) :
        key(key), priority(rnd()),
        val(val), size(1), add(0),
        left(nullptr), right(nullptr) { }
};
using pnode = node*;

int get_size(pnode t) {
    return (t ? t->size : 0);
}

void upd_size(pnode t) {
    t->size = get_size(t->left) + 1 + get_size(t->right);
}

void add(pnode t, int add) {
    if (t) {
        t->key += add;
        t->add += add;
    }
}

void push_add(pnode t) {
    if (t && t->add) {
        add(t->left, t->add);
        add(t->right, t->add);
        t->add = 0;
    }
}

void split(const pnode root, int key, pnode& left, pnode& right) {
    if (!root) {
        left = right = nullptr;
        return;
    }
    push_add(root);
    if (root->key <= key) {
        split(root->right, key, root->right, right);
        left = root;
    } else {
        split(root->left, key, left, root->left);
        right = root;
    }
    upd_size(root);
}

pnode merge(const pnode l, const pnode r) {
    if (!l || !r)
        return l ? l : r;
    push_add(l);
    push_add(r);
    pnode res = nullptr;
    if (l->priority > r->priority) {
        res = l;
        res->right = merge(res->right, r);
    } else {
        res = r;
        res->left = merge(l, res->left);
    }
    upd_size(res);
    return res;
}

pnode find(const pnode root, int key) {
    if (!root)
        return nullptr;
    else if (root->key == key)
        return root;
    return find(root->key > key ? root->left : root->right, key);
}

int find_continuous(const pnode root, int start_key) {
    if (!root)
        return 0;
    push_add(root);
    if (get_size(root->left) + start_key == root->key) {
        return root->key - start_key + 1 +
            find_continuous(root->right, root->key + 1);
    } else {
        return find_continuous(root->left, start_key);
    }
}

void insert(pnode& root, pnode t) {
    pnode left = nullptr, right = nullptr;
    split(root, t->key - 1, left, right);
    left = merge(left, t);
    int cont = find_continuous(right, t->key);
    pnode mid = nullptr;
    split(right, t->key + cont, mid, right);
    // merge(left, t, mid', right)
    add(mid, 1);
    root = merge(left, merge(mid, right));
}

void to_array(const pnode root, vector<pii>& v) {
    if (!root)
        return;
    push_add(root);
    to_array(root->left, v);
    v.push_back({ root->key, root->val });
    to_array(root->right, v);
}

void print(const pnode root) {
    vector<pii> res;
    to_array(root, res);
    cout << res.back().first << '\n';
    for (int i = 1, j = 0; i <= res.back().first; ++i)
        cout << (res[j].first == i ? res[j++].second : 0) << ' ';
    cout << '\n';
}

void solve() {
    int n, m;
    cin >> n >> m;
    pnode root = nullptr;
    for (int i = 1; i <= n; ++i) {
        int pos;
        cin >> pos;
        insert(root, new node(pos, i));
        //print(root);
    }
    print(root);
}