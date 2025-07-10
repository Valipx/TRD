#include<bits/stdc++.h>
using namespace std;

struct Node {
    public:
    int v = 0;
    Node() {};
    Node(int val){
        v = val;
    }
    void merge(const Node& l, const Node& r){
        v = l.v + r.v;
    }
};

struct Update {
    public:
    int v = 0;
    Update() {};
    Update(int val){
        v = val;
    }

    void combine(const Update& otherupdate, const int& tl, const int& tr){
        v += otherupdate.v;
    }

    void apply(Node &node, const int& tl, const int& tr) const {
        node.v += (tr - tl + 1)  * v;
    }
};

template<typename node, typename update>
struct SegTree {
    int n;
    vector<node> t;
    vector<update> unprop;
    vector<bool> lazy;
    node identityElement;
    update identityTransformation;

    public:
    SegTree(int num){
        n = num;
        t.resize(4 * n);
        unprop.resize(4 * n);
        lazy.resize(4 * n);
        identityElement = Node();
        identityTransformation = Update();
    }

    void apply(const int& v, const int& tl, const int& tr, const update& upd){
        if(tl != tr){
            lazy[v] = true;
            unprop[v].combine(upd,tl,tr);
        }
        upd.apply(t[v], tl, tr);
    }

    void pushdown(const int& v, const int& tl, const int& tr){
        if(not lazy[v]) return;
        lazy[v] = false;
    }
}
