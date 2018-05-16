# 对称二叉树

```cpp
bool isSymmetric(TreeNode* root) {
    if (root != NULL) {
        return dfs(root->left, root->right);
    }
    return true;
}
```
```cpp
bool dfs(TreeNode* left, TreeNode* right) {
    if (left == NULL && right == NULL) return true;
    else if (left == NULL || right == NULL) return false;
    if (left->val == right->val) {
        if (dfs(left->left,right->right))
            return dfs(left->right,right->left);
    }
    return false;
}
```
# 层次遍历

```cpp
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> res;
    
    queue<TreeNode*> q;
    if (root != NULL) q.push(root);
    
    while (!q.empty()) {
        int levCount = q.size(), count = 0;
        vector<int> tmp;
        while (count < levCount) {
            TreeNode* front = q.front();
            tmp.push_back(front->val);
            ++count;
            if (front->left != NULL) 
                q.push(front->left);
            if (front->right != NULL) 
                q.push(front->right);
            q.pop();
        }
        res.insert(res.begin(), tmp);
    }
    return res;
}
```
# 判断平衡二叉树

```cpp
bool isBalanced(TreeNode* root) {
    if (root != NULL) {
        if (abs(dfs(root->left) - dfs(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right)) return true;
        return false;
    }
    return true;
}
int dfs(TreeNode* root) {
    if (root == NULL) return 0;
    int d1 = dfs(root->left);
    int d2 = dfs(root->right);
    return d1 < d2 ? d2+1 : d1+1;
}
```
# 最小深度

```cpp
int dfs2(TreeNode* root) {
    if (root == NULL) return 0;
    int left = dfs2(root->left);
    int right = dfs2(root->right);
    return (left == 0 || right == 0) ? left + right + 1 : left > right ? right + 1 : left + 1;  
}
```

# 二叉搜索树的最近公共祖先

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL) return root;
    if (p->val > q->val) {
        TreeNode* tmp = p;
        p = q;
        q = tmp;
    }
    
    if (p->val <= root->val && q->val >= root->val) 
      	return root;
    else if (root->val < p->val) 
      	return lowestCommonAncestor(root->right, p, q);
    else if (root->val > q->val) 
      	return lowestCommonAncestor(root->left, p, q);
}
```

# 路径之和（可从中间开始）

```cpp
int pathSum(TreeNode* root, int sum) {
    if(!root) return 0;
    return sumUp(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}

int sumUp(TreeNode* root, int pre, int& sum){
    if(!root) return 0;
    int current = pre + root->val;
    return (current == sum) + sumUp(root->left, current, sum) + sumUp(root->right, current, sum);
}
```
#  二进制手表

```cpp
void DFS(int len, int k, int curIndex, int val, vector<int>& vec)  
{  
    if(k==0 && len==4 && val < 12) vec.push_back(val);  
    if(k==0 && len==6 && val < 60) vec.push_back(val);  
    if(curIndex == len || k == 0) return;  
    DFS(len, k, curIndex+1, val, vec);  
    val += pow(2, curIndex), k--, curIndex++;  
    DFS(len, k, curIndex, val, vec);  
}  
  
vector<string> readBinaryWatch(int num) {  
    vector<string> ans;  
    for(int i = max(0, num-6); i <= min(4, num); i++)  
    {  
        vector<int> vec1, vec2;  
        DFS(4, i, 0, 0, vec1), DFS(6, num-i, 0, 0, vec2);  
        for(auto val1: vec1)  
            for(auto val2: vec2)   
            {  
                string str = (to_string(val2).size()==1?"0":"") + to_string(val2);  
                ans.push_back(to_string(val1)+":"+ str);  
            }  
    }  
    return ans;  
} 
```
# 二叉搜索树众数

```cpp
vector<int> findMode(TreeNode* root) {
        vector<int> res;
        int mx = 0, cnt = 1;
        TreeNode *pre = NULL;
        inorder(root, pre, cnt, mx, res);
        return res;
}
    
void inorder(TreeNode* node, TreeNode*& pre, int& cnt, int& mx, vector<int>& res) {
        if (!node) return;
        inorder(node->left, pre, cnt, mx, res);
        if (pre) {
            cnt = (node->val == pre->val) ? cnt + 1 : 1;
        }
        if (cnt >= mx) {
            if (cnt > mx) res.clear();
            res.push_back(node->val);
            mx = cnt;
        } 
        pre = node;
        inorder(node->right, pre, cnt, mx, res);
}
```

#  二叉搜索树最小绝对差

```cpp
int getMinimumDifference(TreeNode* root) {
        int res = INT_MAX;
        helper(root, INT_MIN, INT_MAX, res);
        return res;
}
void helper(TreeNode* root, int low, int high, int& res) {
        if (!root) return;
        if (low != INT_MIN) res = min(res, root->val - low);
        if (high != INT_MAX) res = min(res, high - root->val);
        helper(root->left, low, root->val, res);
        helper(root->right, root->val, high, res);
}
```

# 二叉搜索树累加

```cpp
TreeNode* convertBST(TreeNode* root) {
    dfs(root);
    return root;
}
int sum = 0;
void dfs(TreeNode* root) {
    if (root == NULL) return ;
    dfs(root->right);
    root->val += sum;
    sum = root->val;
    dfs(root->left);
}
```
