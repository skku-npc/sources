int n;
stack<int> st;
vector<bool> check;
vector<vector<int>> adj, adj_r;

void dfs(int curr) {
    check[curr] = true;
    for (auto& next : adj[curr])
        if (!check[next]) dfs(next);
    st.push(curr);
}
set<set<int>> kosaraju() {
    check.resize(n);
    for (int i = 0; i < n; i++)
        if (!check[i]) dfs(i);
    check = vector<bool>(n);
    set<set<int>> ret;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (check[node]) continue;
        set<int> se;
        stack<int> sk;
        sk.push(node);
        while (!sk.empty()) {
            int curr = sk.top();
            sk.pop();
            check[curr] = true;
            se.insert(curr);
            for (auto next : adj_r[curr])
                if (!check[next]) sk.push(next);
        }
        ret.insert(se);
    }
    return ret;
}
