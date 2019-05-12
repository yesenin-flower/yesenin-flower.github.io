## 对称二叉树

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
## 层次遍历

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
## 判断平衡二叉树

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
## 最小深度

```cpp
int dfs(TreeNode* root) {
    if (root == NULL) return 0;
    int left = dfs2(root->left);
    int right = dfs2(root->right);
    return (left == 0 || right == 0) ? left + right + 1 : left > right ? right + 1 : left + 1;  
}
```

## 二叉搜索树的最近公共祖先

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

## 路径之和

找出从上到下路径和等于sum的路径数，可从中间开始，可不到叶子结点。

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
## 二进制手表

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
## 二叉搜索树众数

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

## 二叉搜索树最小绝对差

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

## 累加二叉搜索树

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

## 根据二叉树创建字符串

```
输入: 二叉树: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

输出: "1(2(4))(3)"

解释: 原本将是“1(2(4)())(3())”，在你省略所有不必要的空括号对之后，它将是“1(2(4))(3)”。
```

```cpp
    string tree2str(TreeNode* t) {  
        PreOrderTraversal(t);  
        return ans;  
    } 
	string ans;  
    void PreOrderTraversal(TreeNode* root)//前序遍历  
    {  
        int left = 0;  
        if(root)  
        {  
            ans += to_string(root->val) ;  
            if(root->left != NULL)  
            {  
                left = 1;//标志位，是否有左节点  
                ans += '(';  
                PreOrderTraversal(root->left);  
                ans += ')';  
            }  
            if(root->right != NULL)  
            {  
                if(left == 0)//如果没有左节点就直接到又节点，说明应该输出一个()  
                    ans += "()";  
                ans += '(';  
                PreOrderTraversal(root->right);  
                ans += ')';  
            }  
        }  
    }  
```

## 两数之和  - 输入 BST

利用哈希表

```cpp
bool findTarget(TreeNode* root, int k) {
    if (!root) return false;
    unordered_set<int> s;
    return helper(root, k, s);
}
bool helper(TreeNode* node, int k, unordered_set<int>& s) {
    if (!node) return false;
    if (s.count(k - node->val)) return true;
    s.insert(node->val);
    return helper(node->left, k, s) || helper(node->right, k, s);
}
```
## 修剪二叉搜索树

```cpp
TreeNode* trimBST(TreeNode* root, int L, int R) {
    if( root == NULL )
        return NULL;
    if( root->val < L  )return trimBST(root->right,L,R);
    
    if(root->val > R )return trimBST(root->left,L,R);
    
    root->left = trimBST(root->left,L,R);
    root->right = trimBST(root->right,L,R);
       
    return root;
}
```
## 最长同值路径

```cpp
int longestUnivaluePath(TreeNode* root) {
    if (root == NULL) return 0;
    int c = dfs(root->left, root->val, 0) + dfs(root->right,root->val, 0);
    if (c > high) high = c;
    longestUnivaluePath(root->left);
    longestUnivaluePath(root->right);
    return high;
}
int high = 0;
int dfs(TreeNode* root, int pre, int c) {
    if (root == NULL) return c;
    if (root->val == pre) ++c;
    else return c;
    int l = dfs(root->left, pre, c);
    int r = dfs(root->right, pre, c);
    return max(l,r);
}
```

## 二叉树中第二小的节点

给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 `2` 或 `0`。如果一个节点有两个子节点的话，那么这个节点的值不大于它的子节点的值。 

```cpp
int findSecondMinimumValue(TreeNode* root) {
    int m = INT_MAX;
    dfs(root, root->val, m);
    return m == INT_MAX ? -1 : m;
}
void dfs(TreeNode* root, int m1, int& m2) {
    if (root == NULL) return;
    
    if (root->val > m1 && root->val < m2) m2 = root->val;
    else if (root->val >= m2) return;
    dfs(root->left, m1, m2);
    dfs(root->right, m1, m2);
}
```

## 打印二叉树

```cpp
vector<vector<string>> printTree(TreeNode* root) {  
    if (root == NULL) {  
        return {};  
    }  
    int height = getHeight(root);  
    int width = pow(2,height)-1;  
    vector<vector<string>> ret(height, vector<string>(width, ""));  
    printTree(root, 0, 0, width - 1, ret);  
    return ret;  
}  
int getHeight(TreeNode *root) {  
    if (root == NULL) {  
        return 0;  
    }  
    return max(getHeight(root->left), getHeight(root->right)) + 1;  
}  
void printTree(TreeNode *node, int level, int left, int right, vector<vector<string>> &ret) {  
    if (node == NULL) {  
        return;  
    }  
    int mid = left + (right - left) / 2;  
    ret[level][mid] = to_string(node->val);  
    printTree(node->left, level + 1, left, mid - 1, ret);       // print the left subtree  
    printTree(node->right, level + 1, mid + 1, right, ret);     // print the right subtree  
} 
```

## 二叉搜索树迭代器

```Cpp
BSTIterator(TreeNode *root) {
    push(root);
}
/** @return whether we have a next smallest number */
bool hasNext() {
    return !s.empty();
}
/** @return the next smallest number */
int next() {
    TreeNode * tmp = s.top();
    s.pop();  
    push(tmp->right);  
    return tmp->val;
}
private:
stack<TreeNode *> s;
void push(TreeNode *root) {
    while (root != NULL) {
        s.push(root);
        root = root->left;
    }
}
```
## 完全二叉树的节点个数

```cpp
int countNodes(TreeNode* root) {
    int hLeft = leftHeight(root);
    int hRight = rightHeight(root);
    if (hLeft == hRight) return pow(2, hLeft) - 1;
    return countNodes(root->left) + countNodes(root->right) + 1;
}
int leftHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + leftHeight(root->left);
}
int rightHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + rightHeight(root->right);
}
```

## [递增顺序查找树](https://leetcode-cn.com/problems/increasing-order-search-tree/)

```cpp
TreeNode* increasingBST(TreeNode* root) {
    return dfs(root, NULL);
}
TreeNode* dfs(TreeNode* root, TreeNode* pre) {
    if (root == NULL) return pre;
    
    TreeNode* tmp = dfs(root->left, root);
    root->left = NULL;
    root->right = dfs(root->right, pre);
    return tmp;
}
```