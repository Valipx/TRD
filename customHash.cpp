#include<bits/stdc++.h>
using namespace std;

mt19937 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count());
static inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
uint64_t mix(uint64_t h1, uint64_t h2, uint64_t seed) {
    if (h1 > h2) swap(h1, h2);
    uint64_t x = h1 ^ (h2 + seed);
    return splitmix64(x);
}