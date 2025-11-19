struct BellmanFord {
	struct Edge { int u, v; ll w; };
	int n; vector<Edge> e;
	vector<ll> d; vector<int> pre;
	void init(int _n) { n = _n; e.clear(); }
	void add(int u, int v, ll w) { e.push_back({u, v, w}); }
	bool run(int src) {
		d.assign(n, LLONG_MAX); pre.assign(n, -1); d[src] = 0;
		rep(i,0,n-1) for (auto [u, v, w] : e)
			if (d[u] < LLONG_MAX && d[v] > d[u] + w)
				d[v] = d[u] + w, pre[v] = u;
		for (auto [u, v, w] : e)
			if (d[u] < LLONG_MAX && d[v] > d[u] + w)
				return false;
		return true;
	}
	vi getNegCycle() {
		for (auto [u, v, w] : e)
			if (d[u] < LLONG_MAX && d[v] > d[u] + w) {
				int x = v;
				rep(i,0,n) x = pre[x];
				vi cyc;
				for (int y = x;; y = pre[y]) {
					cyc.pb(y);
					if (y == x && sz(cyc) > 1) break;
				}
				reverse(all(cyc));
				return cyc;
			}
		return {};
	}
};
