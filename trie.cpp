struct trie
{
    char conv(char c)
    {
        return c - 'a';
    }
    struct vertex
    {
        int nxt[26];
        int finish; // if not finish, -1
        //0based를 가정하는 것
        vertex()
        {
            memset(nxt, -1, sizeof nxt);
            finish = -1;
        }
    };
    vector<vertex> data;
    int head;//data[head]: head의 vertex
    int size; // 단어의 총 개수
    trie()
    {
        head = 0;
        size = 0;
        data.push_back(vertex());
    }
    void add(const char* str)
    {
        int v_idx = head;
        for (int idx = 0; str[idx]; ++idx)
        {
            if (data[v_idx].nxt[conv(str[idx])] == -1)
            {
                data[v_idx].nxt[conv(str[idx])] = data.size();
                data.push_back(vertex());
            }
            v_idx = data[v_idx].nxt[conv(str[idx])];
        }
        data[v_idx].finish = size++;
    }
    int retrieve(const char* str) //찾지 못하면 -1, 찾았다면 add되었던 순서를 리턴(0부터 시작)
    {
        int v_idx = head;
        for (int idx = 0; str[idx]; ++idx)
        {
            if (data[v_idx].nxt[conv(str[idx])] == -1) return -1;
            v_idx = data[v_idx].nxt[conv(str[idx])];
        }
        return data[v_idx].finish;
    }
};
