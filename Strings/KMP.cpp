#include<bits/stdc++.h>
using namespace std;

vi pi(const string& s) {
	vi p(sz(s));
	forn(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}
vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	forn(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}