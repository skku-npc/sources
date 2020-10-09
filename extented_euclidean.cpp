pair<int, int> extended_euclidean(int a, int b) {
    int s0 = 1, s1 = 0, t0 = 0, t1 = 1, r0 = a, r1 = b, q, r, s, t;
    while (r1 > 0) {
        q = r0 / r1;
        r = r0 - q * r1; r0 = r1; r1 = r;
        s = s0 - q * s1; s0 = s1; s1 = s;
        t = t0 - q * t1; t0 = t1; t1 = t;
    }
    return {s0, t0};
}


