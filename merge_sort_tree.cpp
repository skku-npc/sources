struct merge_sort_tree
{
    vector<vector<int>> tree;
    vector<int> a;
    int n;
    merge_sort_tree(int n): n(n)
    {
        tree.resize(2*n-1);
        a.resize(n);
    }
    void init()
    {
        for (int i = n - 1; i<2*n-1;++i)
        {
            tree[i].resize(1);
            tree[i][0] = a[i- (n - 1)];
        }
        for (int i=n-2; i>=0; --i)
        {
            tree[i].resize(tree[i*2+1].size() + tree[i*2+2].size());
            merge(tree[i*2+1].begin(), tree[i*2+1].end(), tree[i*2+2].begin(), tree[i*2+2].end(), tree[i].begin());
        }
    }
    int qry_ub(int qs, int qe, int val)
    {
        int ret = 0;
        qs += n - 1;
        qe += n;
        for(; qs < qe; qs = (qs - 1) / 2, qe = (qe -1)/2)
        {
            if (qs%2 == 0)
            {
                ret += upper_bound(tree[qs].begin(), tree[qs].end(), val) - tree[qs].begin();
                ++qe;
            }
            if (qe%2 == 0)
            {
                --qe;
                ret += upper_bound(tree[qe].begin(), tree[qe].end(), val) - tree[qe].begin();
            }
        };
        return ret;
    }
    int qry_lb(int qs, int qe, int val)
    {
        int ret = 0;
        qs += n - 1;
        qe += n;
        for(; qs < qe; qs = (qs - 1) / 2, qe = (qe -1)/2)
        {
            if (qs%2 == 0)
            {
                ret += lower_bound(tree[qs].begin(), tree[qs].end(), val) - tree[qs].begin();
                ++qs;
            }
            if (qe%2 == 0)
            {
                --qe;
                ret += lower_bound(tree[qe].begin(), tree[qe].end(), val) - tree[qe].begin();
            }
        }
        return ret;
    }
};
