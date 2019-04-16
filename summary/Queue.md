## [滑动窗口最大值](https://segmentfault.com/a/1190000003903509)

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    if (nums.size() == 0) return res;  
    
    deque<int> dq;
    for (int i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if ((i+1) >= k) res.push_back(nums[dq.front()]);
    }
    return res;
}
```

