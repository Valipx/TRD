int lcs(string a, string b) {
    vi dp(sz(b) + 1);
    for (char c : a) {
        for (int i = sz(b) - 1; i >= 0; i--) {
            if (b[i] == c) dp[i + 1] = dp[i] + 1;
        }
        for (int i = 0; i < sz(b); ++i) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
        }
    }
    return dp[sz(b)];
}