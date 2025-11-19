template<bool VALS_IN_EDGES> struct HLD {
    int N, ti;
    vector<int> par, root, depth, sz, pos, rpos, base;
    vector<vector<int>> adj;
    LazySeg tree;

    // 1. Constructor receives N and allocates vectors
    HLD(int _N) : N(_N), ti(0), par(_N), root(_N), depth(_N), 
                  sz(_N), pos(_N), adj(_N), tree(_N) {}

    void ae(int u, int v) { 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    // 2. Run this AFTER adding edges to build the decomposition
    void build(int R = 0) {
        par[R] = depth[R] = 0;
        ti = 0;
        rpos.clear(); base.clear();
        rpos.reserve(N); base.reserve(N);

        dfsSz(R); 
        root[R] = R; 
        dfsHld(R);
        
        // Initialize Segment Tree with the base layout
        tree = LazySeg(base);
    }

    void dfsSz(int x) {
        sz[x] = 1;
        for (int& y : adj[x]) {
            // Remove parent from adjacency list to treat as directed tree
            par[y] = x; depth[y] = depth[x]+1;
            adj[y].erase(find(adj[y].begin(), adj[y].end(), x)); 
            
            dfsSz(y); sz[x] += sz[y];
            if (sz[y] > sz[adj[x][0]]) swap(y, adj[x][0]); // Heavy child to front
        }
    }

    void dfsHld(int x) {
        pos[x] = ti++; 
        rpos.push_back(x); 
        base.push_back(0); // Initial value (change if input array exists)
        
        for (int y : adj[x]) {
            root[y] = (y == adj[x][0] ? root[x] : y);
            dfsHld(y);
        }
    }

    template<class F>
    void processPath(int u, int v, F op) {
        while (root[u] != root[v]) {
            if (depth[root[u]] < depth[root[v]]) swap(u, v);
            op(pos[root[u]], pos[u]);
            u = par[root[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u] + VALS_IN_EDGES, pos[v]);
    }

    void modifyPath(int u, int v, int val) {
        processPath(u, v, [&](int l, int r) { tree.update(l, r, val); });
    }

    int queryPath(int u, int v) {
        int res = -1e9; // Ensure this identity matches your problem (e.g., 0 or -INF)
        processPath(u, v, [&](int l, int r) { res = max(res, tree.query(l, r)); });
        return res;
    }

    void modifySubtree(int x, int val) {
        tree.update(pos[x] + VALS_IN_EDGES, pos[x] + sz[x] - 1, val);
    }

    int querySubtree(int x) {
        return tree.query(pos[x] + VALS_IN_EDGES, pos[x] + sz[x] - 1);
    }
};