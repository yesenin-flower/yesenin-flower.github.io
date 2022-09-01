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

###[Online Stock Span]()

```cpp
class StockSpanner {
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        pair<int,int> temp;
        temp.first = price;
        temp.second = count;
        int ans =0;
        bool flag = false;
        // stack.push(temp);
        while(!st.empty() && price >= st.top().first){
            st.pop();
            flag = true;
        }
        if(!st.empty()){
            ans = temp.second - st.top().second;
        }else{
            if(flag){
                ans = temp.second + 1;
            }else{
                ans = 1;
            }
        }
        st.push(temp);
        count++;
        return ans;
    }
private:
    stack<pair<int,int>> s;
    int count=0;
};
```

### 最大频率stack

```
Input: 
["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
Output: [null,null,null,null,null,null,null,5,7,5,4]
Explanation:
After making six .push operations, the stack is [5,7,5,7,4,5] from bottom to top.  Then:

pop() -> returns 5, as 5 is the most frequent.
The stack becomes [5,7,5,7,4].

pop() -> returns 7, as 5 and 7 is the most frequent, but 7 is closest to the top.
The stack becomes [5,7,5,4].

pop() -> returns 5.
The stack becomes [5,7,4].

pop() -> returns 4.
The stack becomes [5,7].
```

```cpp

class FreqStack {
public:
    int max_frequency; // keep note of the current maximum frequency
    unordered_map<int, int> freq_mp; // to store the freq of numbers
    unordered_map<int, stack<int>> freq_stack_mp; // to store the numbers with same freq in a stack
    
    FreqStack() {
        // initially maximum frequency is 0
        max_frequency=0;
    }
    
    void push(int x) {
        // increase the freq of x in frequency map
        ++freq_mp[x];
        
        // update max_frequency
        if(max_frequency<freq_mp[x]) max_frequency = freq_mp[x];
        
        // push x to its freq stack
        freq_stack_mp[freq_mp[x]].push(x);
    }
    
    int pop() {
        // get the top element from the stack of maximum frequency
        // here stack is used for taking care of the "frequency tie" condition
        int curr_top = freq_stack_mp[max_frequency].top();
        
        // update both the maps
        freq_stack_mp[max_frequency].pop();
        --freq_mp[curr_top];
        //cout<<freq_stack_mp[max_frequency].size()<<" "<<max_frequency<<" ";
        // if the stack of maximum element becomes empty, then delete it from "freq_stack_mp" along with decreasing "max_frequency"
        if(freq_stack_mp[max_frequency].empty()) {
            freq_stack_mp.erase(max_frequency);
            --max_frequency;
        }
        //cout<<max_frequency<<endl;
        // return the current top element
        return curr_top;
    }
};
```

### Remove K Digits

Given string num representing a non-negative integer `num`, and an integer `k`, return *the smallest possible integer after removing* `k` *digits from* `num`.

1231 (1) -> 121

```cpp
string removeKdigits(string num, int k) {
    if (k >= num.size()) return "0";
    if (k == 0) return num;
    stack<char> minimal;
    minimal.push('0');
    for (auto n: num) {
        char tmp = minimal.top();
        while (tmp > n && k > 0) {
            minimal.pop();
            k -= 1;
            tmp = minimal.top();
        }
        minimal.push(n);
    }
    while(k && !minimal.empty())
    {
        --k;
        minimal.pop();
    }
    string res;
    while(!minimal.empty())
    {
        res = minimal.top() + res; // pushing stack top to string
        minimal.pop(); // pop the top element
    }
    int idx = 0;
    while (idx < res.size()) {
        if (res[idx] != '0')
            break;
        idx += 1;
    }
    res = res.substr(idx, res.size()-idx);
    if(res.size() == 0)
        return "0";
    return res;
}
```