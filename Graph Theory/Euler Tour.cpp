struct TreeTour {
    int n;
    int timer;
    vector<vector<int>> adj;
    vector<int> st, en, par;

    // Constructor: Allocates vectors based on n
    // Use n+1 if your graph is 1-based, or n if 0-based.
    TreeTour(int _n) : n(_n) {
        adj.resize(n);
        st.resize(n);
        en.resize(n);
        par.assign(n, -1); // Initialize parents to -1
        timer = 0;
    }

    void ae(int a, int b) { 
        adj[a].push_back(b); 
        adj[b].push_back(a); 
    }

    void dfs(int x) {
        st[x] = timer++;
        for (int y : adj[x]) {
            if (y != par[x]) {
                par[y] = x; 
                dfs(y); 
            }
        }
        en[x] = timer - 1;
    }   

    void build(int root = 0) { 
        timer = 0;
        par[root] = root; // Set root's parent to itself or -1 to stop
        dfs(root); 
    } 
};