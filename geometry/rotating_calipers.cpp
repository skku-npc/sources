#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define x second
#define y first
vector<pii> V;
long long int ccw(pii a, pii b, pii c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}
bool cmp(pii a, pii b) {
    long long int c = ccw(V[0], a, b);
    return c ? c > 0 : a < b;
}
double dis(pii a, pii b) { return hypot(a.x - b.x, a.y - b.y); }
pii operator-(pii a, pii b) { return make_pair(a.y - b.y, a.x - b.x); }
void solve(void) {
    int N;
    scanf("%d", &N);
    V.resize(N);
    for (int i = 0; i < N; ++i)
        scanf("%d%d", &V[i].x, &V[i].y);
    swap(V[0], *min_element(V.begin(), V.end()));
    sort(V.begin() + 1, V.end(), cmp);
    pii S[200010];
    int sz = 0;
    S[sz++] = V[0], S[sz++] = V[1];
    for (int nx = 2; nx < N; S[sz++] = V[nx], ++nx)
        while (sz >= 2 && ccw(S[sz - 2], S[sz - 1], V[nx]) <= 0)
            sz--;
    double ans = 0;
    pii f, g;
    for (int i = 0, j = 1; i < sz; ++i) {
        int ni = (i + 1) % sz;
        int nj = (j + 1) % sz;
        while (1) {
            pii a = {0, 0};
            pii b = S[ni] - S[i];
            pii c = S[nj] - S[j];
            long long int val = ccw(a, b, c);
            double d = dis(S[i], S[j]);
            if (ans < d) {
                ans = d;
                f = S[i];
                g = S[j];
            }
            if (val <= 0)
                break;
            j = (j + 1) % sz;
            nj = (j + 1) % sz;
        }
    }
    printf("%d %d %d %d\n", f.x, f.y, g.x, g.y);
}
int main(void) {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
