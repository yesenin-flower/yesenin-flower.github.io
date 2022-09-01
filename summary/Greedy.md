## 买卖股票的最佳时机 II

给定一个数组，它的第 *i* 个元素是一支给定股票第 *i* 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

**注意：**你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

```
输入: [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
```

```cpp
int maxProfit(vector<int>& prices) {
    int max = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] - prices[i-1] > 0) 
          max += prices[i] - prices[i-1];
    }
    return max;
}
```

```cpp
//只能一笔交易时：
//前i天的最大收益 = max{前i-1天的最大收益，第i天的价格-前i-1天中的最小价格}
int maxProfit(vector<int>& prices) {
    if (prices.size()==0) return 0;
    int _m = 0;
    int mins = prices[0];
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] - mins > _m) _m = prices[i] - mins;
        if (prices[i] < mins) mins = prices[i];
    }
    return _m;
}
```

### [Score After Flipping Matrix](https://www.cnblogs.com/grandyang/p/10674440.html)

```cpp
int matrixScore(vector<vector<int>>& A) {
    int m = A.size(), n = A[0].size(), res = (1 << (n - 1)) * m;
    for (int j = 1; j < n; ++j) {
        int cnt = 0;
        for (int i = 0; i < m; ++i) {
            cnt += (A[i][j] == A[i][0]);
        }
        res += max(cnt, m - cnt) * (1 << (n - 1 - j));
    }
    return res;
}
```