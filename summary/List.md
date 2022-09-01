## Presum

#### Maximum Absolute Sum of Any Subarray

求presum，presum中的最大值-最小值的绝对值

####Minimun Absolute Sum of Any Subarray 

求presum，排序presum，两个相邻的presum差的最小值

## 旋转数组

将包含* n* 个元素的数组向右旋转 *k *步。

例如，如果  *n* = 7 ,  *k* = 3，给定数组  `[1,2,3,4,5,6,7]`  ，向右旋转后的结果为 `[5,6,7,1,2,3,4]`。

前n-k个reverse，后k个reverse`[4,3,2,1,7,6,5]`

再全局reverse

## HASHTABLE

如果要求index，就用hashtable做。

| 题号   | 题名           |
| :--- | ------------ |
| 1    | 两数之和         |
| 532  | 数组中的K-diff数对 |
| 18   | 四数之和         |
|      |              |

## 数组最长公共前缀

```
输入: ["flower","flow","flight"]
输出: "fl"
```

先排序，第一个和最后一个元素的相同前缀就是整个数组的最长公共前缀

## 删除排序数组中的重复项+移除某个元素+移动零

```cpp
int removeDuplicates(vector<int>& nums) {
    if (nums.size()==0) return 0;
    int cur = 0;
    for (int i=1; i<nums.size(); ++i) {
        if (nums[i] != nums[cur]) nums[++cur] = nums[i];
    }
    return cur+1;
}
```
## 合并有序数组

从后往前合并。

```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int len = m + n - 1;
    while ( i >= 0 && j >= 0 ) {
        if ( nums1[i] > nums2[j] ) nums1[len--] = nums1[i--];
        else nums1[len--] = nums2[j--];
    }
    while ( j >= 0 ) {
        nums1[len--] = nums2[j--];
    }
}
```

## 修改一个值得到非递减数列

在出现 nums[i] < nums[i - 1] 时，需要考虑的是应该修改数组的哪个数，使得本次修改能使 i 之前的数组成为非递减数组，并且 **不影响后续的操作**。

优先考虑令 nums[i - 1] = nums[i]，因为如果修改 nums[i] = nums[i - 1] 的话，那么 nums[i] 这个数会变大，那么就有可能比 nums[i + 1] 大，从而影响了后续操作。

还有一个比较特别的情况就是 nums[i] < nums[i - 2]，只修改 nums[i - 1] = nums[i] 不能令数组成为非递减，只能通过修改 nums[i] = nums[i - 1] 才行。

```cpp
public boolean checkPossibility(int[] nums) {
    int cnt = 0;
    for(int i = 1; i < nums.length; i++){
        if(nums[i] < nums[i - 1]){
            cnt++;
            if(i - 2 >= 0 && nums[i - 2] > nums[i]) 
              	nums[i] = nums[i-1];
            else nums[i - 1] = nums[i];
        }
    }
    return cnt <= 1;
}
```
## [Shortest Unsorted Continuous Subarray](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/)

Given an integer array, you need to find one **continuous subarray** that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the **shortest** such subarray and output its length.

先排序，找不同

方法二：

分三步骤：1）分别从左和从右，找出第一个非增/非降的位置left和right；2）在区间[left, right]之内找到最大值lmax和最小值rmin；3）将区间[left, right]分别向左和向右扩展，直到其左边的第一个数小于rmin，其右边的第一个数大于lmax。扩展后的区间[left, right]的长度就是题目所求。算法的时间复杂度是O(n)，空间复杂度是O(1)。

方法三：
使用栈 s 来维持一个递增或递减序列的下标，区间的上下界分别用 start 和 end 记录。

先从左往右遍历一次数组 nums 以确定目标区间的下界，对每一个元素 nums[i]，比较栈顶对应的数组元素 nums[s.top()] 是否大于 nums[i]，若大于则更新 start = min(start, s.top()) 并出栈，重复直到栈为空或 nums[s.top()] <= nums[i]，将当前下标 i 入栈。这样遍历完一次后，start 的值就变成目标区间的上界了。

在对数组从右往左遍历一次，用类似的方法可以确定目标区间的下界 end。

### [Maximum Sum of Two Non-Overlapping Subarrays](https://blog.csdn.net/MrJustin/article/details/105609570)

```cpp
class Solution {
   public int maxSumTwoNoOverlap(int[] A, int L, int M) {
        for (int i = 1; i < A.length; ++i)
            A[i] += A[i - 1]; 
        int res = A[L + M - 1], Lmax = A[L - 1], Mmax = A[M - 1];
        for (int i = L + M; i < A.length; ++i) {
          //L在左侧
            Lmax = Math.max(Lmax, A[i - M] - A[i - M - L]);
          //M在左侧
            Mmax = Math.max(Mmax, A[i - L] - A[i - L - M]);
            res = Math.max(res, Math.max(Lmax + A[i] - A[i - M], Mmax + A[i] - A[i - L]));
        }
        return res;
    }
}
```



## [找到所有数组中消失的数字](https://www.cnblogs.com/grandyang/p/6222149.html)

```cpp
vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != nums[nums[i] - 1]) {
            swap(nums[i], nums[nums[i] - 1]);
            --i;
        }
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != i + 1) {
            res.push_back(i + 1);
        }
    }
    return res;
}
```
## [最小移动次数使数组元素相等](https://www.cnblogs.com/grandyang/p/6053827.html)

```cpp
int minMoves(vector<int>& nums) {
    int mn = INT_MAX, res = 0;
    for (int num : nums) mn = min(mn, num);
    for (int num : nums) res += num - mn;
    return res;
}
```

```cpp
int minMoves(vector<int>& nums) {
    int mn = INT_MAX, sum = 0, res = 0;
    for (int num : nums) {
        mn = min(mn, num);
        sum += num;
    }
    return sum - mn * nums.size();
}
```

## 子数组最大平均数

```cpp
double findMaxAverage(vector<int>& nums, int k) {
    int before = 0;
    for (int i = 0; i < k; ++i) {
        before += nums[i];
    }
    double maxs = before;
    for (int i = k; i < nums.size(); ++i) {
        before = before - nums[i - k] + nums[i];
        if (maxs < before) maxs = before;
    }
    return maxs / k;
}
```
## [供暖器](https://leetcode-cn.com/problems/heaters/)

```cpp
int findRadius(vector<int>& houses, vector<int>& heaters) {
    sort(houses.begin(), houses.end());
    sort(heaters.begin(),heaters.end());
    
    int i = 0, index = 0, max_dis = 0;
    while (i < houses.size() && index < heaters.size()) {
        while (index + 1 < heaters.size() && (abs(heaters[index+1] - houses[i]) <= abs(heaters[index] - houses[i]))) {
            index++;
        }
        max_dis = max(max_dis, abs(heaters[index] - houses[i]));
        ++i;
    }
    return max_dis;
}
```
## 相对名次

```cpp
vector<string> findRelativeRanks(vector<int>& nums) {
    vector<int> rank;
    for(int i=0; i<nums.size(); ++i) rank.push_back(i);

    sort(rank.begin(), rank.end(), [&](int a, int b){return nums[a] > nums[b];});
    vector<string> ranks(nums.size());

    for(int i=3; i<nums.size(); ++i){
        ranks[rank[i]] = std::to_string(i+1);
    }

    if(nums.size() > 0) ranks[rank[0]] = "Gold Medal";
    if(nums.size() > 1) ranks[rank[1]] = "Silver Medal";
    if(nums.size() > 2) ranks[rank[2]] = "Bronze Medal";

    return ranks;
}
```
## 寻找数组的中心索引

```cpp
int pivotIndex(vector<int>& nums) {
    int n = nums.size();
    int sum = 0;
    for(int ii = 0; ii < n; ii ++) {
        sum += nums[ii];
    }
    int leftSum = 0;
    int rightSum = sum;
    for(int ii = 0; ii < n; ii ++) {
        leftSum += ii > 0 ? nums[ii - 1] : 0;
        rightSum -= nums[ii];
        if(leftSum == rightSum) {
            return ii;
        }
    }
    return -1;
}
```
## 词典中最长的单词

```cpp
string longestWord(vector<string>& words) {
    unordered_set<string> s;
    for (auto w : words) {
        s.insert(w);
    }
    string res = "";
    for (auto w : words){
        bool check = true;
        for (int i = 1 ; i < w.size(); ++i) {
            if (s.find(w.substr(0, i)) == s.end()) {
                check = false;
                break;
            }
        }
        if (check && (res.size() < w.size() || (res.size() == w.size() && w < res))) {
            res = w; 
        }
        
    }
    
    return res;
}
```
## 最短无序连续子数组

```cpp
int findUnsortedSubarray(vector<int>& nums) {
    vector<int > nums2(nums);
    sort(nums2.begin(), nums2.end());
    
    int begin = 0, end = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != nums2[i]) {
            begin = i;
            break;
        }
    }
    for (int i = nums.size() - 1; i >= 0; --i) {
        if (nums[i] != nums2[i]) {
            end = i;
            break;
        }
    }
    return end == 0? 0 : end - begin + 1;
}
```
## 最长和谐子序列

```cpp
int findLHS(vector<int>& nums) {
    map<int, int> mp;
    for (int n : nums) {
        if (mp.find(n) == mp.end()) mp[n] = 1;
        else  ++mp[n];
    }
    int max = 0;
    for (auto p : mp) {
        int key = p.first;
        if (mp.find(key - 1) == mp.end()) continue;
        else if (max < mp[key-1] + mp[key]) max = mp[key-1] + mp[key];
        if (mp.find(key + 1) == mp.end()) continue;
        else if (max < mp[key+1] + mp[key]) max = mp[key+1] + mp[key];
    }
    return max;
}
```

## 全排列

```cpp
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> tmp;
    bool used[nums.size()];
    fill(used, used+nums.size(), false);
    dfs(nums,  used, tmp, res);
    return res;
}
void dfs(vector<int>& nums, bool used[], vector<int> tmp, vector<vector<int>>& res) {
    if (tmp.size() >= nums.size()) {
        res.push_back(tmp);
        return;
    }
    
    for (int i = 0; i < nums.size(); ++i) {
        if (!used[i]) {
            tmp.push_back(nums[i]);
            used[i] = 1;
            dfs(nums, used, tmp, res);
            tmp.pop_back();
            used[i] = 0;
        }
    }
}
```
```cpp
vector<vector<int> > permuteUnique(vector<int> &num) {
    vector<vector<int> > res;
    vector<int> out;
    vector<int> visited(num.size(), 0);
    sort(num.begin(), num.end());
    permuteUniqueDFS(num, 0, visited, out, res);
    return res;
}
void permuteUniqueDFS(vector<int> &num, int level, vector<int> &visited, vector<int> &out, vector<vector<int> > &res) {
    if (level >= num.size()) res.push_back(out);
    else {
        for (int i = 0; i < num.size(); ++i) {
            if (visited[i] == 0) {
                if (i > 0 && num[i] == num[i - 1] && visited[i - 1] == 0) continue;
                visited[i] = 1;
                out.push_back(num[i]);
                permuteUniqueDFS(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
            }
        }
    }
}
```
## 子集

```cpp
void dfs(vector<int>& nums, vector<vector<int>>& res, vector<int> tmp, int index) {
    if (index >= nums.size()) return;
  
    dfs(nums, res, tmp, index + 1);          
    tmp.push_back(nums[index]);
    res.push_back(tmp);
    dfs(nums, res, tmp, index+ 1);

    return;
}
```

## 组合总和

1. 当前数字能不能重复使用
2. 数组是不是distinct number， 返回数组如何去重

```cpp
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> item;
    dfs(candidates,target,0,item,res);
    return res;
}
//candidates无重复数，且每个candidate可重复
void dfs(vector<int>& candidates, int target, int start, vector<int> item, vector<vector<int>>& res) {
    if (target < 0) return;
    else if (target == 0) {
        res.push_back(item);
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        item.push_back(candidates[i]);
        dfs(candidates, target - candidates[i], i, item, res);
        item.pop_back();
    }
}
//candidates有重复数，且每个candidate不可重复
void dfs2(vector<int>& candidates, int target, int start, vector<int> item, vector<vector<int>>& res) {
    if (target < 0) return;
    else if (target == 0) {
        res.push_back(item);
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        //同一层中，后面的数和前面相同的时候，会出现重复，直接continue
        if (i != start && candidates[i] == candidates[i-1])
            continue;
        item.push_back(candidates[i]);
        dfs(candidates, target - candidates[i], i+1, item, res);
        item.pop_back();
    }
}
```
## [下一个排列](https://blog.csdn.net/NoMasp/article/details/49913627)

```cpp
void nextPermutation(vector<int>& nums) {
    int index = nums.size() - 1;
    while(nums[index] <= nums[index-1]) {
        --index;
    }
    if(index == 0) {
        sort(nums.begin(), nums.end());
        return ;
    }
    int second = INT_MAX, secondIndex = INT_MAX;
    for(int i = nums.size() - 1; i >= index - 1; -- i) {
        if(nums[i] > nums[index - 1]) {
            if(nums[i] < second) {
                second = nums[i];
                secondIndex = i;
            }               
        }               
    }  
    swap(nums[index-1],nums[secondIndex]);
    sort(nums.begin()+index, nums.end());   
}
```

## [到最近的人的最大距离](https://leetcode-cn.com/problems/maximize-distance-to-closest-person/)

```cpp
int maxDistToClosest(vector<int>& seats) {
    int m = 1, n = 1;
    int first = -1, end = -1;
    
    for (int i = 0; i < seats.size(); ++i) {
        if (first == -1 && seats[i] == 1) {
            first = i;end = i;
        } 
        else if (first != -1 && seats[i] == 1) 
            end = i;
        if (seats[i] == 0 && i > 0 && seats[i]== seats[i-1]) ++n;
        else n=1;
        m = max(n, m);
    }
    end = seats.size()-end-1;
    m = (m+1)/2;
    //cout<<first<<" "<<m<<" "<<end<<endl;
    return m >= first ? m >= end ? m: end: first;
}
```
## [将数组分成和相等的三个部分](https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum/)

```cpp
bool canThreePartsEqualSum(vector<int>& A) {
    int sums[A.size()] = {0};
    sums[0] = A[0];
    for(int i = 1; i < A.size(); ++i) {
        sums[i] = sums[i-1] + A[i];
    }
    if (sums[A.size() - 1] % 3 != 0) return false;
    int avg = sums[A.size() - 1] / 3;
    int i = 0, j = A.size() - 1;
    while (sums[i] != avg && i + 1 < j) ++i;
    while (sums[A.size() - 1] - sums[j-1] != avg && i + 1 < j) --j;
    
    return sums[i] == avg && sums[A.size() - 1] - sums[j-1] == avg;
}
```
##  Cells with Odd Values in a Matrix

```cpp
class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        unordered_map<int, int> rows;
        unordered_map<int, int> cols;
        
        for(int i=0; i<indices.size(); i++){
            rows[indices[i][0]]++;
            cols[indices[i][1]]++;
        }
        int r=0;
        int c=0;
        for(int i=0; i<n; i++) if(rows[i]%2) r++;
        for(int i=0; i<m; i++) if(cols[i]%2) c++;
        return r*m + c*n - 2*r*c;
    }
};
```

### [Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

[Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)

1-n可以作为list的index判断是否出现/出现次数

```cpp
vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int>  result;
        for (int i = 0; i < nums.size(); ++i) {
            int index = abs(nums[i]) - 1;
            if (nums[index] > 0)
                nums[index] = -nums[index]; 
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) {
                result.push_back(i+1);
            }
        }
        return result;
    }
```

### [835. Image Overlap](https://leetcode.com/problems/image-overlap/)

计算出所有从A中1到B中1的平移向量，那么出现次数最多的平移向量的频率，就是可重叠1的最大个数

```cpp
int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
    int m = A.size();
    vector<pair<int,int>> loca, locb;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (A[i][j] == 1)
                loca.push_back(make_pair(i,j));
            if (B[i][j] == 1)
                locb.push_back(make_pair(i,j));
        }
    }
    int res = 0;
    map<pair<int, int>, int> direction;
    for (auto a: loca)
        for (auto b: locb) {
            pair<int, int> t = make_pair(a.first-b.first, a.second-b.second);
            direction[t] += 1;
            res = max(res, direction[t]);
        }
    return res;
}
```
### [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/solution/)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int N = nums.size();
        vector<int> res(N, 1);
        int prod = 1;
        for (int i = 0; i < N; i ++) {
            res[i] = prod;
            prod *= nums[i];
        }
        prod = 1;
        for (int i = N - 1; i >= 0; i--) {
            res[i] *= prod;
            prod *= nums[i];
        }
        return res;
    }
};
```

### [Array Nesting](https://leetcode.com/problems/array-nesting/)

```cpp
    int arrayNesting(vector<int>& nums) {
        int res = 0;
        bool visited[nums.size()];
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < nums.size(); ++i) {
            if (visited[i]) continue;
            visited[i] = true;
            int cur = nums[i];
            int count = 1;
            while(cur != i) {
                count+=1;
                cur = nums[cur];
            }
            res = max(res, count);
        }
        return res;
    }
```

###[Beautiful Arrangement II](https://leetcode.com/problems/beautiful-arrangement-ii/)

When \text{k = n-1}k = n-1, a valid construction is \text{[1, n, 2, n-1, 3, n-2, ....]}[1, n, 2, n-1, 3, n-2, ....]. One way to see this is, we need to have a difference of \text{n-1}n-1, which means we need \text{1}1 and \text{n}n adjacent; 

Actually we can construct for `[1...k+1]` and append `[k+2...n]` too. As first part contains diffs `1...k`, and diff of `k+2` and last element of first part (which is `k/2+1` for even `k` and `(k+1)/2` for odd `k`) is `k/2+1` or `(k+3)/2`, which are both true for `k>=2`, and when `k==1`, first part is empty, it works too.

```cpp
    vector<int> constructArray(int n, int k) {
        vector<int> res(n, 0);
        int cur = 0, dir = 2;
        for (int i = 1; i <= k+1; ++i) {
            res[cur] = i;
            cur += dir;
            if (cur >= k+1) {
                dir = -2;
                if (cur-2 == k-1) cur = k;
                else cur = k-1;
            }
        }
        for (int i = k+2; i <= n; ++i)
            res[i-1] = i;
        return res;
    }
```

### [Corporate Flight Bookings](https://zxi.mytechroad.com/blog/math/leetcode-1109-corporate-flight-bookings/)

```cpp
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ans(n + 1);
        for (const auto& b : bookings) {
          ans[b[0] - 1] += b[2];
          ans[b[1]] -= b[2];
        }
        for (int i = 1; i < n; ++i)
          ans[i] += ans[i - 1];
        ans.pop_back();
        return ans;
}
```

### [Moving Stones Until Consecutive II](https://leetcode.com/problems/moving-stones-until-consecutive-ii/)

给定一个数组，问把数组变成连续递增的数组需要把数组里面的数组变换多少次，求最少的次数和最多的次数。

```cpp
    vector<int> numMovesStonesII(vector<int>& A) {
        sort(A.begin(), A.end());
        int i = 0, n = A.size(), low = n;
        int high = max(A[n - 1] - n + 2 - A[1], A[n - 2] - A[0] - n + 2);
        for (int j = 0; j < n; ++j) {
            while (A[j] - A[i] >= n) ++i;
            if (j - i + 1 == n - 1 && A[j] - A[i] == n - 2)
                low = min(low, 2); //还是要Min一下的，有可能为0， 或者1
            else
                low = min(low, n - (j - i + 1));//这个区间是符合要求的，里面的j-i+1的数不用动，剩下的数要需要动的
        }
        vector<int> res;
        res.push_back(low);
        res.push_back(high);
        return res;
    }
```

###[Best Sightseeing Pair](https://blog.csdn.net/Eric_1993/article/details/104041142)

求和分为两个部分 `(A[i] + i)` 以及 `A[j] - j`. 使用 `res` 来记录 `(A[i] + A[j] + i - j)` 的最大值, 使用 `max_prev` 来不断更新 `A[i] + i` 的值. 由于 `max_prev` 保存 `A[i] + i` 的值, 因此更新 `res` 时, 使用 `max_prev + A[j] - j`.

```cpp
int maxScoreSightseeingPair(vector<int>& A) {
  int res = 0, max_prev = 0;
  for (int i = 0; i < A.size(); ++ i) {
    res = std::max(res, max_prev + A[i] - i);
    max_prev = std::max(max_prev, A[i] + i);
  }
  return res;
}
```

### [Flip String to Monotone Increasing](https://leetcode.com/problems/flip-string-to-monotone-increasing/)

if we want `x` zeros followed by `N-x` ones, there are `P[x]` ones in the start that must be flipped, plus `(N-x) - (P[N] - P[x])` zeros that must be flipped. The last calculation comes from the fact that there are `P[N] - P[x]` ones in the later segment of length `N-x`, but we want the number of zeros.

```cpp
int minFlipsMonoIncr(string S) {
        int first = 0, end = S.size()-1;
        int n = S.size();
        int v[n+1];
        memset(v, 0, sizeof(v));
        for (int i = 0; i < n; ++i) v[i+1] = v[i] + (S[i] == '1');
            
        int ans = INT_MAX;
        for (int i = 0; i <= n; ++i) 
            ans = min(ans, v[i] + n - i -(v[n]-v[i]));
        return ans;
 }
```

### [Last Moment Before All Ants Fall Out of a Plank](https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/)

现在有两只蚂蚁相向而行，遇到之后各自掉头或不掉头继续走并没有什么区别，所以直接找最左边和最右边的蚂蚁那个距离边界更远就行了。

```cpp
int getLastMoment(int n, vector<int>& left, vector<int>& right) {
  int max_val = 0;
  for(auto ele: left){
  	max_val = max(ele, max_val);
  }

  for(auto ele: right){
  	max_val = max(max_val, n-ele);
  }

  return max_val;
}
```

###[Count Number of Teams](https://leetcode.com/problems/count-number-of-teams/)

```cpp
    int numTeams(vector<int>& rating) {
        int result;
        
        for (int mid = 1; mid < rating.size(); ++mid) {
            int left_large = 0, left_small = 0, rignt_large = 0, right_small = 0;
            for(int i=0;i<mid;i++){
                if(rating[i]<rating[mid]) left_small++;
                else left_large++;
            }
            for(int k=mid+1;k<rating.size();k++){
                if(rating[k]<rating[mid]) right_small++;
                else rignt_large++;
            }
            result += left_large*right_small+left_small*rignt_large;
        }
        return result;
    }
```

### [Minimum Difference Between Largest and Smallest Value in Three Moves](https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/)

```
int minDifference(vector<int>& nums) {
        if (nums.size() <= 4) return 0;
        sort(nums.begin(), nums.end());
        int n = nums.size(), ans = INT_MAX;
        ans=min(ans,nums[n-1]-nums[3]); /* Changing the first 3 numbers to last number*/
        ans=min(ans,nums[n-4]-nums[0]); /* Changing the last 3 numbers to first number*/
        ans=min(ans,nums[n-2]-nums[2]);
        ans=min(ans,nums[n-3]-nums[1]);
        return ans;
    }
```

### [Previous Permutation With One Swap]()

```
Step 1:Set two pointers: L & R
Step 2: Move L from the end to the bengining of the array, found the first number break the non-increase trend. If L do not exist then return the original A.
Step 3: Move R from the end to the begining of the array, find the first number which is smaller than the number at the L pointer. If there are same numbers, choose the left one.
Step4: Swap the numbers at L and R pointer
```

```cpp
vector<int> prevPermOpt1(vector<int>& A) {
    n = A.size();
    if (n<=1) return A;
    int l = n-2;
    while (l>=0 && A[l]<=A[l+1])
        l -= 1;
    if (l < 0)
        return A;
    r = n-1;
    while (A[r]>=A[l])
        r -= 1;
    while (A[r]==A[r-1])
        r -= 1;
    int tmp = A[r];
    A[r] = A[l];
    A[l] = A[r];
    return A;
}
```
### [Subarray Sums Divisible by K]()

```cpp
  int subarraysDivByK(vector<int>& A, int K) {    
    vector<int> c(K);
    c[0] = 1;
    int ans = 0;
    int sum = 0;
    for (int a : A) {
      sum = (sum + a % K + K) % K;
      ans += c[sum]++;
    }
    return ans;
  }
```

### Minimum Operations to Reduce X to Zero

```cpp
    int minOperations(vector<int>& nums, int x) {
        int y = INT_MAX;
        map<int, int> s;
        int s1 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            s1 += nums[i];
            s[x-s1] = i+1;
            if (x - s1 == 0) y = i+1;
            //cout<<s[x-s1];
        }
        
        int s2 = 0;
        for (int i = nums.size()-1; i >= 0; --i) {
            s2 += nums[i];
            int tmp = nums.size() - i;
            if (x - s2 == 0) y = min(y, tmp);
            if (s.find(s2) != s.end()) {
                tmp += s[s2];
                if (tmp > nums.size()) break;
                y = min(y, tmp);
            }
        }
        //dfs(0, nums.size()-1, 0, nums, x);
        return y == INT_MAX ? -1: y;
    }
```

### Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts

Given a rectangular cake with height `h` and width `w`, and two arrays of integers `horizontalCuts` and `verticalCuts` where `horizontalCuts[i]` is the distance from the top of the rectangular cake to the `ith` horizontal cut and similarly, `verticalCuts[j]` is the distance from the left of the rectangular cake to the `jth` vertical cut.

*Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays `horizontalCuts` and `verticalCuts`.* Since the answer can be a huge number, return this modulo 10^9 + 7.

```cpp
int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        horizontalCuts.insert(horizontalCuts.begin(),0);
        horizontalCuts.insert(horizontalCuts.end(),h);
        verticalCuts.insert(verticalCuts.begin(),0);
        verticalCuts.insert(verticalCuts.end(),w);
        unsigned long horizontalMax=0, verticalMax=0;
        unsigned long mode = 1e9 + 7;
        for (int i = 0; i < horizontalCuts.size()-1; ++i) {
            unsigned long tmp = (horizontalCuts[i+1]-horizontalCuts[i])%mode;
            if (horizontalMax < tmp)
                horizontalMax = tmp;
        }
        for (int i = 0; i < verticalCuts.size()-1; ++i) {
            unsigned long tmp = (verticalCuts[i+1]-verticalCuts[i])%mode;
            if (verticalMax < tmp)
                verticalMax = tmp;
        }
        return (horizontalMax*verticalMax)%mode;
    }
```

