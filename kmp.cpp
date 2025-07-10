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