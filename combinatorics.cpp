const int maxn = 1e6;
vector<int> fact(maxn + 1), inv(maxn + 1);

int binpow(int a, int b, int m) {
    if(b == 0) return 1;
    int x = binpow(a, b / 2, m);
    if(b % 2 == 0)
        return (1LL * x * x) % m;
    else
        return (1LL * ((1LL * x * x) % m) * a) % m;
}

void pre(int m) {
    fact[0] = 1;
    for(int i = 1; i <= maxn; i++){
        fact[i] = (1LL * fact[i - 1] * i) % m;
    }
    inv[maxn] = binpow(fact[maxn], m - 2, m);
    for(int i = maxn - 1; i >= 0; i--){
        inv[i] = (1LL * inv[i + 1] * (i + 1)) % m;
    }
}

int ncr(int n, int r, int m) {
    if(r < 0 || r > n) return 0;
    return (1LL * fact[n] * inv[r] % m * inv[n - r]) % m;
}