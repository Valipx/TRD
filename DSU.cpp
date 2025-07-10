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
    }

    int find(int v) {
        if (parent[v] == v) return v;
        int root = find(parent[v]);
        return parent[v] = root;
    }

    void merge(int u, int v) {
        int U = leader(u);
        int V = leader(v);
        if (U == V) return;
        if (size[U] > size[V]) {
            swap(U, V);
        }
        parent[U] = V;
        size[V] += size[U];
    }

    bool connected(int u, int v) {
        return (find(u) == find(v));
    }

    int leader(int u) {
        return find(u);
    }

    int sizeOf(int u) {
        return size[leader(u)];
    }

    vector<int> leaders() {
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (leader(i) == i) result.push_back(i);
        }
        return result;
    }
};