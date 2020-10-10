const int MN = 802;

int r[MN][MN];
int d[MN][MN];
vector<int> graph[MN];

int chk[MN][MN];
void mkedge(int fm, int to, int w) {
    if (!chk[fm][to]) {
        graph[fm].pb(to);
        graph[to].pb(fm);
        chk[fm][to] = chk[to][fm] = 1;
    }
    r[fm][to] += w;
}

int dist[MN];
int prv[MN];
bool spfa(int src, int sink) {
    bitset<MN> inQ;
    queue<int> q;

    memset(prv, -1, sizeof prv);
    memset(dist, 0x3F, sizeof dist);
    // q, inQ, dist, prv, r(chk can)

    dist[src] = 0;
    q.push(src);
    inQ[src] = 1;
    while (sz(q)) {
        int now = q.front();
        q.pop();
        inQ[now] = 0;
        for (int nxt : graph[now]) {
            if (r[now][nxt] > 0 && dist[nxt] > dist[now] + d[now][nxt]) {
                dist[nxt] = dist[now] + d[now][nxt];
                prv[nxt] = now;
                if (!inQ[nxt]) {
                    q.push(nxt);
                    inQ[nxt] = 1;
                }
            }
        }
    }
    return prv[sink] != -1;
}
pair<int, int> mcmf(int src, int sink) {
    pair<int, int> ret = {0, 0};
    while (spfa(src, sink)) {
        int flow = INT_MAX;
        for (int now = sink; now != src; now = prv[now])
            flow = min(flow, r[prv[now]][now]);
        ret.s += flow;
        for (int now = sink; now != src; now = prv[now]) {
            ret.f += flow * d[prv[now]][now];
            r[prv[now]][now] -= flow;
            r[now][prv[now]] += flow;
        }
    }
    return ret;
}

int WK, src, sink;
void solve() {
    int n, m;
    cin >> n >> m;
    WK = n;
    src = n + m;
    sink = n + m + 1;
    forn(i, n) mkedge(src, i, 1);
    forn(i, m) mkedge(i + WK, sink, 1);
    forn(i, n) {
        int k;
        cin >> k;
        forn(j, k) {
            int w, cst;
            cin >> w >> cst;
            --w;
            mkedge(i, w + WK, 1);
            d[i][w + WK] = -cst;
            d[w + WK][i] = cst;
        }
    }
    pair<int, int> p = mcmf(src, sink);
    cout << p.s << " " << -p.f << "\n";
}