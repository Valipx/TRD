template<bool directed> struct Euler {
	using pii = pair<int, int>;
	int N; vector<vector<pii>> adj;
	vector<vector<pii>::iterator> its;
	vector<bool> used;
	void init(int _N) { N = _N; adj.resize(N); }
	void add_edge(int a, int b) {
		int id = used.size(); used.push_back(false);
		adj[a].emplace_back(b, id);
		if (!directed) adj[b].emplace_back(a, id);
	}
	vector<pii> solve(int src = 0) {
		its.resize(N); for (int i = 0; i < N; ++i) its[i] = adj[i].begin();
		vector<pii> ans, stk{{src, -1}}; int last = -1;
		while (!stk.empty()) {
			int x = stk.back().first;
			auto &it = its[x], end = adj[x].end();
			while (it != end && used[it->second]) ++it;
			if (it == end) {
				if (last != -1 && last != x) return {};
				ans.push_back(stk.back()); stk.pop_back();
				if (!stk.empty()) last = stk.back().first;
			} else {
				stk.push_back(*it); used[it->second] = true;
			}
		}
		if ((int)ans.size() != (int)used.size() + 1) return {};
		reverse(ans.begin(), ans.end()); return ans;
	}
};
