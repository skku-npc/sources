#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    typedef int flow_t;

    struct Edge {
        int nxt;
        flow_t res;  // residual flow
        size_t inv;  // inversed edge index
        Edge(int n, flow_t r, size_t v) : nxt(n), res(r), inv(v) {}
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> q, lvl, start;

    Dinic(int _n) {
        n = _n;
        adj.resize(n);
    }
    void add_edge(int a, int b, flow_t cap, flow_t cap_inv=0) {
        adj[a].emplace_back(b, cap, adj[b].size());
        adj[b].emplace_back(a, cap_inv, adj[a].size() - 1);
    }
    bool assign_level(int src, int sink) {
        memset(&lvl[0], 0, sizeof(lvl[0]) * n);
        queue<int> q;
        q.push(src);
        lvl[src] = 1;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto i : adj[cur]) {
                if (!lvl[i.nxt] && i.res > 0) {
                    lvl[i.nxt] = lvl[cur] + 1;
                    q.push(i.nxt);
                }
            }
        }
        return lvl[sink];
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

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n; cin >> n;
    Dinic d(52);
    for (int i = 0; i < n; i++) {
        int k;
        char c1, c2;
        cin >> c1 >> c2 >> k;
        int a = islower(c1) ? c1 - 'a' + 26 : c1 - 'A';
        int b = islower(c2) ? c2 - 'a' + 26 : c2 - 'A';
        d.add_edge(a, b, k, k);
    }
    cout << d.solve(0, 25) << endl;
}

// 백준 6086번: 최대 유량