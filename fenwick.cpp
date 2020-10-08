typedef long long ll;
// #define int ll
struct fenwick {
    vector<int> tree;
    fenwick(int n) : tree(n+1){}
    void update(int idx, int df) {
        for (; idx < tree.size(); idx += idx & -idx) tree[idx] += df;
    }
    ll get_sum(int e) {
        ll ret = 0;
        for (; e > 0; e -= e & -e) ret += tree[e];
        return ret;
    }
};
