### quicksort

以中间的数作为基数，使用双指针i,j进行双向遍历：

- 1、i从左往右寻找第一位大于基数（6）的数字，j从右往左寻找第一位小于基数（6）的数字；
- 2、找到后将两个数字进行交换。继续循环交换直到i>=j结束循环；
- 3、最终指针i=j,此时交换基数和i(j)指向的数字即可将数组划分为小于基数（6）/基数（6）/大于基数（6）的三部分，即完成一趟快排；

```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quitsort(nums, 0, nums.size()-1);
        return nums;
    }
private:
    void quitsort(vector<int>& nums,int l, int r) {
        if (l < r) {
            int idx = patition(nums, l, r);
            quitsort(nums, l, idx-1);
            quitsort(nums, idx+1, r);
        }
    }
    int patition(vector<int>& n,int l, int r) {
        // p为基数，即待排序数组的第一个数
        int p = n[(l + r) / 2];
        int i = l;
        int j = r;
        while (i <= j) {
          // 从右往左找第一个小于基数的数
          while (n[j] >= p && i < j) {
            j--;
          }
          // 从左往右找第一个大于基数的数
          while (n[i] <= p && i < j) {
            i++;
          }
          // 找到后交换两个数
          if (i <= j) {
          		swap(n[i], n[j]);
            	i++;
            	j--;
          }
        }
        return i;
    }
};
```

```cpp
vector<int> sortArray(vector<int>& nums) {
	if (nums.size() <= 1) return nums;
    qSort(nums, 0, nums.size() - 1);
    return nums;
}
void qSort(vector<int>& nums, int start, int end) {
        if (start >= end) return;
  			int left = start;
        int right = end;
        int mid = (left + right) >> 1;
  			//1. get value of pivot
        int pivot = nums[mid];
        //2. left <= right
  			//3. nums[i] < pivot
        while (left <= right) {
            while (left <= right && nums[left] < pivot) left++;
            while (left <= right && nums[right] > pivot) right--;
            if (left <= right) {
                swap(nums[left++], nums[right--]);
            }
        }
  			//4. start->right; left->end;
        qSort(nums, start, right);
        qSort(nums, left, end);
}
```

### merge sort

```java
public class Solution {
    /**
     * @param A an integer array
     * @return void
     */
    public void sortIntegers2(int[] A) {
        // use a shared temp array, the extra memory is O(n) at least
        int[] temp = new int[A.length];
        mergeSort(A, 0, A.length - 1, temp);
    }
    
    private void mergeSort(int[] A, int start, int end, int[] temp) {
        if (start >= end) {
            return;
        }
        
        int left = start, right = end;
        int mid = (start + end) / 2;

        mergeSort(A, start, mid, temp);
        mergeSort(A, mid + 1, end, temp);
        merge(A, start, mid, end, temp);
    }
    
    private void merge(int[] A, int start, int mid, int end, int[] temp) {
        int left = start;
        int right = mid + 1;
        int index = start;
        
        // merge two sorted subarrays in A to temp array
        while (left <= mid && right <= end) {
            if (A[left] < A[right]) {
                temp[index++] = A[left++];
            } else {
                temp[index++] = A[right++];
            }
        }
        while (left <= mid) {
            temp[index++] = A[left++];
        }
        while (right <= end) {
            temp[index++] = A[right++];
        }
        
        // copy temp back to A
        for (index = start; index <= end; index++) {
            A[index] = temp[index];
        }
    }
}
```

### quick selection

```cpp
int kthLargestElement(int k, vector<int> &nums) {
  int n = nums.size();
  // 为了方便编写代码，这里将第 k 大转换成第 k 小问题。
  k = n - k;
  return partition(nums, 0, n - 1, k);
}

int partition(vector<int>& nums, int start, int end, int k) {
  int left = start, right = end;
  int pivot = nums[left];

  while (left <= right) {
    while (left <= right and nums[left] < pivot) {
      left++;
    }
    while (left <= right and nums[right] > pivot) {
      right--;
    }
    if (left <= right) {
      swap(nums[left], nums[right]);
      left++;
      right--;
    }
  }

  // 如果第 k 小在左侧，搜索右边的范围，否则搜索右侧。
  if (k <= right) {
    return partition(nums, start, right, k);
  }
  if (k >= left) {
    return partition(nums, left, end, k);
  }
  return nums[k];
}
```