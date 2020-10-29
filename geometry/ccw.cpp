struct P {
    int x, y;
    int s() { return this->x + this->y; }
};

struct L {
    L() {}
    L(const P &a, const P &b) : a(a), b(b) {}
    P a, b;
};

int ccw(const P &a, const P &b, const P &c) {
    int k = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if (k > 0) return 1;
    if (k) return -1;
    return 0;
}

int insc(L p, L q) {
    if (!ccw(p.a, p.b, q.a) && !ccw(p.a, p.b, q.b)) {
        if (p.a.s() > p.b.s()) swap(p.a, p.b);
        if (q.a.s() > q.b.s()) swap(q.a, q.b);
        int a = p.a.s(), b = p.b.s(), c = q.a.s(), d = q.b.s();
        if (b < c || d < a) return 0;
        if (b == c || a == d) return 1;
        return -1;
    }
    if (ccw(p.a, p.b, q.a) == ccw(p.a, p.b, q.b) ||
        ccw(q.a, q.b, p.a) == ccw(q.a, q.b, p.b))
        return 0;
    return 1;
}
