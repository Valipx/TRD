#define ll long long
const int m = 1000000007;
struct mint {
    ll x;
    mint() : x(0) {}
    mint(ll x) : x((x%m+m)%m) {}
    mint& fix() { x = (x%m+m)%m; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint& operator+=(const mint& a) { if ((x+=a.x)>=m) x-=m; return *this; }
    mint& operator-=(const mint& a) { if ((x+=m-a.x)>=m) x-=m; return *this; }
    mint& operator*=(const mint& a) { (x*=a.x)%=m; return *this; }
    mint operator+(const mint& a) const { return mint(*this) += a; }
    mint operator-(const mint& a) const { return mint(*this) -= a; }
    mint operator*(const mint& a) const { return mint(*this) *= a; }
    bool operator<(const mint& a) const { return x < a.x; }
    bool operator==(const mint& a) const { return x == a.x; }
};

istream& operator>>(istream& i, mint& a) { i >> a.x; return i; }
ostream& operator<<(ostream& o, const mint& a) { o << a.x; return o; }

typedef vector<mint> vm;