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

struct Heap {
private: 
    vector<int> heap = { -INF };
public:
    void push(int val) {
        int pos = heap.size();
        heap.push_back(val);
        while (pos > 1 && heap[pos / 2] < heap[pos]) {
            swap(heap[pos], heap[pos / 2]);
            pos /= 2;
        }
    }

    int pop() {
        int tmp = heap[1];
        swap(heap[1], heap.back());
        heap.pop_back();
        int pos = 1;
        while (pos * 2 < (int)heap.size() && heap[pos] < heap[pos * 2] ||
            pos * 2 + 1 < (int)heap.size() && heap[pos] < heap[pos * 2 + 1]) {
            if (pos * 2 + 1 == (int)heap.size() || heap[pos * 2] > heap[pos * 2 + 1]) {
                swap(heap[pos], heap[pos * 2]);
                pos *= 2;
            } else {
                swap(heap[pos], heap[pos * 2 + 1]);
                pos *= 2;
                pos += 1;
            }
        }
        return tmp;
    }
};

void solve() {
    int t;
    cin >> t;
    Heap heap;
    while (t--) {
        char c;
        cin >> c;
        if (c == '0') {
            int x;
            cin >> x;
            heap.push(x);
        } else {
            cout << heap.pop() << '\n';
        }

    }
}