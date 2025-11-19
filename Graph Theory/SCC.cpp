void scc(const vvi& g, vvi& comps, vvi& cg) {
    int n = sz(g);
    comps.clear(); cg.clear();
    vi order; order.reserve(n);
    vi vis(n,0), root(n);
    auto dfs = [&](auto&& self, int u, const vvi& gr, vi& out) -> void {
        vis[u] = 1;
        for (int v : gr[u]) if (!vis[v]) self(self, v, gr, out);
        out.push_back(u);
    };
    forn(i,0,n) if (!vis[i]) dfs(dfs, i, g, order);
    vvi grR(n);
    forn(u,0,n) for (int v : g[u]) grR[v].push_back(u);
    fill(all(vis), 0);
    reverse(all(order));
    for (int u : order) if (!vis[u]) {
        vi c; dfs(dfs, u, grR, c);
        comps.push_back(c);
        int r = *min_element(all(c));
        for (int v : c) root[v] = r;
    }
    cg.assign(n, vi());
    forn(u,0,n) for (int v : g[u])
        if (root[u] != root[v])
            cg[root[u]].push_back(root[v]);
}
