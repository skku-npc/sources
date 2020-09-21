#include <bits/stdc++.h>
using namespace std;

struct node {
    int nxt, flw, rev;
    node(int a, int b, int c) : nxt(a), flw(b), rev(c) {}
};

int T, n, m, ans, src, sink;
int board[51][51];
int level[2550], idx[2550];
vector<vector<node>> adj;
int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};

void addEdge(int a, int b, int flow) {
    adj[a].emplace_back(b, flow, adj[b].size());
    adj[b].emplace_back(a, 0, adj[a].size() - 1);
}

bool inRange(int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < m;
}

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(src);
    level[src] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto i : adj[cur]) {
            if (level[i.nxt] == -1 && i.flw > 0) {
                level[i.nxt] = level[cur] + 1;
                q.push(i.nxt);
            }
        }
    }
    return level[sink] != -1;
}

int dfs(int cur, int cap) {
    if (cur == sink) return cap;
    for (int &i = idx[cur]; i < adj[cur].size(); i++) {
        int nxt = adj[cur][i].nxt;
        int flw = adj[cur][i].flw;
        if (level[cur] + 1 == level[nxt] && flw > 0) {
            int val = dfs(nxt, min(cap, flw));
            if (val > 0) {
                adj[cur][i].flw -= val;
                adj[nxt][adj[cur][i].rev].flw += val;
                return val;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        ans = 0;
        src = n * m;
        sink = src + 1;
        adj = vector<vector<node>>(n * m + 2);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                cin >> board[i][j];
                ans += board[i][j];
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                int cur = i * m + j;
                if ((i + j) & 1) {
                    addEdge(src, cur, board[i][j]);
                    for (int d = 0; d < 4; d++) {
                        int ny = i + dy[d];
                        int nx = j + dx[d];
                        if (!inRange(ny, nx)) continue;
                        int ncur = ny * m + nx;
                        addEdge(cur, ncur, INT_MAX);
                    }
                } else {
                    addEdge(cur, sink, board[i][j]);
                }
            }

        while (bfs()) {
            memset(idx, 0, sizeof(idx));
            while (true) {
                int val = dfs(src, INT_MAX);
                if (!val) break;
                ans -= val;
            }
        }

        cout << ans << '\n';
    }
}

// 백준 11495번: 격자 0 만들기
// https://www.acmicpc.net/problem/11495