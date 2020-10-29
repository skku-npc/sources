void manacher(const char* str, int len, vector<int>& a) {  // 사용 전 문자 앞뒤로 # 추가하기
    a.resize(len);
    int p = 0;
    for (int i = 0; i < len; ++i) {
        if (i <= p + a[p])
            a[i] = min(a[2 * p - i], p + a[p] - i);  // 점 p를 기준으로 대칭
        else
            a[i] = 0;
        while (i - a[i] - 1 >= 0 && i + a[i] + 1 < len && str[i - a[i] - 1] == str[i + a[i] + 1])  // 확장
            ++a[i];
        if (p + a[p] < i + a[i]) p = i;  // p = 최대 커버
    }
}
