struct merge_sort_tree
{
    vector<vector<int>> tree;
    vector<int> a;
    int n;
    int base;
    merge_sort_tree(int n): n(n)
    {
        base = 1;
        while(base < n) base <<= 1;
        tree.resize(base*2 - 1);
        --base;
        a.resize(n);
    }
    void init()
    {
        for (int i = base; i<base+n;++i)
        {
            tree[i].resize(1);
            tree[i][0] = a[i-base];
        }
        for (int i=base-1; i>=0; --i)
        {
            tree[i].resize(tree[i*2+1].size() + tree[i*2+2].size());
            merge(tree[i*2+1].begin(), tree[i*2+1].end(), tree[i*2+2].begin(), tree[i*2+2].end(), tree[i].begin());
        }
    }
    int qry_ub(int qs, int qe, int val)//[qs, qe]에서 val이하 몇개?
    {
        int ret = 0;
        qs += base;
        qe += base+1;
        for(; qs < qe; qs = (qs - 1) / 2, qe = qe/2)
        {
            if (qs%2 == 0)
            {
                ret += upper_bound(tree[qs].begin(), tree[qs].end(), val) - tree[qs].begin();
                ++qs;
            }
            if (qe%2 == 0)
            {
                --qe;
                ret += upper_bound(tree[qe].begin(), tree[qe].end(), val) - tree[qe].begin();
            }
        }
        return ret;
    }
    int qry_lb(int qs, int qe, int val)// [qs, qe]에서 val미만 몇개?
    {
        int ret = 0;
        qs += base;
        qe += base+1;
        for(; qs < qe; qs = (qs - 1) / 2, qe = qe/2)
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
    int qry_kth(int l, int r, int k)//배열 a에서, [l,r]에 속하는 '값'들만 고려 했을 때, k번째 원소의 index를 반환
    {
        int node = 0;
        while(node < base)
        {
            int c = upper_bound(tree[node*2+1].begin(), tree[node*2+1].end(), r) -
                    lower_bound(tree[node*2+1].begin(), tree[node*2+1].end(), l);
            if (c >= k)
            {
                node = 2*node + 1;
            }
            else
            {
                node = 2*node + 2;
                k -= c;
            }
        }
        return node - base;
    }
};
