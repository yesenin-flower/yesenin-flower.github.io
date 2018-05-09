# 最大子序和

把序列从中间分为两部分，那么最大子序列和可能在三处出现，要么整个出现在输入数据的左半部，要么整个出现在右半部，要么跨越分界线。前两种情况可以递归求解，第三种情况的最大和可以通过求出前半部分（包括前半部分的最后一个元素）的最大和以及后半部分（包含后半部分的第一个元素）的最大和而得到，此时将两个和相加。

```cpp
int split(vector<int>& nums,int start,int end) {
        if (start == end) {
            return nums[start];
        }
        int med = (start + end) / 2;
        int maxLeftSum = split(nums, start, med);
        int maxRightSum = split(nums, med+1, end);
        
        int left = 0, maxleft = INT_MIN;
        for (int i = med; i >= start; i--) {  
            left += nums[i];
            if (left>maxleft) 
                maxleft = left;
        }
        
        int right = 0, maxright = INT_MIN;
        for (int i=med+1; i<=end; ++i) {
            right += nums[i];
            if (right>maxright) 
                maxright = right;
        }
        int maxBorderSum = maxleft + maxright;  
        return maxBorderSum > maxLeftSum ? maxBorderSum > maxRightSum ? maxBorderSum : maxRightSum  
            : maxLeftSum > maxRightSum ? maxLeftSum : maxRightSum; 
}
```

# x 的平方根

```cpp
int mySqrt(int x) {
        if ( x == 0 ) return 0;
        
        int low = 1;
        int high = x;
        int med;
        while ( low <= high ) {
            med = (low + high) / 2;
            if ( med == x / med )
                return med;
            else if ( med < x / med ) {
                low = med + 1;
            } else {
                high = med - 1;
            }
        } 
        if ( med > x / med ) return med - 1;
        else return med;
}
```

