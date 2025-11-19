void floydWarshall(vector<vi>& m) { 
	int n = sz(m);
	forn(i,0,n) m[i][i] = min(m[i][i], 0LL);
	forn(k,0,n) forn(i,0,n) forn(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) {
			auto newDist = max(m[i][k] + m[k][j], -inf);
			m[i][j] = min(m[i][j], newDist);
		}
	forn(k,0,n) if (m[k][k] < 0) forn(i,0,n) forn(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}
