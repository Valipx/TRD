vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), q;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	forn(i,0,sz(gr)) if (indeg[i] == 0) q.push_back(i);
	forn(j,0,sz(q)) for (int x : gr[q[j]])
		if (--indeg[x] == 0) q.push_back(x);
	return q;
}
