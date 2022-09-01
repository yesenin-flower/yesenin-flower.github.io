#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int solution(vector<int> &A)
{
    int res = 1;
    for (auto a : A)
    {
        if (a == 0)
            return 0;
        res *= (a > 0 ? 1 : -1);
    }
    return res;
}

int main()
{
    vector<int> A = {1, -2, -3, -5, 0};
    cout << solution(A);
}
