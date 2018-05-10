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
