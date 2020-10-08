struct convexhull_trick
{
    //일단 binary search와 linear둘다 구현해둠
    struct line
    {
        long long a, b;
        pair<long long, long long> start_x;// first/second
        long long y(long long x){return a*x + b;}
        static bool compare_x(line& l, const line& l1, const line& l2)//intersect_x(l, l1) < intersect_x(l, l2)
        {
            long long t1 = (l1.b - l.b) * (l.a - l2.a);
            long long t2 = (l2.b - l.b) * (l.a - l1.a);
            bool op = (l.a - l2.a < 0) ^ (l.a - l1.a < 0);
            return op? t1>t2:t1<t2;
        }
        bool not_start(long long x)//start_x > x
        {
            if (start_x.second < 0) return start_x.first < x*start_x.second;
            return start_x.first > x * start_x.second;
        }
    };
    vector<line> stk;
    int qptr;
    convexhull_trick(int capacity = 100'010) : qptr(0)
    {
        stk.reserve(capacity);
    }
    void init(int capacity = 100'010)
    {
        stk.clear();
        stk.reserve(capacity);
        qptr = 0;
    }
    void push_line(line l)
    {
        while(stk.size() > 1)
        {
            line& l1 = stk[stk.size() - 1];
            line& l2 = stk[stk.size() - 2];
            if (line::compare_x(l, l2, l1)) break;
            stk.pop_back();
        }
        if (qptr >= stk.size()) qptr = stk.size() - 1;
        if(!stk.empty()) l.start_x = make_pair(stk.back().b - l.b, l.a - stk.back().a);
        else l.start_x = make_pair(0LL, 0LL);
        stk.push_back(l);
    }
    void push_line(long long a, long long b)
    {
        push_line({a, b});
    }
    long long query_bs(long long x)
    {
        int lf = 0, rg = stk.size() - 1;
        while(lf < rg)
        {
            int mid = (lf + rg + 1) / 2;
            if (stk[mid].not_start(x))
            {
                rg = mid - 1;
            }else lf = mid;
        }
        return stk[lf].y(x);
    }
    long long query_linear(long long x)//x값이 증가하는 순서대로 들어와야함
    {
        while(qptr + 1 < stk.size() && !stk[qptr+1].not_start(x))
            ++qptr;
        return stk[qptr].y(x);
    }
};
