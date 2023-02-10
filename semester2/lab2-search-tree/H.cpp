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
    int val;
    int priority;
    int size;
    bool inverse;
    node* left;
    node* right;
    node(int val) : val(val), priority(rnd()), size(1), inverse(false), left(nullptr), right(nullptr) { }
};
using pnode = node*;

int get_size(pnode t) {
    return (t ? t->size : 0);
}

void upd_size(pnode t) {
    t->size = get_size(t->left) + 1 + get_size(t->right);
}

void inv(pnode t) {
    if (t)
        t->inverse ^= 1;
}

void push_inv(pnode t) {
    if (t && t->inverse) {
        swap(t->left, t->right);
        inv(t->left);
        inv(t->right);
        t->inverse = false;
    }
}

void split(pnode root, int key, pnode& left, pnode& right) {
    if (!root) {
        left = right = nullptr;
        return;
    }
    push_inv(root);
    int left_key = get_size(root->left);
    if (left_key + 1 <= key) {
        split(root->right, key - left_key - 1, root->right, right);
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
    pnode res = nullptr;
    push_inv(l);
    push_inv(r);
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

//pnode find_kth(const pnode root, int k) {
//    if (!root)
//        return nullptr;
//    int left_size = get_size(root->left);
//    if (root->left && left_size >= k)
//        return find_kth(root->left, k);
//    else if (left_size + 1 == k)
//        return root;
//    else
//        return find_kth(root->right, k - left_size - 1);
//}

void insert(pnode& root, int value, int pos) {
    pnode left = nullptr, right = nullptr;
    split(root, pos, left, right);
    left = merge(left, new node(value));
    root = merge(left, right);
}

void erase(pnode& root, int key) {
    if (!root)
        return;
    push_inv(root);
    int left_size = get_size(root->left);
    if (left_size + 1 == key) {
        root = merge(root->left, root->right);
    } else {
        if (left_size >= key)
            erase(root->left, key);
        else
            erase(root->right, key - left_size - 1);
        upd_size(root);
    }
}

void to_array(const pnode root, vector<int>& v) {
    if (!root)
        return;
    push_inv(root);
    to_array(root->left, v);
    v.push_back(root->val);
    to_array(root->right, v);
}

void print(const pnode root) {
    vector<int> res;
    to_array(root, res);
    //cout << res.size() << '\n';
    for (int i : res)
        cout << i << ' ';
    cout << '\n';
}

void solve() {
    int n, m;
    cin >> n >> m;
    pnode root = nullptr;
    for (int i = 0; i < n; ++i) {
        int v = i + 1;
        //cin >> v;
        insert(root, v, i + 1);
        //print(root);
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        pnode t1 = nullptr, t2 = nullptr;
        split(root, l - 1, t1, t2);
        pnode t3 = nullptr;
        if (t2)
            split(t2, r - get_size(t1), t2, t3);
        inv(t2);
        root = merge(t1, merge(t2, t3));
        //print(root);
    }
    print(root);
}