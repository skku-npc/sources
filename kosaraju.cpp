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
vector<vector<int>> kosaraju() {
    check.resize(n);
    for (int i = 0; i < n; i++)
        if (!check[i]) dfs(i);
    check = vector<bool>(n);
    vector<vector<int>> ret;
    stack<int> sk;
    vector<int> comp;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (check[node]) continue;
        sk.push(node);
        comp.clear();
        while (!sk.empty()) {
            int curr = sk.top();
            sk.pop();
            check[curr] = true;
            comp.push_back(curr);
            for (auto next : adj_r[curr])
                if (!check[next]) sk.push(next);
        }
        ret.push_back(comp);
    }
    return ret;
}
