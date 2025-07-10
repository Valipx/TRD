#include<bits/stdc++.h>
using namespace std;

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