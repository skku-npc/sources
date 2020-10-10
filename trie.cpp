struct trie {
    int conv(char c) { return c - 'a'; }
    struct vertex {
        int nxt[26]; // 알파벳 갯수
        int finish;  // if not finish, -1
        // 0-based를 가정하는 것
        vertex() {
            memset(nxt, -1, sizeof nxt);
            finish = -1;
        }
    };
    vector<vertex> data;
    int head; // data[head]: head의 vertex
    int size; // 단어의 총 개수
    trie(int cap = 30000) {
        // trie 자체가 용량을 많이 잡아먹기에 생성자에서 cap을 잘 지정하여 매모리를 아낀다
        // cap = (단어의 갯수 * 단어의 길이 + 1)
        data.reserve(cap); 
        head = 0;
        size = 0;
        data.push_back(vertex());
    }
    void add(const char *str) {
        int v_idx = head;
        for (int idx = 0; str[idx]; ++idx) {
            if (data[v_idx].nxt[conv(str[idx])] == -1) {
                data[v_idx].nxt[conv(str[idx])] = data.size();
                data.push_back(vertex());
            }
            v_idx = data[v_idx].nxt[conv(str[idx])];
        }
        data[v_idx].finish = size++; // 만약 중복된 단어가 들어올 수 있다면, 각 노드 별로 count 변수를 만들어야 한다.
    }
    int retrieve(const char *str) { // 찾지 못하면 -1, 찾았다면 add되었던 순서를 리턴(0부터 시작)
        int v_idx = head;
        for (int idx = 0; str[idx]; ++idx) {
            if (data[v_idx].nxt[conv(str[idx])] == -1)
                return -1;
            v_idx = data[v_idx].nxt[conv(str[idx])];
        }
        return data[v_idx].finish;
    }
};
