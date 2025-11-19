#include <bits/stdc++.h>
using namespace std;

struct DSU {
private:
    int n;
    vector<int> parent, size, color;
    bool bipartite;

public:
    DSU(int num) {
        n = num;
        parent = vector<int>(num);
        iota(parent.begin(), parent.end(), 0);
        size = vector<int>(num, 1);
        color = vector<int>(num, 0); 
        bipartite = true;
    }

    int find(int v) {
        if (parent[v] == v) return v;
        int root = find(parent[v]);
        color[v] ^= color[parent[v]];
        return parent[v] = root;
    }

    void merge(int u, int v) {
        int U = find(u);
        int V = find(v);

        if (U == V) {
            if (color[u] == color[v]) bipartite = false;
            return;
        }

        if (size[U] > size[V]) {
            swap(U, V);
            swap(u, v);
        }

        parent[U] = V;
        size[V] += size[U];
        color[U] = color[u] ^ color[v] ^ 1;
    }

    bool connected(int u, int v) {
        return (find(u) == find(v));
    }

    int leader(int u) {
        return find(u);
    }

    int size(int u) {
        return size[leader(u)];
    }

    bool is_bipartite() {
        return bipartite;
    }
};

struct Edge { 
    int u, v, weight; 
    bool operator<(const Edge& other) const { 
        return weight < other.weight; 
    } 
};

pair<int, vector<Edge>> kruskal(int n, vector<Edge>& edges) { 
    DSU dsu(n); 
    vector<Edge> mst;
    int w = 0; 
    sort(edges.begin(), edges.end()); 
    for (const Edge& edge : edges) { 
        if (!dsu.connected(edge.u, edge.v)) { 
            dsu.merge(edge.u, edge.v); 
            mst.push_back(edge); 
            w += edge.weight;
        } 
    } 
    return {w,mst}; 
}