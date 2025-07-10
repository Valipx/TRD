struct digraph {
    int n;
    vector<vector<pair<int,int>>> adj;
    const int INF = 1e9;
    vector<int> d; 
    vector<int> p; 

    digraph(int _n) : n(_n) {
        adj.resize(n);
        d.assign(n, INF);
        p.assign(n, -1);
    }
    
    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    bool spfa(int s, int &cycs) {
        d.assign(n, INF);
        p.assign(n, -1);
        vector<int> cnt(n, 0);
        vector<bool> inqueue(n, false);
        queue<int> q;
        
        d[s] = 0;
        q.push(s);
        inqueue[s] = true;
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            inqueue[v] = false;
            
            for (auto edge : adj[v]) {
                int to = edge.first;
                int len = edge.second;
                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                    if (!inqueue[to]) {
                        q.push(to);
                        inqueue[to] = true;
                        cnt[to]++;
                        if (cnt[to] > n) {
                            cycs = to;
                            return false;  
                        }
                    }
                }
            }
        }
        return true;
    }

    vector<int> negCycle(int s) {
        int v = s;
        for (int i = 0; i < n; ++i)
            v = p[v];
        
        vector<int> cycle;
        for (int cur = v;; cur = p[cur]) {
            cycle.push_back(cur);
            if (cur == v && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
};

