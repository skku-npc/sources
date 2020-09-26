#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int>> edge, inverse_edge;
int v, e;

void dfs(vector<bool> &check, stack<int> &visit, int curr)
{
    check[curr] = true;
    for (int next : edge[curr])
    {
        if (check[next])
            continue;
        dfs(check, visit, next);
    }
    visit.push(curr);
}

set<set<int>> kosaraju(void)
{
    vector<bool> check(v + 1, false);
    stack<int> visit;
    for (int i = 1; i <= v; i++)
    {
        if (check[i])
            continue;
        dfs(check, visit, i);
    }

    check = vector<bool>(v + 1, false);
    set<set<int>> ret;
    while (!visit.empty())
    {
        int node = visit.top();
        visit.pop();
        if (check[node])
            continue;

        stack<int> sk;
        sk.push(node);
        set<int> se;
        while (!sk.empty())
        {
            int curr = sk.top();
            sk.pop();
            check[curr] = true;
            se.insert(curr);
            for (int next : inverse_edge[curr])
            {
                if (check[next])
                    continue;
                sk.push(next);
            }
        }
        ret.insert(se);
    }
    return ret;
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> v >> e;
    edge.resize(v + 1);
    inverse_edge.resize(v + 1);
    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        inverse_edge[b].push_back(a);
    }
    set<set<int>> scc = kosaraju();

    return 0;
}