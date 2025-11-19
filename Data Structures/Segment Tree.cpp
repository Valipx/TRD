/* --- MODIFICATION GUIDE ---
   To adapt this Segment Tree, you only need to change the 'Node' struct and 'merge' function.
   
   1. FOR SUM:
      - Node Constructor: Node(int x = 0) : v(x) {}  // Identity is 0
      - Merge: return Node(a.v + b.v);

   2. FOR MINIMUM:
      - Node Constructor: Node(int x = 2e18) : v(x) {} // Identity is Infinity
      - Merge: return Node(min(a.v, b.v));

   3. FOR MAXIMUM:
      - Node Constructor: Node(int x = -2e18) : v(x) {} // Identity is -Infinity
      - Merge: return Node(max(a.v, b.v));

   4. FOR XOR:
      - Node Constructor: Node(int x = 0) : v(x) {} // Identity is 0
      - Merge: return Node(a.v ^ b.v);

   5. FOR GCD:
      - Node Constructor: Node(int x = 0) : v(x) {} // Identity is 0 (gcd(x, 0) = x)
      - Merge: return Node(std::gcd(a.v, b.v));
*/
struct Node {
    int v;
    // DEFAULT: Using -1e18 for MAX queries (change this for other types)
    Node(int x = -1e18) : v(x) {} 
};

Node merge(Node a, Node b) {
    // DEFAULT: Max logic (change this for other types)
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
        // Returns Identity (Node()) if range is invalid
        if (ql > qr || l > qr || r < ql) return Node();
        if (ql <= l && r <= qr) return t[v];
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