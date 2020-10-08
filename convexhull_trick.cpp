typedef long long ll;
struct convexhull_trick {
    //일단 binary search와 linear 둘 다 구현해둠
    struct line {
        ll a, b;
        pair<ll, ll> start_x; // first/second
        ll y(ll x) { return a * x + b; }
        static bool compare_x(line &l, const line &l1, const line &l2) {
            // intersect_x(l, l1) < intersect_x(l, l2)
            ll t1 = (l1.b - l.b) * (l.a - l2.a);
            ll t2 = (l2.b - l.b) * (l.a - l1.a);
            bool op = (l.a - l2.a < 0) ^ (l.a - l1.a < 0);
            return op ? t1 > t2 : t1 < t2;
        }
        bool not_start(ll x) { // start_x > x
            if (start_x.second < 0)
                return start_x.first < x * start_x.second;
            return start_x.first > x * start_x.second;
        }
    };
    vector<line> stk;
    int qptr;
    convexhull_trick(int capacity = 100'010) : qptr(0) {
        stk.reserve(capacity);
    }
    void init(int capacity = 100'010) {
        stk.clear();
        stk.reserve(capacity);
        qptr = 0;
    }
    void push_line(line l) {
        while (stk.size() > 1) {
            line &l1 = stk[stk.size() - 1];
            line &l2 = stk[stk.size() - 2];
            if (line::compare_x(l, l2, l1)) break;
            stk.pop_back();
        }
        if (qptr >= stk.size())
            qptr = stk.size() - 1;
        if (!stk.empty()) l.start_x = make_pair(stk.back().b - l.b, l.a - stk.back().a);
        else l.start_x = make_pair(0LL, 0LL);
        stk.push_back(l);
    }
    void push_line(ll a, ll b) { push_line({a, b}); }
    ll query_bs(ll x) {
        int lf = 0, rg = stk.size() - 1;
        while (lf < rg) {
            int mid = (lf + rg + 1) / 2;
            if (stk[mid].not_start(x)) rg = mid - 1;
            else lf = mid;
        }
        return stk[lf].y(x);
    }
    ll query_linear(ll x) { // x값이 증가하는 순서대로 들어와야함
        while (qptr + 1 < stk.size() && !stk[qptr + 1].not_start(x)) ++qptr;
        return stk[qptr].y(x);
    }
};
