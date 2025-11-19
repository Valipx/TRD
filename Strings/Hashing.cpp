struct Hashing {
	static const int M1 = 999999067, M2 = 19047851;
	static const int B1 = 9973, B2 = 3137;
	inline static vector<int> pow1 = {1};
	inline static vector<int> pow2 = {1};
	vector<int> p_hash1, p_hash2;
	static void ensure_powers(int n) {
		while (pow1.size() <= n) {
			pow1.push_back((pow1.back() * B1) % M1);
			pow2.push_back((pow2.back() * B2) % M2);
		}
	}
	Hashing() : p_hash1(1, 0), p_hash2(1, 0) {}
	Hashing(const string &s) : p_hash1(s.size() + 1), p_hash2(s.size() + 1) {
		ensure_powers(s.size());
		p_hash1[0] = 0;
		p_hash2[0] = 0;
		for (int i = 0; i < s.size(); ++i) {
			p_hash1[i + 1] = ((p_hash1[i] * B1) % M1 + s[i]) % M1;
			p_hash2[i + 1] = ((p_hash2[i] * B2) % M2 + s[i]) % M2;
		}
	}
	pair<int, int> get_hash(int start, int end) {
		int len = end - start + 1;
		int val1 = p_hash1[end + 1] - (p_hash1[start] * pow1[len]) % M1;
		int val2 = p_hash2[end + 1] - (p_hash2[start] * pow2[len]) % M2;
		int hash1 = (val1 % M1 + M1) % M1;
		int hash2 = (val2 % M2 + M2) % M2;
		return {hash1, hash2};
	}
};