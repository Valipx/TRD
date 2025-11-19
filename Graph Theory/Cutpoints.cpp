vector<int> tin(n + 1, -1), low(n + 1, -1), vis(n + 1, 0);
    int timer = 0;
    set<int> cutpoints;
    function<void(int, int)> dfs = [&](int v, int p) {
        vis[v] = 1, tin[v] = low[v] = timer++;
        int children = 0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (vis[to]) low[v] = min(low[v], tin[to]);
            else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p != -1) cutpoints.insert(v);
                ++children;
            }
        }
        if (p == -1 && children > 1) cutpoints.insert(v);
    };
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(i, -1);
