struct hopcroft_karp{
    //0based-index
    int nx, ny;
    vector<int> X;//X[x] = 집합 X의 원소 x가 어떤 y에 대응되어 있는가?
    vector<int> Y;//Y[y] = 집합 Y의 원소 y가 어떤 x에 대응되어 있는가?
    vector<vector<int>> adj; // X -> Y 형태의 이분그래프, X를 Y로 대응한다.
    vector<int> dist;
    hopcroft_karp(int nx, int ny) : nx(nx), ny(ny){
        X.resize(nx);
        Y.resize(ny);
        adj.resize(nx);
        dist.resize(nx);
    }
    void add_edge(int x, int y){
        adj[x].push_back(y);
    }

    void assign_level(){
        queue<int> q;
        for(int i=0;i<nx;++i){
            if (X[i] == -1){
                dist[i] = 0;
                q.push(i);
            } else dist[i] = -1;
        }
        while(!q.empty()){
            int now = q.front(); q.pop();
            for (int nxt: adj[now]){
                if (Y[nxt] != -1 && dist[Y[nxt]] == -1){
                    dist[Y[nxt]] = dist[now] + 1;
                    q.push(Y[nxt]);
                }
            }
        }
    }
    bool find_match(int now){
        for (int nxt: adj[now]){
            if (Y[nxt] == -1 || dist[Y[nxt]] == dist[now] + 1 && find_match(Y[nxt])){
                Y[nxt] = now;
                X[now] = nxt;
                return true;
            }
        }
        return false;
    }
    int operator()(){
        X.assign(nx, -1);
        Y.assign(ny, -1);
        int ret = 0;
        int flow = 0;
        do{
            assign_level();
            flow = 0;
            for(int i=0;i<nx;++i)
                flow += X[i] == -1 && find_match(i);
            ret += flow;
        }while(flow);
        return ret;
    }
};
