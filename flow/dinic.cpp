struct dinic {
    typedef int flow_t;

    struct edge {
        int nxt;
        flow_t res;  // residual flow
        size_t inv;  // inverse edge index
        edge(int n, flow_t r, size_t v) : nxt(n), res(r), inv(v) {}
    };

    int n;
    vector<vector<edge>> adj;
    vector<int> q, lvl, start;

    dinic(int _n) {
        n = _n;
        adj.resize(n);
    }
    void add_edge(int a, int b, flow_t cap, flow_t cap_inv=0) {
        adj[a].emplace_back(b, cap, adj[b].size());
        adj[b].emplace_back(a, cap_inv, adj[a].size() - 1);
    }
    bool assign_level(int src, int sink) {
        int t = 0;
        memset(&lvl[0], 0, sizeof(lvl[0]) * n);
        lvl[src] = 1;
        q[t++] = src;
        for (int h = 0; h < t && !lvl[sink]; h++) {
            int cur = q[h];
            for (auto& e : adj[cur]) {
                if (lvl[e.nxt] == 0 && e.res > 0) {
                    lvl[e.nxt] = lvl[cur] + 1;
                    q[t++] = e.nxt;
                }
            }
        }
        return lvl[sink] != 0;
    }
    flow_t block_flow(int cur, int sink, flow_t cur_flow) {
        if (cur == sink) return cur_flow;
        for (int& i = start[cur]; i < adj[cur].size(); i++) {
            auto& e = adj[cur][i];
            if (e.res > 0 && lvl[e.nxt] == lvl[cur] + 1) {
                if (flow_t res = block_flow(e.nxt, sink, min(e.res, cur_flow))) {
                    e.res -= res;
                    adj[e.nxt][e.inv].res += res;
                    return res;
                }
            }
        }
        return 0;
    }
    flow_t solve(int src, int sink) {
        q.resize(n);
        lvl.resize(n);
        start.resize(n);
        flow_t ans = 0;
        while (assign_level(src, sink)) {
            memset(&start[0], 0, sizeof(start[0]) * n);
            while (flow_t flow = block_flow(src, sink, numeric_limits<flow_t>::max()))
                ans += flow;
        }
        return ans;
    }
};