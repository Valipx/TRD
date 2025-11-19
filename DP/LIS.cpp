int lis(const vi &a) {
    vi d;
    for (int x : a) {
        auto it = lower_bound(all(d), x);
        if (it == d.end()) d.pb(x);
        else *it = x;
    }
    return sz(d);
}
