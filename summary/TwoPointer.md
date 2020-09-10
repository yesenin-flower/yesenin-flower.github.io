## [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

```cpp
int maxArea(vector<int>& height) {
    int len = height.size();
    int left = 0, right = len - 1;
    int maxx = 0,temp;
    while (left<right&&left<len-1 && right>=0)
    {
       temp = min(height[left], height[right])*(right - left);
       if (temp > maxx)maxx = temp;
        if (height[left] < height[right])left++;
        else right--;
    }
    return maxx;
}
```

##[Partition Array into Disjoint Intervals](https://leetcode.com/problems/partition-array-into-disjoint-intervals/)

```
var partitionDisjoint = function(A) {
    let max = A[0];
    let allMax = A[0];
    let solution = 1;
    for (let i = 1; i < A.length; i++) {
        if (A[i] < max) {
            solution = i + 1;
            max = allMax;
        } else {
            allMax = Math.max(allMax, A[i]);
        }
    }
    return solution;
};
```



## Two Sum 输入有序数组

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

## [977. Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/)

Given an array of integers `A` sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.

```cpp
vector<int> sortedSquares(vector<int>& A) {
    vector<int> result(A.size(), 0); 
    int start = 0, end = A.size()-1;
    int point = A.size()-1;
    while (start <= end) {
        int m = A[start] * A[start];
        int n = A[end] * A[end];
        //cout<<start<<" "<<end<<" "<<A[start]<<" "<<A[end]<<" "<<m<<" "<<n<<endl;
        if (m < n) {
            result[point--] = n;
            --end;
        } else {
            result[point--] = m;
            ++start;
        }
    }
    return result;
}
```
