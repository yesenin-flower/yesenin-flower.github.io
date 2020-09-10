## [打家劫舍](https://leetcode-cn.com/problems/house-robber/)

每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，**如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警**。

给定一个代表每个房屋存放金额的非负整数数组，计算你**在不触动警报装置的情况下，**能够偷窃到的最高金额。

```
输入: [1,2,3,1]
输出: 4
解释: 偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
```

dp[i] = max(num[i] + dp[i - 2], dp[i - 1])

```cpp
int rob(vector<int>& num) {
    if (num.size() <= 1) return num.empty() ? 0 : num[0];
    
    vector<int> dp = {num[0], max(num[0], num[1])};
    
    for (int i = 2; i < num.size(); ++i) {
        dp.push_back(max(num[i] + dp[i - 2], dp[i - 1]));
    }
    
    return dp.back();
}
```
## 爬楼梯

```cpp
int climbStairs(int n) {
    if ( n == 1) return 1;
    int dp[n];
    dp[0] = 1;
    dp[1] = 2;
    for ( int i = 2; i < n; ++i ) {
        dp[i] = dp[i-2] + dp[i-1];
    }
    return dp[n-1];
}
```
### [1277. Count Square Submatrices with All Ones](https://blog.csdn.net/XX_123_1_RJ/article/details/104131436)

![](https://tva1.sinaimg.cn/large/007S8ZIlgy1gi2txx5gekj309b08zdgj.jpg)

dp\[i][j]的值应该是dp\[i-1][j-1]、 dp\[i-1][j] 和 dp\[i][j-1]三值中的最小的一个 然后 +1

```python
def countSquares(self, A: List[List[int]]) -> int:
        res = 0
        for i in range(len(A)):
            for j in range(len(A[0])):
                if i and j and A[i][j]:
                    A[i][j] = min(A[i - 1][j], A[i][j - 1], A[i - 1][j - 1]) + 1
                res += A[i][j]
        return res
```

