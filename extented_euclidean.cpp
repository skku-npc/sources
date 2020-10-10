pair<int, int> extended_euclidean(int a, int b) {
    int s = 1, ss = 0, t = 0, tt = 1, r0 = a, r1 = b, q;
    while (r1 > 0) {
        q = r0 / r1;
        tie(r0, r1) = make_tuple(r1, r0 - q * r1);
        tie(s, ss) = make_tuple(ss, s - q * ss);
        tie(t, tt) = make_tuple(tt, t - q * tt);
    }
    return {s, t};
}
