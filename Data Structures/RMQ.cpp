#include<bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vi> st;
    vi log;
    SparseTable(const vi &a) {
        int n = a.size(), k = 32 - __builtin_clz(n);
        st.assign(k, vi(n)); log.assign(n+1, 0);
        forn(i, 2, n+1) log[i] = log[i/2] + 1;
        st[0] = a;
        forn(j, 1, k) forn(i, 0, n - (1<<j) + 1)
        st[j][i] = min(st[j-1][i], st[j-1][i + (1<<(j-1))]);
    }
    int query(int l, int r) {
        int j = log[r - l + 1];
        return min(st[j][l], st[j][r - (1<<j) + 1]);
    }
};