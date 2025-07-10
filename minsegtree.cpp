struct segtree{
    int n;
    vector<int> t;

    public:
    segtree(int num){
        n = num;
        t = vector<int>(4 * n);
    }

    void build(vector<int> &a, int v, int tl, int tr){
        if(tl == tr){
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build(a, 2 * v, tl, tm);
        build(a, (2 * v) + 1, tm + 1, tr); 
        t[v] = min(t[2 * v], t[(2 * v) + 1]);
    }

    int query(int v, int tl, int tr, int l, int r){
        if(l > r) return INT_MAX; 
        if(tl > r || tr < l) return INT_MAX;
        if(l <= tl && tr <= r) return t[v]; 

        int tm = (tl + tr) >> 1;
        int left = query(2 * v, tl, tm, l, min(r, tm));
        int right = query((2 * v) + 1, tm + 1, tr, max(l, tm + 1), r);
        return min(left, right);
    }

    void build(vector<int> &a){
        build(a, 1, 0, n - 1);
    }
    int query(int l, int r){
        return query(1, 0, n - 1, l, r);
    }
};