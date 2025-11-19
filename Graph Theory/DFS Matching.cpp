/*
    MAXIMUM BIPARTITE MATCHING (Kuhn's Algorithm)
    ---------------------------------------------
    Finds the maximum number of independent edges in a bipartite graph.
    
    USAGE:
    1. Graph 'g': 
       - Adjacency list representing edges from the LEFT partition to the RIGHT partition.
       - g[i] contains neighbors of Left Node 'i'.
       - Size of 'g' = Number of nodes in Left Partition (N).
    
    2. Vector 'btoa':
       - Represents the matching for the RIGHT partition.
       - Size = Number of nodes in Right Partition (M).
       - Initialize with -1 before calling. 
       - Result: btoa[j] = i means Right Node 'j' is matched with Left Node 'i'.

    3. Returns:
       - The total number of matched pairs.

    COMPLEXITY: O(N * E) worst case.
*/

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1; int di = btoa[j];
    for (int e : g[di])
        if (!vis[e] && find(e, g, btoa, vis)) {
            btoa[e] = di;
            return 1;
        }
    return 0;
}

int dfsMatching(vector<vi>& g, vi& btoa) {
    vi vis;
    forn(i,0,sz(g)) {
        vis.assign(sz(btoa), 0);
        for (int j : g[i])
            if (find(j, g, btoa, vis)) {
                btoa[j] = i;
                break;
            }
    }
    return sz(btoa) - (int)count(all(btoa), -1);
}