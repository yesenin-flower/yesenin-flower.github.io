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

# 删除排序数组中的重复项+移除某个元素

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
# 数组数字加一

```cpp
vector<int> plusOne(vector<int>& digits) {
        int m = 1;
        for ( int i = digits.size() - 1; i>=0; --i ) {
            m += digits[i];
            digits[i] = m % 10;
            m = m / 10;
            if ( m == 0 ) break;
        }
        if ( m == 1 )
            digits.insert(digits.begin(), m);
        return digits;
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
