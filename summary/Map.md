##[Two Sum](https://leetcode.com/problems/two-sum/)

#### Two-pass Hash Table

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for (int i{0}; i<nums.size(); i++) {
            auto p = mp.find(target-nums[i]);
            if (p != mp.end())
                return {p->second, i};
            mp[nums[i]] = i;
        }
        return {};
    }
```

[总持续时间可被 60 整除的歌曲](https://leetcode-cn.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/)

```cpp
int numPairsDivisibleBy60(vector<int>& time) {
    if(time.size() < 2) return 0;
    int c[60]{0};
    for(int t : time)
        c[t % 60]++;
    int ans = c[0] * (c[0] - 1) / 2 + c[30] * (c[30] - 1) / 2;
    for(int i = 1; i < 30; i++)
        ans += c[i] * c[60 - i];
    return ans;
}
```



## [存在重复元素 II](https://leetcode-cn.com/problems/contains-duplicate-ii/)

给定一个整数数组和一个整数 *k*，判断数组中是否存在两个不同的索引 *i* 和 *j*，使得 **nums [i] = nums [j]**，并且 *i* 和 *j* 的差的绝对值最大为 *k*。

```cpp
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    map<int, int> m;  
    for (int i = 0; i < nums.size(); ++i) {  
       if (m.find(nums[i]) != m.end() && i - m[nums[i]] <= k)    return true;  
       else m[nums[i]] = i;      
    }  
    return false;  
}


```

## [How Many Numbers Are Smaller Than the Current Number](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/)

```cpp
vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    map<int, int> mp;
    for (int i = 0; i <= 100; ++i) {
        mp[i] =  0;
    }
    for (int i = 0; i < nums.size(); ++i) {
        mp[nums[i]] += 1;  
    }
    for (int i = 1; i < 100; i++) {
        mp[i] = mp[i] + mp[i - 1];  
    }
    vector<int> result;
    for (int i = 0; i < nums.size(); ++i) {
        result.push_back(mp[nums[i]] > 0 ? mp[nums[i] - 1] : 0); 
    }
    return result;
}
```

