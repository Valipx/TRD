vi solve(int cap, vi v, vi w) {
    // Use vector<vi> instead of array for standard C++ compliance
    vector<vi> dp(sz(v) + 1); 
    dp[0].resize(cap + 1);
    
    for (int i = 0; i < sz(v); ++i) {
        dp[i+1] = dp[i];
        // Iterate through possible weights to transition FROM
        for (int j = 0; j < cap + 1 - w[i]; ++j) {
            dp[i+1][w[i]+j] = max(dp[i+1][w[i]+j], dp[i][j] + v[i]);
        }
    }
    
    vi ans;
    // Iterate backwards to reconstruct the path
    for (int i = sz(v) - 1; i >= 0; --i) {
        if (dp[i][cap] != dp[i+1][cap]) {
            cap -= w[i];
            ans.pb(i);
        }
    }
    return ans;
}