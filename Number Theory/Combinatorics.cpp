combs/*
    === COMBINATORICS IDENTITIES & CHEATSHEET ===

    1. [cite_start]STARS AND BARS (Distributing N items into K bins) [cite: 1]
       -------------------------------------------------------
       A. Non-negative (bins can be empty): x1 + ... + xk = N, xi >= 0
          Formula: C(N + K - 1, K - 1)

       B. Positive (bins cannot be empty): x1 + ... + xk = N, xi >= 1
          Formula: C(N - 1, K - 1)

       C. Lower Bounds: xi >= ai
          Let SumA = sum(a1...ak). New N' = N - SumA.
          Reduce to Case A: C(N' + K - 1, K - 1)

       D. Upper Bounds (Inclusion-Exclusion): 0 <= xi <= B
          Sum_{j=0 to K} (-1)^j * C(K, j) * C(N - j*(B+1) + K - 1, K - 1)
          (Note: The term C(n, r) is 0 if r > n, handling the stop condition implicitly)

    2. BASIC IDENTITIES
       -------------------------------------------------------
       - Symmetry:      C(n, k) = C(n, n-k)
       - Pascal:        C(n, k) = C(n-1, k-1) + C(n-1, k)
       - Sum of row:    Sum_{i=0 to n} C(n, i) = 2^n
       - Alt Sum:       Sum_{i=0 to n} (-1)^i * C(n, i) = 0

    3. ADVANCED IDENTITIES
       -------------------------------------------------------
       - Hockey Stick:  Sum_{i=r to n} C(i, r) = C(n+1, r+1)
       - Vandermonde:   Sum_{k=0 to r} C(m, k) * C(n, r-k) = C(m+n, r)
                        (Choosing r items from two groups of size m and n)
       - Sum of Sq:     Sum_{i=0 to n} C(n, i)^2 = C(2n, n)

    4. CATALAN NUMBERS
       -------------------------------------------------------
       Cat(n) = C(2n, n) / (n + 1)
       - Valid parenthesis sequences of length 2n
       - Binary trees with n nodes
       - Triangulations of convex polygon with n+2 vertices
*/

template<int MAXN, int MOD>
struct Comb {
    array<int,MAXN+1> f, g;  
    Comb() {
        f[0]=1;
        for(int i=1;i<=MAXN;++i) 
            f[i]=1LL*f[i-1]*i%MOD;
        g[MAXN]=powmod(f[MAXN], MOD-2);
        for(int i=MAXN;i>0;--i) 
            g[i-1]=1LL*g[i]*i%MOD;
    }
    static int powmod(int a, int p) {
        int res=1;
        for(; p; p>>=1, a=1LL*a*a%MOD) 
            if(p&1) res=1LL*res*a%MOD;
        return res;
    }
    int operator()(int n, int r) const {
        return (r<0||r>n) ? 0 
             : int(1LL * f[n] * g[r] % MOD * g[n-r] % MOD);
    }
};