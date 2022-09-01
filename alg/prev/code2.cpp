#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int calDigits(int N)
{
    int res = 0;
    while (N != 0)
    {
        res += N % 10;
        N = N / 10;
    }
    return res;
}

int solution(int N)
{
    // write your code in C++14 (g++ 6.2.0)
    int sum_N = calDigits(N) * 2;
    int res = N + 1;
    while (calDigits(res) != sum_N)
    {
        res += 1;
    }
    return res;
}
// 18*2

int main()
{
    cout << (solution(499));
}