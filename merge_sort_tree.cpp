#define all(v) (v).begin(),(v).end()
struct merge_sort_tree{
    vector<vector<int>> tree;
    vector<int> a;
    int n;
    int base;
    merge_sort_tree(int n): n(n) {
        base = 1;
        while(base < n) base <<= 1;
        tree.resize(base*2 - 1);
        --base;
        a.resize(n);
    }
    void init() {
        for (int i = base; i<base+n;++i) {
            tree[i].resize(1);
            tree[i][0] = a[i-base];
        }
        for (int i=base-1; i>=0; --i) {
            tree[i].resize(tree[i*2+1].size() + tree[i*2+2].size());
            merge(all(tree[2*i+1]), all(tree[2*i+2]), tree[i].begin());
        }
    }
    //[qs, qe]에서 val이하 몇개?
    int qry_ub(int qs, int qe, int val) {
        int ret = 0;
        qs += base;
        qe += base+1;
        for(; qs < qe; qs = qs / 2, qe = qe / 2){
            if (qs%2 == 0){
                ret += upper_bound(all(tree[qs]), val) - tree[qs].begin();
                ++qs;
            }
            if (qe%2 == 0){
                --qe;
                ret += upper_bound(all(tree[qe]), val) - tree[qe].begin();
            }
        }
        return ret;
    }
    // [qs, qe]에서 val미만 몇개?
    int qry_lb(int qs, int qe, int val){
        int ret = 0;
        qs += base;
        qe += base+1;
        for(; qs < qe; qs = qs / 2, qe = qe / 2){
            if (qs%2 == 0){
                ret += lower_bound(all(tree[qs]), val) - tree[qs].begin();
                ++qs;
            }
            if (qe%2 == 0){
                --qe;
                ret += lower_bound(all(tree[qe]), val) - tree[qe].begin();
            }
        }
        return ret;
    }
    //배열 a에서, [l,r]에 속하는 '값'들만 고려 했을 때, k번째 원소의 index를 반환
    int qry_kth(int l, int r, int k){
        int node = 0;
        while(node < base){
            int c = upper_bound(all(tree[node*2+1]), r) -
                    lower_bound(all(tree[node*2+1]), l);
            if (c >= k){
                node = 2*node + 1;
            }
            else{
                node = 2*node + 2;
                k -= c;
            }
        }
        return node - base;
    }
};
