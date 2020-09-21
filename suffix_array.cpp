//모두 0based index
void get_sa(char*s, int n, vector<int>& sa) {
    sa.resize(n);
    int m = 26;
    vector<int> cnt(max(n, m), 0), x(n, 0), y(n, 0);
    forn(i, n) cnt[x[i]=s[i]-'a']++;
    forn(i, m-1) cnt[i+1] += cnt[i];
    for(int i=n-1;i>=0;--i) sa[--cnt[x[i]]] = i;
    for (int len = 1, p = 0; p + 1 < n; len<<=1, m = p+1) {
        p = 0;
        for (int i = n - len;i<n;++i) y[p++] = i;
        forn(i, n) if (sa[i] >= len) y[p++] = sa[i] - len;
        
        forn(i, m) cnt[i] = 0;
        forn(i, n) cnt[x[i]]++;
        forn(i, m-1) cnt[i+1] += cnt[i];
        for (int i=n-1;i>=0;--i) sa[--cnt[x[y[i]]]] = y[i];
        y = x; p = 0; x[sa[0]] = 0;
        forn(i, n-1) {
            x[sa[i+1]] = sa[i]+len<n && sa[i+1]+len<n && y[sa[i]] == y[sa[i+1]] && y[sa[i]+len] == y[sa[i+1]+len]?p:++p;
        }
    }

}
void get_lcp(char*s, int n, vector<int>& sa, vector<int>& lcp) {
    lcp.resize(n);
    vector<int> rank(sz(sa));
    forn(i, n) rank[sa[i]]=i;
    int k = 0, j;
    for(int i=0;i<n;lcp[rank[i++]]=k) {
        if (rank[i]-1>=0)
            for(k?k--:0, j=sa[rank[i]-1];s[i+k]==s[j+k];++k);
    }
}
