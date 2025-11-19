tuple<int, int, int> kadane_with_indices(const vi &a) {
	int cur = 0, best = INT_MIN, l = 0, L = 0, R = -1;
	for (int i = 0; i < a.size(); ++i) {
		if (cur <= 0) cur = a[i], l = i;
		else cur += a[i];
		if (cur > best) best = cur, L = l, R = i;
	}
	return {best, L, R}; // subarray a[L..R]
}
