#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vi p, sz;
    DSU(int n) : p(n), sz(n,1) { iota(all(p), 0); }
    int find(int v) { return p[v] == v ? v : p[v] = find(p[v]); }
    void merge(int u, int v) {
        u = find(u); v = find(v); if (u == v) return;
        if (sz[u] > sz[v]) swap(u, v); p[u] = v; sz[v] += sz[u]; 
    }
    bool connected(int u, int v) { return find(u) == find(v); }
};