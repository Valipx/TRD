#include<bits/stdc++.h>
using namespace std;

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