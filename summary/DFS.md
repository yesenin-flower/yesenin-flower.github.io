### Matchsticks to Square

You are given an integer array `matchsticks` where `matchsticks[i]` is the length of the `ith` matchstick. You want to use **all the matchsticks** to make one square. You **should not break** any stick, but you can link them up, and each matchstick must be used **exactly one time**.

Return `true` if you can make this square and `false` otherwise.

```cpp
class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        int edge = 0;
        for (auto m: matchsticks) edge += m;
        if (edge % 4 != 0) return false;
        edge /= 4;
        
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
                
        return dfs(0, 0, 0, 0, 0, matchsticks, edge);
    }
private:    
    bool dfs(int i, int j, int k, int m, int cur, vector<int>& matchsticks, int edge) {
        if (i == edge && j == edge && k == edge && m == edge) return true;
        if (cur >= matchsticks.size()) return false;
        if (i > edge || j > edge || k > edge || m > edge) return false;
        return dfs(i + matchsticks[cur], j, k, m, cur+1, matchsticks, edge) || dfs(i, j + matchsticks[cur], k, m, cur+1, matchsticks, edge) || dfs(i, j, k + matchsticks[cur], m, cur+1, matchsticks, edge) || dfs(i, j, k, m + matchsticks[cur], cur+1, matchsticks, edge);
    }    
};
```

### 576. Out of Boundary Paths

Recursion with Memoization

```cpp
class Solution {
public:
    int findPaths(int _m, int _n, int _maxMove, int startRow, int startColumn) {
        m = _m, n = _n;
        vector<string> cur;
        memset(memo, -1, sizeof(memo));
        return dfs(startRow, startColumn, _maxMove);
    }
private:
    int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int m, n;
    int memo[51][51][51];
    int M = 1000000007;
    int dfs(int x, int y, int sz) {
        if (x < 0 || x >= m || y < 0 || y >= n) {
            return 1;
        }
        if (sz == 0) return 0;
        if (memo[x][y][sz] >= 0) return memo[x][y][sz];
        int res = 0;
        for (int i = 0; i < 4; ++i) {
            int _x = x+dir[i][0], _y = y+dir[i][1];
            res = (res + dfs(_x, _y, sz-1) % M) % M;
        }
        memo[x][y][sz] = res;
        return res;
    }
};
```

### Combination Sum IV

Given an array of **distinct** integers `nums` and a target integer `target`, return *the number of possible combinations that add up to* `target`.

The test cases are generated so that the answer can fit in a **32-bit** integer.

Basically, I'm checking all possibilities that can be subtracted from target.
To do some Recursion Tree Pruning, I'm using
a) Memoization.
b) Sorting the numbers array. If at any point, I can't subtract a[i] from target, then any number after a[i] can't be used to add upto target.
Hence, break.

```cpp
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<int> dp(target+1, -1);
        return dfs(nums, target, dp);
    }
private:
    int dfs(vector<int>& nums, int target, vector<int>& dp) {
        if (target < 0) return 0;
        if (target == 0) return 1;
        //cout<<target<<endl;
        if (dp[target] != -1) return dp[target];
        int ans = 0;
        for (auto n: nums) {
            if(target < n) break;
            ans += dfs(nums, target - n, dp);
        }
        //cout<<target<<" "<<ans<<endl;
        dp[target] = ans;
        return ans;
    }
};
```

