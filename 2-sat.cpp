int n, m;
vector<int> g[20000];
int dfsn[20000], scc[20000];
stack<int> stk;
int ce;
vector<vector<int>> res;
int dfs(int now) {
    dfsn[now] = ce++;
    int ret = dfsn[now];
    stk.push(now);
    for (int nxt : g[now]) {
        if (dfsn[nxt] == -1)
            ret = min(ret, dfs(nxt));
        else if (scc[nxt] == -1)
            ret = min(ret, dfsn[nxt]);
    }
    if (ret == dfsn[now]) {
        res.pb(vector<int>());

        int t;
        do {
            t = stk.top();
            stk.pop();
            scc[t] = sz(res) - 1;
            res.back().push_back(t);
        } while (t != now);
        // sort
    }
    return ret;
}

void solve() {
    memset(dfsn, -1, sizeof dfsn);
    memset(scc, -1, sizeof scc);
    //    ce = 0;
    //    res.clear();
    //
    cin >> n >> m;
    //    forn(i, n) g[i].clear();

    forn(_, m) {
        int x, y;
        cin >> x >> y;
        if (x < 0) {
            x = -x;
            --x;
            x += n;
        } else
            --x;
        if (y < 0) {
            y = -y;
            --y;
            y += n;
        } else
            --y;
        if (x >= n)
            g[x - n].pb(y);
        else
            g[x + n].pb(y);
        if (y >= n)
            g[y - n].pb(x);
        else
            g[y + n].pb(x);
    }
    forn(i, 2 * n) {
        if (dfsn[i] == -1)
            dfs(i);
    }
    forn(i, n) {
        if (scc[i] == scc[i + n]) {
            cout << "0\n";
            return;
        }
    }
    cout << "1\n";
    vector<int> v(2 * n);
    vector<int> ans(n, -1);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [](int a, int b) { return scc[a] > scc[b]; });
    forn(i, 2 * n) {
        if (v[i] >= n) {
            if (ans[v[i] - n] == -1)
                ans[v[i] - n] = 1;
        } else {
            if (ans[v[i]] == -1)
                ans[v[i]] = 0;
        }
    }
    forn(i, n) cout << ans[i] << ' ';
    cout << '\n';
}