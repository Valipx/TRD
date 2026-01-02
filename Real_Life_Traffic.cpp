//Bismillah
#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define forn(i, a, n) for (int i = a; i < n; i++)
#define fornr(i, a, n) for (int i = n - 1; i >= a; i--)
#define print(a) cout << a << "\n";
#define printarr(a) forn(i, 0, a.size()) cout << a[i] << " "; cout << endl;
#define file_read(filepath) freopen(filepath, "r", stdin);
#define file_write(filepath) freopen(filepath, "w", stdout);
#define f first
#define s second
#define pb push_back
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define sorted(a) is_sorted(all(a))
#define vi vector<int>
#define vvi vector<vector<int>>
#define vc vector<char>
#define vs vector<string>
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define vpii vector<pair<int,int>>
#define MOD1 1000000007
#define mii map<int,int>
#define sz(a) (int)a.size()
#define ld long double
#define add insert

void solve(int tc){
    int n, m;
    cin >> n >> m;
    vvi adj(n);
    forn(i,0,m){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi disc(n, -1), low(n, -1);
    vi deg(n, 0); 
    vector<bool> vis(n, false);
    set<pii> bridges; 
    int timer = 0;
    function<void(int,int)> br = [&](int u, int p) {
        vis[u] = true;
        disc[u] = low[u] = timer++;
        for(auto v : adj[u]){
            if(v == p) continue;
            if(vis[v]){
                low[u] = min(low[u], disc[v]);
            } else {
                br(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] > disc[u]){
                    bridges.insert({min(u, v), max(u, v)});
                    deg[u]++;
                    deg[v]++;
                }
            }
        }
    };
    br(0, -1);
    fill(all(vis), false);
    int leaves = 0;
    function<void(int, int&)> comp = [&](int u, int &cd) {
        vis[u] = true;
        cd += deg[u];
        for(auto v : adj[u]){
            if(vis[v]) continue;
            if(bridges.count({min(u, v), max(u, v)})) continue;
            
            comp(v, cd);
        }
    };
    forn(i, 0, n){
        if(!vis[i]){
            int curcomp = 0;
            comp(i, curcomp);
            if(curcomp == 1){
                leaves++;
            }
        }
    }
    cout << "Case " << tc << ": " << (leaves + 1) / 2 << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    int tc = 1;
    while(t--){
        solve(tc++);
    }
}