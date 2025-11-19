struct TwoSAT {
    int N; vector<vector<int>> g, gr; vector<int> comp, order;
    TwoSAT(int n): N(n), g(2*n), gr(2*n), comp(2*n) {}
    // var i → literal 2*i (true), 2*i+1 (false)
    void imply(int a,int b){ g[a].push_back(b); gr[b].push_back(a); }
    void either(int a,int b){ imply(a^1,b); imply(b^1,a); }
    vector<int> solve() {
        order.clear();
        comp.assign(2*N,-1);
        function<void(int)> dfs1 = [&](int u){
            comp[u]=0;
            for(int v:g[u]) if(comp[v]<0) dfs1(v);
            order.push_back(u);
        };
        for(int i=0;i<2*N;i++) if(comp[i]<0) dfs1(i);
        comp.assign(2*N,-1);
        int cid=0;
        function<void(int)> dfs2 = [&](int u){
            comp[u]=cid;
            for(int v:gr[u]) if(comp[v]<0) dfs2(v);
        };
        for(int i=2*N-1;i>=0;i--) {
            int u=order[i];
            if(comp[u]<0) dfs2(u), cid++;
        }
        vector<int> res(N);
        for(int i=0;i<N;i++){
            if(comp[2*i]==comp[2*i+1]) return {};
            res[i]= comp[2*i] > comp[2*i+1];
        }
        return res;
    }
};
