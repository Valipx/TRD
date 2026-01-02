//Bismillah
#include <bits/stdc++.h>
using namespace std;

// --- Template Start ---
struct Graph {
    int n;
    bool is_directed;
    vector<vector<int>> adj;
    
    // Algorithm State
    vector<int> tin, low;
    int timer;
    vector<pair<int,int>> bridges;
    set<int> articulation_points;
    
    // For BCC (Vertex Biconnected Components)
    vector<vector<pair<int,int>>> bccs; // Stores edges of each component
    stack<pair<int,int>> st;

    Graph(int nodes, bool directed = false) {
        n = nodes;
        is_directed = directed;
        adj.assign(n, vector<int>());
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (!is_directed) adj[v].push_back(u);
    }

    // Core DFS for finding Bridges, APs, and BCCs
    void dfs(int u, int p = -1) {
        tin[u] = low[u] = timer++;
        int children = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            if (tin[v] != -1) {
                // Back-edge
                low[u] = min(low[u], tin[v]);
                if (tin[v] < tin[u]) {
                    st.push({u, v}); // Push back-edge to stack
                }
            } else {
                // Tree-edge
                st.push({u, v});
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                // Check for Bridge
                if (low[v] > tin[u]) {
                    bridges.push_back({u, v});
                }

                // Check for Articulation Point & BCC extraction
                // Condition: low[v] >= tin[u]
                if (low[v] >= tin[u]) {
                    // 1. Mark AP (Logic: Root needs >1 children, others need condition met)
                    if (p != -1) articulation_points.insert(u);

                    // 2. Extract BCC
                    // Pop edges from stack until we remove (u, v)
                    vector<pair<int,int>> current_bcc;
                    while (true) {
                        pair<int,int> edge = st.top();
                        st.pop();
                        current_bcc.push_back(edge);
                        if (edge == make_pair(u, v)) break;
                    }
                    bccs.push_back(current_bcc);
                }
                children++;
            }
        }

        // Root Articulation Point Check
        if (p == -1 && children > 1) {
            articulation_points.insert(u);
        }
    }

    void run() {
        tin.assign(n, -1);
        low.assign(n, -1);
        timer = 0;
        bridges.clear();
        articulation_points.clear();
        bccs.clear();
        while(!st.empty()) st.pop();

        for (int i = 0; i < n; ++i) {
            if (tin[i] == -1) {
                dfs(i);
                // Note: If the stack is not empty after DFS (isolated edges or root remaining),
                // they usually form a component, but the main loop logic handles BCCs at the cutpoint.
                // Any edges remaining in stack belong to the component containing the root.
                if (!st.empty()) {
                    vector<pair<int,int>> current_bcc;
                    while(!st.empty()) {
                        current_bcc.push_back(st.top());
                        st.pop();
                    }
                    bccs.push_back(current_bcc);
                }
            }
        }
    }
};
// --- Template End ---

// --- Usage Example ---
void solve(){
    int n, m;
    cin >> n >> m;
    
    // 1. Initialize (0-indexed logic assumed)
    Graph g(n, false); // false for undirected

    for(int i = 0; i < m; i++){
        int u, v; 
        cin >> u >> v;
        g.add_edge(u, v); 
    }

    // 2. Run Algorithms
    g.run();

    // 3. Print Results
    cout << "Bridges: " << g.bridges.size() << "\n";
    for(auto p : g.bridges) cout << p.first << "-" << p.second << "\n";

    cout << "\nArticulation Points: " << g.articulation_points.size() << "\n";
    for(auto x : g.articulation_points) cout << x << " ";
    cout << "\n";

    cout << "\nBiconnected Components (Edge Lists): " << g.bccs.size() << "\n";
    for(int i = 0; i < g.bccs.size(); i++) {
        cout << "Component " << i + 1 << ": ";
        for(auto edge : g.bccs[i]) {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}