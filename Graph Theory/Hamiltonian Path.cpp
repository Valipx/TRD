vi hamiltonianPath(int n, const vector<vi> &adj) {
	vector<vector<bool>> dp(1<<n, vector<bool>(n));
	vector<vi> par(1<<n, vi(n, -1));
	forn(i,0,n) dp[1<<i][i] = 1;
	forn(mask,0,1<<n) forn(u,0,n) if (dp[mask][u])
		for (int v : adj[u]) if (!(mask & (1<<v)) && !dp[mask|(1<<v)][v])
			dp[mask|(1<<v)][v] = 1, par[mask|(1<<v)][v] = u; //add cur mask to new if path counting
	int full = (1<<n)-1, end = -1;
	forn(i,0,n) if (dp[full][i]) { end = i; break; }
	if (end == -1) return {};
	vi path;
	for (int cur = end, mask = full; cur != -1;) {
		path.pb(cur);
		int p = par[mask][cur];
		mask ^= 1 << cur; cur = p;
	}
	reverse(all(path));
	return path;
}
