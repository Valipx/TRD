#include<bits/stdc++.h>
using namespace std;

#define forn(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define vi vector<int>
#define pii pair<int,int>
#define int long long
#define sz(a) (int)a.size()

template<class T>
pair<T, vector<pair<int,int>>> edk(vector<unordered_map<int,T>>& g, int s, int t) {
    int n = g.size(), l, r;
    auto og = g;                 // keep original capacities
    T flow = 0, aug;
    vector<int> q(n), p(n);

    // Edmonds–Karp
    for (;;) {
        fill(p.begin(), p.end(), -1);
        p[s] = s; q[l = 0] = s; r = 1;
        while (l < r && p[t] == -1) {
            int u = q[l++];
            for (auto &e : g[u]) if (e.second > 0 && p[e.first] == -1)
                p[q[r++] = e.first] = u;
        }
        if (p[t] == -1) break;
        aug = numeric_limits<T>::max();
        for (int v = t; v != s; v = p[v])
            aug = min(aug, g[p[v]][v]);
        for (int v = t; v != s; v = p[v]) {
            int u = p[v];
            if ((g[u][v] -= aug) == 0) g[u].erase(v);
            g[v][u] += aug;
        }
        flow += aug;
    }

    // find reachable in residual
    vector<char> vis(n);
    queue<int> bfs;
    bfs.push(s);
    vis[s] = 1;
    while (!bfs.empty()) {
        int u = bfs.front(); bfs.pop();
        for (auto &e : g[u]) if (e.second > 0 && !vis[e.first]) {
            vis[e.first] = 1;
            bfs.push(e.first);
        }
    }

    // collect cut edges
    vector<pair<int,int>> cut;
    for (int u = 0; u < n; u++) if (vis[u]) {
        for (auto &e : og[u]) if (e.second > 0 && !vis[e.first]) {
            cut.emplace_back(u, e.first);
        }
    }

    return {flow, cut};
}

int32_t main(){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        int n, m;
        cin >> n >> m;
        vector<unordered_map<int,int>> adj(n);
        while(m--){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u][v] = 1;
            adj[v][u] = 1;
        }
        auto [mincut, edges] = edk<int>(adj, 0, n - 1);
        cout << mincut << endl;
        for(auto it : edges){
            cout << it.first+1 << " " << it.second+1 << endl;
        }
}