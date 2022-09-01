### [数据流中的第K大元素](https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/)

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
//升序队列——小顶堆
//priority_queue <int,vector<int>,greater<int>> pq;
//降序队列——大顶堆
//priority_queue <int,vector<int>,less<int>>pq;
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

```cpp
struct cmp
{
    bool operator()(pair<int,int> a,pair<int,int> b)
    {
        return a.first < b.first;
    }
};


class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> maxh;
        for (int i = 0; i < points.size(); ++i) {
            int tmp = pow(points[i][0],2)+pow(points[i][1],2);
            maxh.push(make_pair(tmp, i));
            if(maxh.size()>k)
                maxh.pop(); 
        }
        vector<vector<int>> res;
        while (!maxh.empty()) {
            res.push_back(points[maxh.top().second]);
            maxh.pop();
        }
        return res;
    }
};
```

# Maximum Performance of a Team

**Greedy** + **Sliding Window**

1. Sort engineers by their efficiency in descending order.
2. For each window of K engineers (we can have less than K people in the first k-1 windows), ans is sum(speed) * min(efficiency).

```cpp
  int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
    vector<pair<int, int>> es;
    for (int i = 0; i < n; ++i)
      es.push_back({efficiency[i], speed[i]});
    sort(rbegin(es), rend(es));
    priority_queue<int, vector<int>, greater<int>> q;
    long sum = 0;
    long ans = 0;
    for (int i = 0; i < n; ++i) {
      if (i >= k) {
        sum -= q.top();
        q.pop();
      }
      sum += es[i].second;
      q.push(es[i].second);
      ans = max(ans, sum * es[i].first);
    }
    return ans % static_cast<int>(1e9 + 7);
  }
```

### 滑动窗口最大值

#### [跳跃游戏 VI](https://leetcode-cn.com/problems/jump-game-vi/)

```cpp
int maxResult(vector<int>& nums, int k) {
    deque<pair<int, int>> dq;
    dq.push_back({nums[0], 0});

    int ans = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        while (!dq.empty() && i - dq.front().second > k) {
            dq.pop_front();
        }
        ans = dq.front().first + nums[i];
        while (!dq.empty() && dq.back().first <= ans) {
          //比他先加入的值，肯定先被踢掉，所以直接踢掉
            dq.pop_back();
        }
        dq.push_back({ans, i});
    }
    return ans;
}

int maxResult(vector<int>& nums, int k) {
        int n = nums.size(), ans = nums[0];
        priority_queue<pair<int,int>> q;// sum. idx
        q.push({nums[0], 0});
        for(int i = 1; i < n; ++i) 
        {
            while(i-q.top().second > k)//这些位置，不能跳到 i 位置
                q.pop();
            //能调过来的位置，选最大的，跳到 i
            ans = q.top().first + nums[i];// 到 i位置的最优选择
            q.push({ans, i});//存入优先队列
        }
        return ans;
    }
```

