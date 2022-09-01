# 二分法

```java
// version 1: with jiuzhang template
class Solution {
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    public int binarySearch(int[] nums, int target) {
        if (nums == null || nums.length == 0) {
            return -1;
        }
        
        int start = 0, end = nums.length - 1;
        while (start + 1 < end) { // 防止死循环
            int mid = start + (end - start) / 2;//防止溢出
            if (nums[mid] == target) {
                end = mid;//根据题目确定这种情况应该怎么做
            } else if (nums[mid] < target) {
                start = mid;
                // or start = mid + 1 这样也对
            } else {
                end = mid;
                // or end = mid - 1 这样也对
            }
        }
        //如果找first position 就先start
        if (nums[start] == target) {
            return start;
        }
        //如果照last position 就先end
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
}


// version 2: without jiuzhang template
class Solution {
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    public int binarySearch(int[] nums, int target) {
        if (nums == null || nums.length == 0) {
            return -1;
        }
        
        int start = 0, end = nums.length - 1;
        while (start < end) {
            int mid = start + (end - start) / 2;//防止溢出
            if (nums[mid] == target) {
                end = mid;
            } else if (nums[mid] < target) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        
        return -1;
    }
}
```

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

###[Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

```cpp
	bool possible(int D, int C, vector<int>& weights) {
        int days = 0;
        int idx = 0;
        while(idx < weights.size() && days <= D) {
            int sum=0;
            if(weights[idx]>C)return false;
            while(idx<weights.size() && sum+weights[idx]<=C){
                sum+=weights[idx];
                idx++;
            }
            days++;
        }
        if(days > D)return false;
        return true;
    }
    int shipWithinDays(vector<int>& weights, int D) {
        int lo=0;
        int hi=weights.size()*500;
        while(hi-lo>1){       
            int mid=(lo+hi)/2;
            if(possible(D,mid,weights)){
                hi=mid;
            }else{
                lo=mid;   
            }
        }
        return hi;
    }
```

### [Magnetic Force Between Two Balls]()

二分法,两个球在位置最小距离最大化

```cpp
class Solution {
public:
    int maxDistance(vector<int>& pos, int m) {
        sort(pos.begin(), pos.end());
        int l=1, r= 1 + (pos.back() - pos.front()) ;// / (m-1);
        while(l+1<r){
            auto mid = (l+r)/2;
            //距离为mid能不能放
            if(able(pos, m, mid)) l = mid;
            else r = mid;
        }
        return l;
    }
    
    bool able(const vector<int>& v, int m, int d){
        int x = v[0];
        while(--m){
            auto it = lower_bound(v.begin(), v.end(), x+d);
            if(it == v.end()) return false;
            x = *it;
        }
        return true;
    }
};
```

### Kth Smallest Element in a Sorted Matrix

Given an `n x n` `matrix` where each of the rows and columns is sorted in ascending order, return *the* `kth` *smallest element in the matrix*.

Note that it is the `kth` smallest element **in the sorted order**, not the `kth` **distinct** element.

You must find a solution with a memory complexity better than `O(n2)`.

```cpp
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int lo = matrix[0][0], hi = matrix[n-1][n-1] + 1, mid, count, tmp;
    
    while (lo < hi) {
        mid = lo + (hi - lo) / 2, tmp = n - 1, count = 0;
        
		// For each row, we count the elements that are smaller then mid
        for (int i = 0; i < n; i++) {
            while (tmp >= 0 && matrix[i][tmp] > mid) tmp--;
            count += tmp + 1;
        }
        
        if (count < k) lo = mid + 1;
        else hi = mid;
    }
    
    return lo;
}
```
