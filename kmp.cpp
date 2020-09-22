//문자열 길이 >= 1
void get_fail(const char* p, int len, vector<int>& fail)//xxxa..xxx f[end of x] => a, //0based
{
    fail.resize(len);
    fail[0] = 0;
    for (int i = 1, j = 0; i < len; ++i)
    {
        while(j && p[i] != p[j]) j = fail[j-1];
        if (p[i] == p[j]) fail[i] = ++j;
    }
}
void KMP(const char* text, int tlen, const char* pattern, int plen, vector<int>& fail, vector<int>& ans) //0based
{
    ans.clear();
    for (int i = 0, j = 0; i < tlen; ++i)
    {
        while(j && text[i] != pattern[j]) j = fail[j-1];
        if (text[i] == pattern[j])
        {
            if (j == plen - 1)
            {
                ans.push_back(i - j);
                j = fail[j];
            } else ++j;
        }
    }
}
