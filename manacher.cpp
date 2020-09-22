void manachers(const char* str, int len, vector<int>& A) // 사용 전 #을 앞뒤로 꼼꼼히 추가하는 것을 잊지 말자
{
    A.resize(len);
    int p = 0;
    for (int i = 0; i < len; ++i)
    {
        if (i <= p + A[p])
            A[i] = min(A[2*p - i], p + A[p] - i);
        else A[i] = 0;
        while(i - A[i] - 1 >= 0 && i + A[i] + 1 < len && str[i - A[i] - 1] == str[i + A[i] + 1])
            ++A[i];
        if(p + A[p] < i + A[i]) p = i;
    }
}
