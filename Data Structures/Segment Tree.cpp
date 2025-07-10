#include<bits/stdc++.h>
using namespace std;

struct Node {
    int v;
    Node(int x = -1) : v(x) {}
};
Node merge(Node a, Node b) {
    return Node(max(a.v, b.v));
}
struct segtree {
    int n;
    vector<Node> t;
    segtree(int n): n(n), t(4*n) {}
    segtree(vector<int> &a): segtree(a.size()) { build(a); }
    void build(vector<int> &a, int v, int l, int r) {
        if (l == r) { t[v] = Node(a[l]); return; }
        int m = (l + r) >> 1;
        build(a, v*2, l, m); build(a, v*2+1, m+1, r);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
    Node query(int v, int l, int r, int ql, int qr) {
        if (ql > qr || l > qr || r < ql) return Node();
        int m = (l + r) >> 1;
        return merge(query(v*2, l, m, ql, min(qr, m)),
                    query(v*2+1, m+1, r, max(ql, m+1), qr));
    }
    void update(int v, int l, int r, int p, int val) {
        if (l == r) { t[v] = Node(val); return; }
        int m = (l + r) >> 1;
        (p <= m ? update(v*2, l, m, p, val)
                : update(v*2+1, m+1, r, p, val));
        t[v] = merge(t[v*2], t[v*2+1]);
    }
    void build(vector<int>& a) { build(a, 1, 0, n-1); }
    int query(int l, int r) { return query(1, 0, n-1, l, r).v; }
    void update(int p, int val) { update(1, 0, n-1, p, val); }
};