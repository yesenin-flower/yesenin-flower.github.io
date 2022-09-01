### Minimize Deviation in Array

```
Even numbers can be divided multiple times until it converts to an odd number.
Odd numbers can be doubled only once as it converts to an even number.
Therefore, even numbers can never be increased.
Follow the steps below to solve the problem: 
 

1. Traverse the vector and double all the odd vector elements. This nullifies the requirement for the 2nd operation.
2. Now, decrease the largest vector element while it’s even.
3. To store the vector elements in sorted manner, insert all vector elements into a Set.
4. Greedily reduce the maximum element present in the Set
5. If the maximum element present in the Set is odd, break the loop.
6. Print the minimum deviation obtained.
```

```cpp
int minimumDeviation(vector<int>& nums) {
    set<int> s;
    for(int i = 0; i < nums.size(); ++i) {
        if (nums[i] % 2 == 0)
            s.insert(nums[i]);
        else
            s.insert(nums[i]*2);
    }
    int diff = *s.rbegin() - *s.begin();
    while (!s.empty() && *s.rbegin() % 2 == 0) {
        int maxEl = *s.rbegin(); 
        s.erase(maxEl); 
        s.insert(maxEl/2);
        diff = min(diff, *s.rbegin() - *s.begin()); 
    }
    return diff;
}
```