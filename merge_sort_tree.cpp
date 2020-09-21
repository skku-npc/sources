struct merge_sort_tree
{
    vector<vector<int>> tree;
    vector<int> a;
    merge_sort_tree(int n)
    {
        int sz = 1;
        while(sz < n) sz <<= 1;
        sz <<= 1;
        tree.resize(sz);
        a.resize(n);
    }

    void init(int ns, int ne, int node)//0, n-1, 1
    {
        if (ns == ne)
        {
            tree[node].resize(1);
            tree[node][0] = a[ns];
            return;
        }
        int mid = (ns + ne) / 2;
        init(ns, mid, node * 2);
        init(mid + 1, ne, node * 2 + 1);
        tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
        merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(),
              tree[node].begin());
    }
    int qry_ub(int ns, int ne, int node, int qs, int qe, int val)//val 이하의 수가 몇개?
    {
        if (qs > ne || ns > qe) return 0;
        if (qs <= ns && ne <= qe)
        {
            int m = upper_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
            return m;
        }
        int mid = (ns + ne) / 2;
        int t1 = qry_ub(ns, mid, node * 2, qs, qe, val);
        int t2 = qry_ub(mid + 1, ne, node * 2 + 1, qs, qe, val);
        return t1 + t2;
    }

    int qry_lb(int ns, int ne, int node, int qs, int qe, int val)//val 미만의 수가 몇개?
    {
        if (qs > ne || ns > qe) return 0;
        if (qs <= ns && ne <= qe)
        {
            int m = lower_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
            return m;
        }
        int mid = (ns + ne) / 2;
        int t1 = qry_lb(ns, mid, node * 2, qs, qe, val);
        int t2 = qry_lb(mid + 1, ne, node * 2 + 1, qs, qe, val);
        return t1 + t2;
    }
};
