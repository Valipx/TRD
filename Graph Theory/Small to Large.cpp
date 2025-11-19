vi siz(N), ans(N), c(N);
vector<vi> adj(N);
vector<multiset<int>> a(N); // or use map/set/etc.
function<void(int,int)> dfs = [&](int v, int p) {
	int big = -1; siz[v] = 1;
	for (int u : adj[v]) if (u != p) {
		dfs(u, v); siz[v] += siz[u];
		if (big == -1 || siz[u] > siz[big]) big = u;
	}
	if (big != -1) swap(a[v], a[big]);
	for (int u : adj[v]) if (u != p && u != big)
		for (int x : a[u]) a[v].insert(x);
	a[v].insert(c[v]); // include self
	ans[v] = sz(a[v]); // example: size of multiset
};
