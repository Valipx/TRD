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
#define sz(a) a.size()
#define ld long double
#define add insert

vector<int> prefix_function(const string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
    
vector<int> occur(const string &s, const string &p) {
    if(p.empty()){
        vector<int> occ;
        for (int i = 0; i <= s.size(); i++)
            occ.push_back(i);
        return occ;
    }
    vector<int> occ;
    vector<int> pi = prefix_function(p);
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];
            if (s[i] == p[j])
                j++;
            if (j == p.size()) {
                occ.push_back(i - p.size() + 1);
                j = pi[j - 1];
        }
    }
    return occ;
}

vi Z(const string& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	forn(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}

void solve(){
    string s;
    cin >> s;
    auto k = prefix_function(s);
    auto z = Z(s);
    printarr(z)
    printarr(k)
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    //cin >> t;
    while(t--){
    	solve();
	}
}
