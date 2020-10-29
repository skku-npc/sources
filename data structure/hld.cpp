constexpr int MAXN = 111111;

vector<int> graph[MAXN];
int par[MAXN], sub[MAXN], dep[MAXN];
void dfs(int now, int before) {
    par[now] = before;
    sub[now] = 1;
    for(int nxt: graph[now]) if (nxt != before)
        {
            dep[nxt] = dep[now] + 1;
            dfs(nxt, now);
            sub[now] += sub[nxt];
        }
}
vector<int> chain[MAXN];
int wt_chain[MAXN], in_chain[MAXN], ps[MAXN], occ = 0;
void hld(int now, int before, int cur_chain) {
    wt_chain[now] = cur_chain;
    in_chain[now] = chain[cur_chain].size();
    chain[cur_chain].push_back(now);
    int hvy = -1;
    for (int nxt: graph[now]) if (nxt != before)
        {
            if (hvy==-1 || sub[nxt] > sub[hvy]) hvy = nxt;
        }
    if (hvy != -1) hld(hvy, now,  cur_chain);
    for (int nxt: graph[now]) if (nxt != before)
        {
            if (nxt != hvy) hld(nxt, now, nxt);
        }
    if (cur_chain == now)
    {
        ps[cur_chain] = occ;
        occ += chain[cur_chain].size();
    }
}
//위치 공식 : ps[wt_chain[a]]+in_chain[a]
int get_lca(int a, int b)
{
    while(wt_chain[a] != wt_chain[b])
    {
        if (dep[wt_chain[a]] > dep[wt_chain[b]])
            a = par[wt_chain[a]];
        else
            b = par[wt_chain[b]];
    }
    if (in_chain[a] > in_chain[b])
        return b;
    else
        return a;
}
