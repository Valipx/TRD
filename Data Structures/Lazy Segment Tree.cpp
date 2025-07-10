#include<bits/stdc++.h>
using namespace std;

struct Node {
    int v;
    Node(int x = -1) : v(x) {}
};
Node merge(Node a, Node b) {
    return Node(max(a.v, b.v));
}
struct LazySeg {
    int n;
    vector<Node> t;
    vector<int> lazy;
    LazySeg(int n): n(n), t(4*n), lazy(4*n, 0) {}
    LazySeg(vector<int> &a): LazySeg(a.size()) { build(a); }
    void push(int v, int l, int r) {
        if (lazy[v] == 0) return;
        t[v].v += lazy[v];
        if (l != r) {
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }
        lazy[v] = 0;
    }
    void build(vector<int> &a, int v, int l, int r) {
        if (l == r) { t[v] = Node(a[l]); return; }
        int m = (l + r) >> 1;
        build(a, v*2, l, m); build(a, v*2+1, m+1, r);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
    void upd(int v, int l, int r, int ql, int qr, int val) {
        push(v, l, r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            lazy[v] += val;
            push(v, l, r);
            return;
        }
        int m = (l + r) >> 1;
        upd(v*2, l, m, ql, qr, val);
        upd(v*2+1, m+1, r, ql, qr, val);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
    Node qry(int v, int l, int r, int ql, int qr) {
        push(v, l, r);
        if (qr < l || r < ql) return Node();
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) >> 1;
        return merge(qry(v*2, l, m, ql, qr),
                     qry(v*2+1, m+1, r, ql, qr));
    }
    void build(vector<int>& a) { build(a, 1, 0, n-1); }
    void update(int l, int r, int val) { upd(1, 0, n-1, l, r, val); }
    int query(int l, int r) { return qry(1, 0, n-1, l, r).v; }
};