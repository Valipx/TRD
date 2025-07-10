#include<bits/stdc++.h>
using namespace std;

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