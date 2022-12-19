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
    node* left;
    node* right;
    node() = default;
    node(int key) : key(key), priority(rnd()), left(nullptr), right(nullptr) { }
};
using pnode = node*;

void split(const pnode root, int key, pnode& left, pnode& right) {
    if (!root)
        left = right = nullptr;
    else if (root->key <= key) {
        split(root->right, key, root->right, right);
        left = root;
    } else {
        split(root->left, key, left, root->left);
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
        split(root, t->key, t->left, t->right);
        root = t;
    } else if (root->key < t->key) {
        insert(root->right, t);
    } else {
        insert(root->left, t);
    }
}

void erase(pnode& root, int key) {
    if (!root)
        return;
    if (root->key == key)
        root = merge(root->left, root->right);
    else
        erase(root->key > key ? root->left : root->right, key);
}

pnode next(const pnode root, int key) {
    if (!root)
        return nullptr;
    else if (root->key <= key)
        return next(root->right, key);
    pnode res = next(root->left, key);
    return res ? res : root;
}

pnode prev(const pnode root, int key) {
    if (!root)
        return nullptr;
    else if (root->key >= key)
        return prev(root->left, key);
    pnode res = prev(root->right, key);
    return res ? res : root;
}

void solve() {
    string s;
    pnode root = nullptr;
    while (cin >> s) {
        int key;
        cin >> key;
        if (s[0] == 'i') {
            insert(root, new node(key));
        } else if (s[0] == 'd') {
            erase(root, key);
        } else if (s[0] == 'e') {
            cout << (find(root, key) ? "true\n" : "false\n");
        } else if (s[0] == 'n') {
            pnode res = next(root, key);
            if (res)
                cout << res->key << "\n";
            else
                cout << "none\n";
        } else {
            pnode res = prev(root, key);
            if (res)
                cout << res->key << "\n";
            else
                cout << "none\n";
        }
    }
}