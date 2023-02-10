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
    int size;
    node* left;
    node* right;
    node(int key) : key(key), priority(rnd()), size(1), left(nullptr), right(nullptr) { }
};
using pnode = node*;

void split(pnode root, int key, pnode& left, pnode& right) {
    if (!root)
        left = right = nullptr;
    else if (root->key <= key) {
        split(root->right, key, root->right, right);
        root->size -= right ? right->size : 0;
        left = root;
    } else {
        split(root->left, key, left, root->left);
        root->size -= left ? left->size : 0;
        right = root;
    }

}

void upd_size(pnode t) {
    t->size = (t->left ? t->left->size : 0) + 1 + (t->right ? t->right->size : 0);
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

void insert(pnode& root, pnode t) {
    if (find(root, t->key))
        return;
    if (!root) {
        root = t;
    } else if (root->priority > t->priority) {
        t->size += root->size;
        split(root, t->key, t->left, t->right);
        root = t;
    } else {
        insert(root->key < t->key ? root->right : root->left, t);
        upd_size(root);
    }
}

void erase(pnode& root, int key) {
    if (!root)
        return;
    if (root->key == key) {
        root = merge(root->left, root->right);
    } else {
        erase(root->key > key ? root->left : root->right, key);
        upd_size(root);
    }
}

pnode kth(const pnode root, int k) {
    if (!root)
        return nullptr;
    int left_size = root->left ? root->left->size : 0;
    if (root->left && left_size >= k)
        return kth(root->left, k);
    else if (left_size + 1 == k)
        return root;
    else
        return kth(root->right, k - left_size - 1);
}

void solve() {
    int unused;
    cin >> unused;
    string s;
    pnode root = nullptr;
    while (cin >> s) {
        int key;
        cin >> key;
        if (s[0] == '1') {
            insert(root, new node(key));
        } else if (s[0] == '0') {
            cout << kth(root, root->size - key + 1)->key << '\n';
        } else {
            erase(root, key);
        }
    }
}