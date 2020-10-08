constexpr int MAXN = 100'00;

int n, m; // 0-based
vector<int> graph[MAXN];
///////////////////
int dfsn[MAXN], scc[MAXN];
stack<int> stk;
vector<vector<int>> res;
int ce;
int dfs(int now)
{
    dfsn[now] = ce++;
    int ret = dfsn[now];
    stk.push(now);
    for (int nxt: graph[now])
    {
        if (dfsn[nxt] == -1) ret = min(ret, dfs(nxt));
        else if (scc[nxt] == -1) ret = min(ret, dfsn[nxt]);
    }
    if (ret == dfsn[now])
    {
        res.push_back(vector<int>());
        int t;
        do
        {
            t = stk.top(); stk.pop();
            scc[t] = res.size() - 1;
            res.back().push_back(t);
        } while(t != now);
    }
    return ret;
}
void set_scc()
{
    memset(dfsn, -1, sizeof dfsn);
    memset(scc, -1, sizeof scc);
    res.clear();
    ce = 0;
    for (int i=0;i<n;++i)
        if (dfsn[i] == -1) dfs(i);
}
