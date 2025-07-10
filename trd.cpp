//Template 
#include<bits/stdc++.h>
using namespace std;

#define forn(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define vi vector<int>
#define pii pair<int,int>
#define int long long
#define sz(a) (int)a.size()
// int32_t main(){
//         ios_base::sync_with_stdio(false);
//         cin.tie(NULL);
//         cout.tie(NULL);
// }

//Data structures

//DSU
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

//SegmentTree(set to Max default)
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

//LazySegmentTree(uses same node and merge as normal seg)
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

//RMQ Sparse Table
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

//Fenwick
template <class T> struct BIT {
	int n;
	vector<T> b, a;
	BIT(int n) : n(n), b(n+1), a(n) {}
	BIT(vector<T>& v) : BIT(v.size()) {
		for (int i = 0; i < n; ++i) add(i, v[i]);
	}
	void add(int i, T v) {
		a[i] += v;
		for (++i; i <= n; i += i & -i) b[i] += v;
	}
	void set(int i, T v) { add(i, v - a[i]); }
	T sum(int i) {
		T r = 0;
		for (++i; i; i -= i & -i) r += b[i];
		return r;
	}
	T sum(int l, int r) { return sum(r) - (l ? sum(l - 1) : 0); }
	int lower_bound(T x) {
		int i = 0;
		for (int k = 1 << __lg(n); k; k >>= 1)
			if (i + k <= n && b[i + k] < x)
				x -= b[i += k];
		return i;
	}
};

//2D Fenwick tree
template <typename T> struct BIT2D {
	int n, m;
	vector<vector<T>> b;
	BIT2D(int n, int m) : n(n), m(m), b(n+1, vector<T>(m+1)) {}
	void add(int r, int c, T v) {
		for (++r; r <= n; r += r & -r)
			for (int i = ++c; i <= m; i += i & -i)
				b[r][i] += v;
	}
	T sum(int r, int c) {
		T s = 0;
		for (++r; r; r -= r & -r)
			for (int i = ++c; i; i -= i & -i)
				s += b[r][i];
		return s;
	}
	T sum(int r1, int c1, int r2, int c2) {
		return sum(r2, c2) - sum(r2, c1-1) - sum(r1-1, c2) + sum(r1-1, c1-1);
	}
};

//Sqrt decomposition
template <class T> struct SqrtDecomp {
	int n, bsz;
	vector<T> a, b;
	SqrtDecomp(int n) : n(n), bsz(sqrt(n) + 1), a(n), b(bsz) {}
	SqrtDecomp(vector<T>& v) : SqrtDecomp(v.size()) {
		for (int i = 0; i < n; ++i) add(i, v[i]);
	}
	void add(int i, T x) {
		b[i / bsz] += x;
		a[i] += x;
	}
	void set(int i, T x) { add(i, x - a[i]); }
	T sum(int l, int r) {
		T res = 0;
		for (int i = l; i <= r;) {
			if (i % bsz == 0 && i + bsz - 1 <= r) {
				res += b[i / bsz];
				i += bsz;
			} else {
				res += a[i++];
			}
		}
		return res;
	}
};

//Matrix Exponentiation
template<class T, int N> struct Matrix {
	using M = Matrix;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		for (int i = 0; i < N; ++i)
			for (int k = 0; k < N; ++k)
				for (int j = 0; j < N; ++j)
					a.d[i][j] += d[i][k] * m.d[k][j];
		return a;
	}
	array<T, N> operator*(const array<T, N>& v) const {
		array<T, N> r{};
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				r[i] += d[i][j] * v[j];
		return r;
	}
	M operator^(long long p) const {
		assert(p >= 0);
		M a, b = *this;
		for (int i = 0; i < N; ++i) a.d[i][i] = 1;
		while (p) {
			if (p & 1) a = a * b;
			b = b * b;
			p >>= 1;
		}
		return a;
	}
};

//CHT
#define ll long long
bool Q;
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};
struct CHT : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.k * x + l.m;
	}
};


//KMP
vi pi(const string& s) {
	vi p(sz(s));
	forn(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}
vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	forn(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

//Z function
vi Z(const string& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	forn(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}


//Manacher, using to find all palindromes centered at i
struct Manacher {
    vector<int> d1, d2;
    Manacher(const string &s) {
        int n = s.size();
        d1.assign(n, 0);
        for (int l = 0, r = -1, i = 0; i < n; i++) {
            int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k--;
            if (i + k > r) { l = i - k; r = i + k; }
        }
        d2.assign(n, 0);
        for (int l = 0, r = -1, i = 0; i < n; i++) {
            int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k--;
            if (i + k > r) { l = i - k - 1; r = i + k; }
        }
    }
    int odd(int i) const { return 2*d1[i] - 1; }
    int even(int i) const { return 2*d2[i+1]; }
};




