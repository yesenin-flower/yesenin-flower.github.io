# 旋转数组

前n-k个reverse，后k个reverse，再全局reverse

# Two Sum 输入有序数组

1. 分治
   第一个数字肯定要小于目标值target，那么我们每次用二分法来搜索target - numbers[i]即可
2. Trick
   两个指针，一个指向开头，一个指向末尾，然后向中间遍历，如果指向的两个数相加正好等于target的话，直接返回两个指针的位置即可，若小于target，左指针右移一位，若大于target，右指针左移一位，以此类推直至两个指针相遇停止


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

如 [4,3,2,3]

```cpp
public boolean checkPossibility(int[] nums) {
    int cnt = 0;
    for(int i = 1; i < nums.length; i++){
        if(nums[i] < nums[i - 1]){
            cnt++;
            if(i - 2 >= 0 && nums[i - 2] > nums[i]) nums[i] = nums[i-1];
            else nums[i - 1] = nums[i];
        }
    }
    return cnt <= 1;
}
```