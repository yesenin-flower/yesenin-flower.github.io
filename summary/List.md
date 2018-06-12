# 旋转数组

将包含* n* 个元素的数组向右旋转 *k *步。

例如，如果  *n* = 7 ,  *k* = 3，给定数组  `[1,2,3,4,5,6,7]`  ，向右旋转后的结果为 `[5,6,7,1,2,3,4]`。

前n-k个reverse，后k个reverse`[4,3,2,1,7,6,5]`

再全局reverse

# Two Sum 输入有序数组

1. 分治
   第一个数字肯定要小于目标值target，那么我们每次用二分法来搜索target - numbers[i]即可
2. 两个指针
   两个指针，一个指向开头，一个指向末尾，然后向中间遍历，如果指向的两个数相加正好等于target的话，直接返回两个指针的位置即可，若小于target，左指针右移一位，若大于target，右指针左移一位，以此类推直至两个指针相遇停止

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
    int sz = numbers.size();
    int l = 0, r = sz - 1;
    vector<int> res;
    while (l < r) {
        int sum = numbers[l] + numbers[r];
        if (sum == target) {
            res.push_back(l+1);
            res.push_back(r+1);
            return res;
        } else if (sum > target){
            --r;
        } else if (sum < target){
            ++l;
        }
    }
    return res;
}
```
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size(); ++i) {
        int j = i + 1;
        int k = nums.size() - 1;
        if (i != 0 && nums[i] == nums[i-1]) continue;
        
        while (j < k) {
            if (nums[i] + nums[j] + nums[k] == 0) {
                res.push_back({nums[i],nums[j],nums[k]});
                ++j;
                --k;
                while (j < k && nums[j] == nums[j-1]) ++j;
                while (j < k && nums[k] == nums[k+1]) --k;
            } else if (nums[i] + nums[j] + nums[k] < 0) {
                ++j;
            } else {
                --k;
            }
        }
    }
    return res;
}
```
```cpp
int triangleNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size()-1; ++j) {
            int k = nums.size() - 1;
            while (j < k && nums[i] + nums[j] <= nums[k]) --k;
            if (j < k) res += k - j;
        }
    }
    return res;
}
```
# HASHTABLE

如果要求index，就用hashtable做。

| 题号   | 题名           |
| :--- | ------------ |
| 1    | 两数之和         |
| 532  | 数组中的K-diff数对 |
| 18   | 四数之和         |
|      |              |

# 数组最长公共前缀

```
输入: ["flower","flow","flight"]
输出: "fl"
```

先排序，第一个和最后一个元素的相同前缀就是整个数组的最长公共前缀

# 删除排序数组中的重复项+移除某个元素+移动零

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
# 合并有序数组

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

# 修改一个值得到非递减数列

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
# [找到所有数组中消失的数字](https://www.cnblogs.com/grandyang/p/6222149.html)

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
# [最小移动次数使数组元素相等](https://www.cnblogs.com/grandyang/p/6053827.html)

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

# 相对名次

```cpp
vector<string> findRelativeRanks(vector<int>& nums) {
    vector<int> rank;
    for(int i=0; i<nums.size(); ++i) rank.push_back(i);

    sort(rank.begin(), rank.end(), 
         [&](int a, int b){return nums[a] > nums[b];});
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
# 寻找数组的中心索引

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
# 词典中最长的单词

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
# 最短无序连续子数组

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
# 最长和谐子序列

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

# 全排列

```cpp
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
# 子集

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

