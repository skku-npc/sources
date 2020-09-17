#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    vector<int> tree, lazy;
    int base;

    SegTree(int a) {
        base = 1;
        while (base < a) base <<= 1;
        tree.resize((base + 1) << 1);
        base--;
    }

    void update(int idx, int val) {
        idx += base;
        tree[idx] = val;//
        idx >>= 1;
        while (idx != 0) {
            tree[idx] = max(tree[idx*2], tree[idx*2+1]);//
            idx >>= 1;
        }
    }

    int query(int l, int r, int s=1, int e=-1, int node=1) {
        if (e == -1) e = base + 1;
        propagate(s, e, node);
        if (l > e || r < s) return INT_MIN;//
        if (l <= s && e <= r) return tree[node];
        return max(query(l, r, s, (s+e)/2, node*2), query(l, r, (s+e)/2+1, e, node*2+1));//
    }

    ////////////////// UNDERNEATH HERE IS FOR LAZY-PROPAGATION //////////////////

    void propagate(int s, int e, int node) {
        if (lazy[node] == 0) return;//
        if (s < e) {
            lazy[node*2] += lazy[node];//
            lazy[node*2+1] += lazy[node];//
        }
        tree[node] += lazy[node] * (e - s + 1);//
        lazy[node] = 0;//
    }

    void add_val(int val, int l, int r, int s=1, int e=-1, int node=1) {
        if (e == -1) e = base + 1;
        propagate(s, e, node);
        if (l > e || r < s) return;
        if (l <= s && e <= r) {
            lazy[node] += val;//
            propagate(s, e, node);
        } else {
            add_val(val, l, r, s, (s+e)/2, node*2);
            add_val(val, l, r, (s+e)/2+1, e, node*2+1);
            tree[node] = tree[node*2] + tree[node*2+1];//
        }
    }
};
