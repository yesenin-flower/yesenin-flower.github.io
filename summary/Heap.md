##[数据流中的第K大元素](https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/)

```cpp
KthLargest(int k, vector<int>& nums) {
    v = k;
    for (auto i : nums) {
        addElement(i);
    }
}

int add(int val) {
    addElement(val);
    return arr.top();
}
priority_queue<int, vector<int>, greater<int> > arr;
int v;

void addElement(int val) {
    if (arr.size() < v) {
        arr.push(val);
    } else {
        if (val > arr.top()) {
            arr.pop();
            arr.push(val);
        }
    }
}
```

## [第k大的元素](https://leetcode.com/problems/kth-largest-element-in-an-array/)

快速选择，基于快速排序的思想，时间复杂度O(n)

```cpp
class Solution {
    
    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    
    public int quickSelect(int[] nums, int left, int right, int k) {
        if (left > right) {
            return 0;
        }
        int j = right, i = left;
        swap(nums, left, (left + right) >> 1);
        while (i < j) {
            while (i < j && nums[j] >= nums[left]) {
                j--;
            }
            while (i < j && nums[i] <= nums[left]) {
                i++;
            }
            if (i < j) {
                swap(nums, i, j);
            }
        }
        swap(nums, i, left);
        int cnt = i - left + 1;
        if (cnt == k) {
            return nums[i];
        } else if (cnt < k) {
            return quickSelect(nums, i + 1, right, k - cnt);
        } else {
            return quickSelect(nums, left, i - 1, k);
        }
    }
    
    public int findKthLargest(int[] nums, int k) {
        return quickSelect(nums, 0, nums.length - 1, nums.length - k + 1);
    }
}
```

堆排，先构造大顶堆，堆顶和堆尾交换k-1次后的堆顶即为第k大

```cpp
class Solution {
    
    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    
    public int heapSelect(int[] nums, int k) {
        int n = nums.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            ajustHeap(nums, i, n);   
        }
        int ansPos = n - 1;
        for (; ansPos > 0 && k > 0; ansPos--, k--) {
            swap(nums, 0, ansPos);
            ajustHeap(nums, 0, ansPos);
        }
        return nums[0];
    }
    
    public void ajustHeap(int[] nums, int pos, int n) {
        int tmp = nums[pos];
        for (int i = pos << 1 | 1; i < n; i = i << 1 | 1) {
            if (i + 1 < n && nums[i + 1] > nums[i]) {
                i++;
            }
            if (nums[i] > tmp) {
                nums[pos] = nums[i];
                pos = i;
            } else {
                break;
            }
        }
        nums[pos] = tmp;
    }
    
    public int findKthLargest(int[] nums, int k) {
        return heapSelect(nums, k - 1);
    }
}
```

```cpp
int findKthLargest(vector<int>& A, int k) {
  //create min heap;
  priority_queue<int,vector<int>,greater<int>> minh;
  for(int i=0;i<A.size();i++)
  {
    minh.push(A[i]);
    //if size of min heap exceeds K , then pop . 
    //This will keep the Kth largest element on top of heap                     
    if(minh.size()>k)
      minh.pop();
  }
  return minh.top();
}
```

