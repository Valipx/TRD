#include<bits/stdc++.h>
using namespace std;

struct Manacher {
    vector<int> d1, d2;
    Manacher(const string &s) {
        int n = s.size();
        d1.assign(n, 0);
        for (int l = 0, r = -1, i = 0; i < n; i++) {
            int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k--;
            if (i + k > r) { l = i - k; r = i + k; }
        }
        d2.assign(n, 0);
        for (int l = 0, r = -1, i = 0; i < n; i++) {
            int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k--;
            if (i + k > r) { l = i - k - 1; r = i + k; }
        }
    }
    int odd(int i) const { return 2*d1[i] - 1; }
    int even(int i) const { return 2*d2[i+1]; }
};