//persistent segTree
struct vertex {
    int l, r, val;
};
int head[100'010]; // i번째 segTree의 root를 나타낸다.
vector<vertex> pst;
//head조작과 0번 segTree만들기는 직접 한다.
//segTree를 생성한다. 0 번째 세그트리는 재활용해줄게 없음으로 필요하다.
void init(int ns, int ne, int nx) {
    if (ns == ne) return;
    int mid = (ns + ne) / 2;
    pst[nx].l = sz(pst);
    pst.pb({-1,-1,0});
    pst[nx].r = sz(pst);
    pst.pb({-1,-1,0});
    init(ns, mid, pst[nx].l);
    init(mid+1, ne, pst[nx].r);
}
//재활용 불가능한 쪽만 파고 들어가서 새로운 노드를 생성, 나머지는 다 재활용한다. root는 손코딩
void update(int ns, int ne, int nx, int idx, int df) {
    if (ns == ne) return;
    int mid = (ns + ne) / 2;
    if (idx <= mid) {
        int lx = pst[nx].l;
        pst[nx].l = sz(pst);
        pst.pb({pst[lx].l,pst[lx].r, pst[lx].val + df});//
        update(ns, mid, pst[nx].l, idx, df);
    }
    else {
        int rx = pst[nx].r;
        pst[nx].r = sz(pst);
        pst.pb({pst[rx].l,pst[rx].r, pst[rx].val + df});//
        update(mid + 1, ne, pst[nx].r, idx, df);
    }
}
int get_sum(int ns, int ne, int nx, int qs, int qe) {
    if (ns > qe || qs > ne) return 0;
    if (qs <= ns && ne <= qe) return pst[nx].val;
    int mid = (ns + ne) / 2;
    return get_sum(ns, mid, pst[nx].l, qs, qe) + get_sum(mid + 1, ne, pst[nx].r, qs, qe);
}
