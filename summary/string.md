# 重复叠加字符串匹配

```cpp
int repeatedStringMatch(string A, string B) {
    int m = A.size(), n = B.size();
    for (int i = 0; i < m; ++i) {
        int j = 0;
        while (j < n && A[(i + j) % m] == B[j]) ++j;
        if (j == n) return (i + j - 1) / m + 1;
    }
    return -1;
}
```

# [重复子串](https://blog.csdn.net/qq_33583069/article/details/51922494)

“KMP算法”，常用于在一个文本串S内查找一个模式串P 的出现位置。

假设现在文本串S匹配到 i 位置，模式串P匹配到 j 位置

1. 如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++，继续匹配下一个字符；
2. 如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]。next 数组各值的含义：代表当前字符之前的字符串中，有多大长度的相同前缀后缀。

```cpp
bool repeatedSubstringPattern(string str) {
    int i = 1, j = 0, n = str.size();
    vector<int> dp(n+1,0);
    while( i < str.size() ){
        if( str[i] == str[j] ) dp[++i]=++j;
        else if( j == 0 ) i++;
        else j = dp[j];
    }
    return dp[n]&&dp[n]%(n-dp[n])==0;
}
```
# 同构字符串

原字符串中的每个字符可由另外一个字符替代，可以被其本身替代，相同的字符一定要被同一个字符替代，且一个字符不能被多个字符替代，即不能出现一对多的映射。

根据一对一映射的特点，我们需要用两个哈希表分别来记录原字符串和目标字符串中字符出现情况，由于ASCII码只有256个字符，所以我们可以用一个256大小的数组来代替哈希表，并初始化为0，我们遍历原字符串，分别从源字符串和目标字符串取出一个字符，然后分别在两个哈希表中查找其值，若不相等，则返回false，若想等，将其值更新为i + 1

```cpp
bool isIsomorphic(string s, string t) {
    int m1[256] = {0}, m2[256] = {0}, n = s.size();
    for (int i = 0; i < n; ++i) {
        if (m1[s[i]] != m2[t[i]]) return false;
        m1[s[i]] = i + 1;
        m2[t[i]] = i + 1;
    }
    return true;
}
```

