#include<bits/stdc++.h>
using namespace std;

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
        return (r<0||r>n) 
             ? 0 
             : int(1LL * f[n] * g[r] % MOD * g[n-r] % MOD);
    }
};