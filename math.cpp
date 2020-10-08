int MOD = 998244353;
int power(int a, int n){
    int res = 1;
    int now = a;
    while(n) {
        if (n&1) res  = (res*now) %MOD;
        n>>=1;
        now = (now*now)%MOD;
    }
    return res;
}
int inv(int a) {
    return power(a, MOD-2);
}
int C(int n, int r) {
    if (n < r) return 0;
    return fact[n] %MOD * inv(fact[n-r])%MOD * inv(fact[r])%MOD;
}
