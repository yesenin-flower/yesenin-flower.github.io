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
# 最小深度

```cpp
int dfs2(TreeNode* root) {
    if (root == NULL) return 0;
    int left = dfs2(root->left);
    int right = dfs2(root->right);
    return (left == 0 || right == 0) ? left + right + 1 : left > right ? right + 1 : left + 1;  
}
```
