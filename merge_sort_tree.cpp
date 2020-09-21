struct merge_sort_tree
{
    vector<vector<int>> tree;
    vector<int> a;
    int n;
    merge_sort_tree(int n): n(n)
    {
        int sz = 1;
        while(sz < n) sz <<= 1;
        sz <<= 1;
        tree.resize(sz);
        a.resize(n);
    }

    void init(int ns = 0, int ne = -1, int node = 1)//0, n-1, 1
    {
        if (ne == -1) ne += n;
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
    int qry_ub(int qs, int qe, int val, int ns = 0, int ne = -1, int node = 1)//val 이하의 수가 몇개?
    {
        if (ne == -1) ne += n;
        if (qs > ne || ns > qe) return 0;
        if (qs <= ns && ne <= qe)
        {
            return upper_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
        }
        int mid = (ns + ne) / 2;
        return qry_ub(qs, qe, val, ns, mid, node*2) + qry_ub(qs, qe, val, mid+1, ne, node*2+1);
    }

    int qry_lb(int qs, int qe, int val, int ns = 0, int ne = -1, int node = 1)//val 미만의 수가 몇개?
    {
        if (ne == -1) ne += n;
        if (qs > ne || ns > qe) return 0;
        if (qs <= ns && ne <= qe)
        {
            return lower_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
        }
        int mid = (ns + ne) / 2;
        return qry_lb(qs, qe, val, ns, mid, node*2) + qry_lb(qs, qe, val, mid+1, ne, node*2+1);
    }
};
