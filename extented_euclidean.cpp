pair<int, int> extended_euclidean(int a, int b)
{
    int s0 = 1, s1 = 0, t0 = 0, t1 = 1, r0 = a, r1 = b;
    while (r1 > 0)
    {
        int temp, q = r0 / r1;
        temp = r0 - q * r1;
        r0 = r1;
        r1 = temp;
        temp = s0 - q * s1;
        s0 = s1;
        s1 = temp;
        temp = t0 - q * t1;
        t0 = t1;
        t1 = temp;
    }
    return {s0, t0};
}
