### [打家劫舍](https://leetcode-cn.com/problems/house-robber/)

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

设 `dp[i][j]`表示以 `A[i][j]`为右下角组成的`正方形个数总和`

显然`dp[i][j]`的值`dp[i-1][j-1]`、 `dp[i-1][j]` 和 `dp[i][j-1]`（分别是：左上角、左边、上边）三个值有关

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

###  Interleaving String

1. 记住已经查过的字符串，递归
2. DP: 可以只记录前一行
   1. dp\[0][0] = true; 
   2. dp\[0][j] = dp\[0][j-1]&&s2\[j-1]==s3[i+j-1]; 
   3. dp\[i][0] = dp\[i-1][0]&&s1\[i-1]==s3[i+j-1];
   4. dp\[i][j] = (dp\[i-1][j]&&s1\[i-1]==s3[i+j-1]) || (dp\[i][j-1]&&s2\[j-1]==s3[i+j-1])

```cpp
public:
    bool isInterleave(string s1, string s2, string s3) {
        vector<vector<int>> memo(s1.size(), vector<int>(s2.size(), -1));
        return helper(s1, s2, s3, 0, 0, 0, memo);
    }
private:
    //method recursion
    bool helper(string s1, string s2, string s3, int l1, int l2, int l3, vector<vector<int>>& memo) {
        if (l2 == s2.size() &&  l1 < s1.size()) {
            //cout<<"1 "<<s1.size()-l1<<" "<<s3.size()-l3<<endl;
            if (s1.size()-l1 != s3.size()-l3) return false;
            return s1.substr(l1, s1.size()-l1) == s3.substr(l3, s3.size()-l3);
        } else if (l1 == s1.size() &&  l2 < s2.size()) {
            //cout<<"2 "<<s2.size()-l2<<" "<<s3.size()-l3<<endl;
            if (s2.size()-l2 != s3.size()-l3) return false;
            return s2.substr(l2, s2.size()-l2) == s3.substr(l3, s3.size()-l3);
        } else if (l3 == s3.size()){
            return l2 == s2.size() && l1 == s1.size();
        } else if (l2 == s2.size() && l1 == s1.size()) return false;
        
        if (memo[l1][l2] >= 0) {
            return memo[l1][l2] == 1 ? true : false;
        }
        bool res = false;
        if (s3[l3] == s1[l1] && s3[l3] != s2[l2]){
            res |= helper(s1, s2, s3, l1+1, l2, l3+1, memo);
        }
        else if (s3[l3] != s1[l1] && s3[l3] == s2[l2]) {
            res |= helper(s1, s2, s3, l1, l2+1, l3+1, memo);
        }
        else if (s3[l3] == s2[l2] && s3[l3] == s1[l1]) {
            res |= helper(s1, s2, s3, l1+1, l2, l3+1, memo);
            if (res) return res;
            res |= helper(s1, s2, s3, l1, l2+1, l3+1, memo);
        }
        memo[l1][l2] = res ? 1 : 0;
        return res;
    }

```

##[Maximum Side Length of a Square with Sum Less than or Equal to Threshold]()

```cpp
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();
        if (m == 0) return 0;
        int n = mat[0].size();
        if (n == 0) return 0;
        
        int presum[m+1][n+1];
        memset(presum, 0, sizeof(presum));
        for (int i = 1; i<= m; ++i)
            for (int j = 1; j <= n; ++j) 
                presum[i][j] = presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1] + mat[i-1][j-1];
                
        
        for (int len = min(m, n); len >= 1; len--) {
            for (int i = 1; i + len <= m; i++) {
                for (int j = 1; j + len <= n; j++) {
                    if (presum[i + len][j + len] - presum[i - 1][j + len] - presum[i + len][j - 1] + presum[i - 1][j - 1] <= threshold) {
                        return len + 1;
                    }
                }
            }
        }
        return 0;
    }
```

##[Uncrossed Lines](https://www.youtube.com/watch?v=duCx_62nMOA)

dp\[i\]\[j\] A中取i个B中取j个 

```cpp
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(A[i-1] == B[j-1]) dp[i][j] = max(dp[i][j], 1+dp[i-1][j-1]);
                dp[i][j] = max({dp[i][j], dp[i-1][j], dp[i][j-1]});
            }
        }
        return dp[n][m];
    }
```

```cpp
class Solution {
public:
    int dp[500][500];
    
    int helper(int i, int j, vector<int> &A, vector<int> &B){
        if(i == A.size() || j == B.size()) return 0;
        
        if(dp[i][j] != -1) return dp[i][j];
        
        int ans = 0;
        
        if(A[i] == B[j]) ans = max(ans, 1+helper(i+1, j+1, A, B));
        ans = max(ans, helper(i+1, j, A, B));
        ans = max(ans, helper(i, j+1, A, B));
        
        return dp[i][j] = ans;
    }
    
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        memset(dp, -1, sizeof(dp));
        
        int n = A.size(), m = B.size();
        
        return helper(0, 0, A, B);
    }
};
```

### [1481. Least Number of Unique Integers after K Removals](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/)

For future readers:
If I am holding a share after today, then either I am just continuing holding the share I had yesterday, or that I held no share yesterday, but bought in one share today: `hold = max(hold, cash - prices[i])`
If I am not holding a share after today, then either I did not hold a share yesterday, or that I held a share yesterday but I decided to sell it out today: `cash = max(cash, hold + prices[i] - fee)`.
Make sure `fee` is only incurred once.

```cpp
int maxProfit(vector<int>& prices, int fee) {
        int cash = 0, hold = -prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            cash = max(cash, hold+prices[i]-fee);
            hold = max(hold, cash-prices[i]);
        }
        return cash;
    }
```

### [Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

For future readers:
If I am holding a share after today, then either I am just continuing holding the share I had yesterday, or that I held no share yesterday, but bought in one share today: `hold = max(hold, cash - prices[i])`
If I am not holding a share after today, then either I did not hold a share yesterday, or that I held a share yesterday but I decided to sell it out today: `cash = max(cash, hold + prices[i] - fee)`.
Make sure `fee` is only incurred once.

```cpp
    int maxProfit(vector<int>& prices, int fee) {
        //dfs(prices, fee, 0, -1, 0);
        //return maxs;
        int cash = 0, hold = -prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            cash = max(cash, hold+prices[i]-fee);
            hold = max(hold, cash-prices[i]);
        }
        return cash;
    }

#OR

    int maxs = 0;
    void dfs(vector<int>& prices, int fee, int cur, int brought,  int profit) {
        if (cur >= prices.size()) {
            maxs = max(profit, maxs);
            return;
        }
        for (int i = cur; i < prices.size(); ++i) {
            if (brought == -1) {
                dfs(prices, fee, i + 1, i, profit);
            } else {
                dfs(prices, fee, i + 1, -1, profit-fee + prices[i] - prices[brought]);
            }
        }
    }
```

### [Count Sorted Vowel Strings](https://leetcode.com/problems/count-sorted-vowel-strings/)

```cpp
    //1,1:1; 2,1:2; 3,1:3; 4,1:4; 5,1:5;  => 15
    //1,2:1; 2,2:3; 3,2:6; 4,2:10; 5,2:15  => 35
    int countVowelStrings(int n) {
        vector<int64_t> cnt(5, 1);
        for (int i = 1; i < n; i++)
          for (int j = 3; j >= 0; j--) cnt[j] += cnt[j + 1];
        return accumulate(cnt.begin(), cnt.end(), 0);
    }
```

```cpp
//因为n上限是51 可以开一个数组[51][5]
int countVowelStrings(int n) {
  int dp[51][5];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < 5; ++i) dp[0][i] = 1;
  for (int i = 1; i < n; ++i) 
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k <= j; ++k) {
        dp[i][j] += dp[i-1][k];
      }
    }


  int res = 0;
  for (int i = 0; i < 5; ++i) {
    cout<<dp[n-1][i]<<endl;
    res += dp[n-1][i];
  }
  return res;
}
```

###[Maximum Length of Repeated Subarray](https://leetcode.com/problems/maximum-length-of-repeated-subarray/solution/)

```cpp
int findLength(vector<int>& A, vector<int>& B) {
        int dp[A.size()+1][B.size()+1];
        memset(dp, 0, sizeof(dp));
        for (int i = A.size()-1; i > -1; --i) {
            for (int j = B.size()-1; j > -1; --j) {
                if(A[i] == B[j]) {
                    dp[i][j] = dp[i+1][j+1]+1;
                    maximum = max(maximum, dp[i][j]);
                }
            }
        }
 }
```

###[Minimum Cost Tree From Leaf Values]()

```
Input: arr = [6,2,4]
Output: 32
Explanation:
There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4
```

尽量保证大数被乘的次数少

###[Partition Array for Maximum Sum]()

![](https://tva1.sinaimg.cn/large/008eGmZEly1gmnmabw463j318w0man85.jpg)

```cpp
int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int dp[arr.size()+1];
    memset(dp,0,sizeof(dp));
    for (int i = 0; i < arr.size(); ++i) {
        int tmp = INT_MIN;
        for (int j = 0; j < k && i-j >= 0; ++j) {
            tmp = max(tmp, arr[i-j]);
            dp[i+1] = max(dp[i+1], dp[i-j] + tmp*(j+1));
        }
        //cout<<i+1<<" "<<tmp<<" "<<dp[i+1]<<endl;
    }
    return dp[arr.size()];
}
```
###[Longest Palindromic Substring]()

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0;
        int _max = 0;
        for (int i = 0; i < s.size(); ++i) {
            int len = max(getlen(i, i, s), getlen(i, i+1, s));
            //cout<<len<<endl;
            if (len > _max) {
                _max = len;
                start = i - (len - 1) / 2;
                //cout<<start<<" "<<len<<endl<<endl;
            }
        }
        return s.substr(start, _max);
    }
private:
    int getlen(int i, int j, string s) {
        while (i >= 0 && j < s.size() && s[i] == s[j]) {
            --i; ++j;
        }
        //cout<<j<<" "<<i<<endl;
        return j - i - 1;
    }
};
```

### Stone Game

自己最大，对手最小，就是让自己和对手的相对分数最大

![](https://tva1.sinaimg.cn/large/008i3skNgy1gr1yw9myqpj318s0om15y.jpg)

dp\[i][j]是从i到j自己能取的相对最大值,按长度沿着对角线降维

|      | 0    | 1               | 2     | 3    |
| ---- | ---- | --------------- | ----- | ---- |
| 0    | 5    | Max(5-3, 3-5)=2 |       |      |
| 1    |      | 3               | Max() |      |
| 2    |      |                 | 4     |      |
|      |      |                 |       | 5    |

2. Stone Game VII

   There are `n` stones arranged in a row. On each player's turn, they can **remove** either the leftmost stone or the rightmost stone from the row and receive points equal to the **sum** of the remaining stones' values in the row. The winner is the one with the higher score when there are no stones left to remove.

   Bob found that he will always lose this game (poor Bob, he always loses), so he decided to **minimize the score's difference**. Alice's goal is to **maximize the difference** in the score.

```cpp
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int sum = 0;
        for (auto s: stones) sum+=s;
        vector<vector<int>> checked(stones.size(), vector<int>(stones.size(), -1));
        return score(stones, checked, 0, stones.size()-1, sum);
    }
private:
    int score(vector<int>& piles, vector<vector<int>>& checked, int l, int r, int sum) {
        if (l >= r) return 0;
        int tmp1 = checked[l+1][r], tmp2 = checked[l][r-1];
        if (tmp1 == -1) {
            tmp1 = score(piles, checked, l+1, r, sum-piles[l]);
            checked[l+1][r] = tmp1;
        }
        if (tmp2 == -1) {
            tmp2 = score(piles, checked, l, r-1, sum-piles[r]);
            checked[l][r-1] = tmp2;
        }
        return max(sum-piles[l] - tmp1, sum-piles[r] - tmp2);
    }
};
```

## 加油

A more intuitive state definition could be: `"dp[i][j] = at station i, the farthest distance someone can get by making j stops."` transition function: `dp[i][j] = max( dp[i - 1][j - 1] + station i's fuel, dp[i - 1][j]) for j = 1 to j = i`

since we only look back for 1 element, we can optimize the dp from [i][j] to dp[j], thus getting the approach 1

on the other hand, approach 2 optimize `for j = 1 to j = i` loop away by using Heap.

```cpp
int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
  int N = stations.size();
  long dp[N + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = startFuel;
  for (int i = 0; i < N; ++i)
    for (int t = i; t >= 0; --t)
      if (dp[t] >= stations[i][0])
        dp[t+1] = max(dp[t+1], dp[t] + (long) stations[i][1]);

  for (int i = 0; i <= N; ++i)
    if (dp[i] >= target) return i;
  return -1;
}
```

## 左上角到右下角的总路径

```cpp
int uniquePaths(int m, int n) {
  int dp[m][n];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  int dir[][2] = {{0,-1},{-1,0}};
  for (int i =0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < 2; ++k) {
        int r = dir[k][0] + i, c= dir[k][1]+j;
        if(r >=0 && c>=0 && r<m && c<n) {
          dp[i][j] += dp[r][c];
        }
      }
      //cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
    }
  }
  return dp[m-1][n-1];
}
```

