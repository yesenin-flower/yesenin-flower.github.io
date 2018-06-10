# 最小栈
1. 两个栈
   一个记录数值，一个记录当前最小值。

   当有新数push进来的时候，如果栈2为空或者这个数小于栈2顶上的值，就把这个数推入栈2。

   当pop的数正好等于最小值时，说明当前栈内的最小值变化了，要弹出这个最小值，记录的下一个最小值来到栈顶。

2. Trick
   一个整型变量min\_val来记录当前最小值，一同入栈，为节省空间，仅在当前最小值更改时才入栈。初始化为整型最大值。

   然后如果需要进栈的数字小于等于当前最小值min\_val，那么将min\_val和新进来的数压入栈，并且将min\_val更新为当前数字。

   在出栈操作时，先将栈顶元素移出栈，再判断该元素是否和min\_val相等，相等就把它下面记录的之前最小值赋给min\_val并弹出。


# 下一个更大的元素

维持一个非递增数组，存储在栈中，当下一个元素比栈顶大时，依次出栈，直到栈顶大于等于该元素时，停止出栈，该元素入栈，此时所有出栈的元素的下一个更大元素为该元素，存储在hashmap中，时间复杂度为O（n）。

```cpp
输入: findNums = [2,4], nums2 = [1,2,3,4].
输出: [3,-1]
解释:
    对于findNums中的数字2，第二个数组中的下一个较大数字是3。
    对于num1中的数字4，第二个数组中没有下一个更大的数字，因此输出 -1。
```

```cpp
vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
    stack<int> s;
    unordered_map<int, int> m;
    for (int n : nums) {
        while (s.size() && s.top() < n) {
            m[s.top()] = n;
            s.pop();
        }
        s.push(n);
    }
    vector<int> ans;
    for (int n : findNums) ans.push_back(m.count(n) ? m[n] : -1);
    return ans;
}
```
# 最大二叉树

```cpp
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    TreeNode* root;
    if (nums.size() == 0)  return root;
    
    stack<TreeNode*> s;
    root = new TreeNode(nums[0]);
    s.push(root);
    
    for (int i = 1; i < nums.size(); ++i) {
        TreeNode* tmp = new TreeNode(nums[i]);
        
        if (s.top()->val  > nums[i]) {
            s.top()->right = tmp;
            s.push(tmp);
        } else {
            TreeNode* top;
            while (!s.empty() && s.top()->val < nums[i]) {
                top = s.top();
                s.pop();
            }       
            tmp->left = top;
            if (!s.empty()) {
                s.top()->right = tmp;
                s.push(tmp);
            }  
            else {
                s.push(tmp);
            }
        }
    }
    while (!s.empty()) {
        root = s.top();
        s.pop();
    }
    return root;
}
```