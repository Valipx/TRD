struct undigraph {
    int n;
    vector<vector<int>> adj;
    vector<int> color;
    vector<int> visited;
    map<pair<int,int>> cost;
    bool bip;
    
    undigraph(int num){
        n = num + 1;
        adj.resize(n + 1);
        color.resize(n + 1);
        visited.resize(n + 1);
    }

    void add(int u, int v, int c = 0){
        adj[u].pb(v);
        adj[v].pb(u);
        cost[{u,v}] = c;
        cost[{v,u}] = c;
    }

    bool isbipartite(){
        color = vector<int>(n+1, -1);
        bool is_bipartite = true;
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (color[i] == -1) {
                q.push(i);
                color[i] = 0;
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    for (int u : adj[v]) {
                        if (color[u] == -1) {
                            color[u] = color[v] ^ 1;
                            q.push(u);
                        } else {
                            is_bipartite &= color[u] != color[v];
                        }
                    }
                }
            }
        }
        return bip = is_bipartite;
    }

    vector<vector<int>> sets(){
        vector<int> a;
        vector<int> b;
        for(int i = 1; i <= n; i++){
            if(color[i] == 1){
                a.push_back(i);
            } else b.push_back(i);
        }
    }

    vector<int> getcolor(){
        return color;
    }
    
    void dijkstras(int s, vector<int> &d, vector<int> &p){
    	d.assign(n+1,INT_MAX);
    	p.assign(n+1,-1);
    	
    	d[s] = 0;
    	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    	q.push({0,s});
    	while(not q.empty()){
    		auto [dist, v] = q.top();
    		q.pop();
    		if(dist != d[v]) continue;
    		
    		for(auto u : adj[v]){
    			int c = cost[{u,v}];
    			if(d[v] + c < d[u]){
    				d[u] = d[v] + c;
    				p[u] = v;
    				q.push({d[u], u});
				}
			}
		}
	}
	
	vector<int> restore_path(int s, int t, vector<int> const& p) {
	    vector<int> path;
	    for (int v = t; v != s; v = p[v])
	        path.push_back(v);
	    path.push_back(s);
	
	    reverse(path.begin(), path.end());
	    return path;
	}
    
};