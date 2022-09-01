### 个数

子序列 subsequence 总个数O(2^n) A **subsequence** is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

子字符串 substring 总个数O(n^2)

### 最长子回文串substring

#### N^3

1. 两个for循环，分别是left和right，第三层封装一个回文串的判定
2. 一个for循环确定长度0->n，第二个for确定left，第三层封装一个回文串的判定

#### N^2

先想暴力的方式，什么部分被浪费了

##### 中心线枚举

当知道bcb以后，abcba只需要判断两端即可，因此中间点最重要

中间点有两种可能：

1. 奇数长度的回文串有n个
2. 偶数长度的回文串有n-1个

因此对于每一个char cur，写两种情况：

1. left=right=cur, 判断回文串
2. left=cur, right=cur+1, 判断回文串

##### 动态规划

dp\[i][j]是回文串 => dp\[i][j] = dp\[i+1][j-1] && (s[i] == s[j])

初始化：

1. 所有的对角线都是true
2. 所有dp\[i][i-1]都是true，因为这个相当于空字符串
3. 因为是i+1，j-1所以循环应该是i = [n-1, 0]; j = [i+1, n-1]

### 回文数字

```cpp
bool isPalindrome(int x) {
    if (x < 0) return false;
    int res = 0, tmp = x;
    while (tmp != 0) {
        if (res > INT_MAX / 10) return false;//注意溢出
        res = res * 10 + (tmp % 10);
        tmp /= 10;
    }
    return res == x;
}
```
### 回文子串subsequence

动态规划

如果s[i] == s[j]，那么当前最长的subsequence: dp\[i][j] = dp\[i+1][j-1] + 2

否则，最长dp\[i][j] = max(dp\[i][j-1] ,dp\[i+1][j])

```cpp
    int longestPalindromeSubseq(string s) {
        int len = s.size();
        int dp[len][len];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < len; ++i) {
            dp[i][i] = 1;
            //dp[i][i-1] = 1;空字符串长度为0
        }
            
        
        for (int i = len-1; i >= 0; --i) {
            for (int j = i+1; j < len; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
                //cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
            }
        }
        return dp[0][len-1];
    }
```

### Unique Length-3 Palindromic Subsequences

问题的关键是找到i到j中间unique的char的个数

用最简单的方式，循环即可。

先找到26个字母对应的首位，这样循环不需要按字符串长度循环

时间复杂度为n + 26*n（还可以用二分法查找，速度更快）

```cpp
int countPalindromicSubsequence(string s) {
    int m = s.size();
    unordered_map<int, vector<int>> locs;
    for (int i = 0; i < m; ++i) {
        locs[s[i] - 'a'].push_back(i);
    }
    int res = 0;
    for (auto loc: locs) {
        //cout<<loc.first<<endl;
        if (loc.second.size() < 2) continue;
        int left = loc.second[0], right = loc.second.back();
        //cout<<loc.first<<" "<<left<<" "<<right<<endl;
        int uniques = 0;
        for (auto chars:locs) {
            for (auto idx: chars.second) {
                if (idx > left && idx < right) {
                    uniques += 1;
                    break;
                }
            }
        }
        //cout<<uniques<<endl;
        res += uniques;
    }
    return res;
}
```