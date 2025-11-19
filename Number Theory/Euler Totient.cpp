vi phi_upto(int N) {
	vi phi(N + 1); iota(phi.begin(), phi.end(), 0);
	for (int i = 2; i <= N; ++i)
		if (phi[i] == i)
			for (int j = i; j <= N; j += i)
				phi[j] -= phi[j] / i;
	return phi;
}
