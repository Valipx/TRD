#include<bits/stdc++.h>
using namespace std;

#define forn(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define vi vector<int>
#define pii pair<int,int>
#define int long long
#define sz(a) (int)a.size()

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