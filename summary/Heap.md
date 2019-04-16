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