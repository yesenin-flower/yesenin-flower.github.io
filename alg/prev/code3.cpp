#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
using namespace std;
bool verify(string &S, int start, int end)
{
    int a = 0, b = 0;
    for (int i = start; i <= end; ++i)
    {
        if (i < 0 || i >= S.length())
            return false;
        if (S[i] == 'a')
            ++a;
        else
            ++b;
    }
    return (a > 0) ^ (b > 0);
}

bool calConsecutive(string &S, int cur)
{
    bool res = verify(S, cur - 2, cur);
    if (res)
        return res;
    res |= verify(S, cur - 1, cur + 1);
    if (res)
        return res;
    res |= verify(S, cur, cur + 2);
    return res;
}

void calNewS(string &S, int cur, vector<int> &dp)
{
    for (int i = cur; i < S.length(); ++i)
    {
        if (calConsecutive(S, i))
        {
            cout << S << " " << i << endl;
            string tmp = "a";
            if (S[i] == 'a')
                tmp = "b";
            string news = S.substr(0, i) + tmp + S.substr(i + 1, S.size() - i - 1);
            cout << news << " " << dp[i] << " " << dp[i + 1] << endl;
            dp[i + 2] = min(dp[i + 1] + 1, dp[i] + 1);
            calNewS(news, i + 1, dp);
            calNewS(S, i + 1, dp);
        }
    }
}

int solution(string &S)
{
    // write your code in C++14 (g++ 6.2.0)
    vector<int> dp(S.length() + 2, 0);
    calNewS(S, 0, dp);
    return dp[S.length() + 1];
}

int main()
{
    string a = "baaaaa";
    cout << solution(a);
}