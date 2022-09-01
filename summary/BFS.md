运用场景:

1. 分层遍历

   1.1 一层层的遍历一个图、树、矩阵

   1.2 简单图的最短路径(简单图:所有边长一样)

2. 连通块问题

   2.1 通过图中一个点找到其他所有连通的点

   2.2 找到所有方案问题的一种非递归实现

3. 拓扑排序

   3.1 实现起来比DFS容易

### [01 Matrix](https://leetcode.com/problems/01-matrix/)

重复更新上下左右

```cpp
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
  vector<vector<int>> result(matrix.size(), vector<int>(matrix[0].size(),INT_MAX));
  queue<pair<int, int> > q;
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[0].size(); ++j) {
      if (matrix[i][j] == 0) {
        result[i][j] = 0;
        q.push(make_pair(i, j));
      } 
    }
  }
  int dir[4][2] = {{-1,0}, {0,1}, {0,-1}, {1,0}};
  while(!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();
    for (int i = 0; i < 4; ++i) {
      int r = cur.first + dir[i][0], c = cur.second + dir[i][1];
      if (r >= 0 && c >= 0 && r < matrix.size() && c < matrix[0].size()) {
        if (result[r][c] > result[cur.first][cur.second] + 1) {
          result[r][c] = result[cur.first][cur.second] + 1;
          q.push(make_pair(r, c));
        }
      }
    }
  }
  return result;
}
```

### [Word Ladder](https://leetcode.com/problems/word-ladder/)


```cpp
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    int n = wordList.size();
    if (n == 0)      return 0;
    //if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return 0;
    int endint = findend(wordList, endWord);
    if (endint == -1)    return 0;
    
    wordList.push_back(beginWord);
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i=0; i<n+1; i++){
        for(int j=i+1; j<n+1; j++){
            if(differCnt(wordList[i], wordList[j])){
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    queue<int> q;
    vector<bool> vis(n+1, false);
    q.push(n);
    vis[n] = true;
    int res = 0;
    while(!q.empty()){
        res += 1;
        int level = q.size();
        while (level > 0) {
            int tmp = q.front();
            q.pop();
            --level;
            for(auto item: graph[tmp]){
                if(!vis[item]){
                    if(wordList[item] == endWord)  return res+1;
                    vis[item] = true;
                    q.push(item);
                }
            }
        }
    }
    return 0;
}

int findend(vector<string>& wordList, string endWord){
    int n=wordList.size();
    for(int i=0; i<n; i++){
        if(wordList[i] == endWord){
            return i;
        }
    }
    return -1;
}
bool differCnt(string &a, string &b){
    int cnt=0, n=a.length();
    for(int i=0; i<n; i++){
        if(a[i] != b[i]){
            cnt++;
            if(cnt>1)   return false;
        }
    }
    return cnt == 1;
}
```

```cpp
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> res;
    unordered_set<string> dict(wordList.begin(), wordList.end());
    vector<string> p{beginWord};
    queue<vector<string>> paths;
    paths.push(p);
    int level = 1, minLevel = INT_MAX;
    unordered_set<string> words;
    while (!paths.empty()) {
        auto t = paths.front(); paths.pop();
        if (t.size() > level) {
            for (string w : words) dict.erase(w);
            words.clear();
            level = t.size();
            if (level > minLevel) break;
        }
        string last = t.back();
        for (int i = 0; i < last.size(); ++i) {
            string newLast = last;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                newLast[i] = ch;
                if (!dict.count(newLast)) continue;
                words.insert(newLast);
                vector<string> nextPath = t;
                nextPath.push_back(newLast);
                if (newLast == endWord) {
                    res.push_back(nextPath);
                    minLevel = level;
                } else paths.push(nextPath);
            }
        }
    }
    return res;
}
```

### [1625. Lexicographically Smallest String After Applying Operations](https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/)

```cpp
string add(string s, int a) {
  int n = s.size();
  bool flag = true;
  for(int i = n-1; i >= 0; i--) {
    if(flag) {
      int val = a + (s[i] - '0');
      val = val % 10;
      s[i] = val + '0';
      flag = false;
    }
    else
      flag = true;
  }
  return s;
}
void dfs(string s, int a, int b, string& ans, unordered_set<string>& mark) {
  if(mark.find(s) != mark.end())
    return;
  mark.insert(s);
  ans = min(ans, s);
  dfs(s.substr(b) + s.substr(0, b), a, b, ans, mark);
  dfs(add(s, a), a, b, ans, mark);
}
string findLexSmallestString(string s, int a, int b) {
  unordered_set<string> mark;
  string ans = s;
  dfs(s, a, b, ans, mark);
  return ans;

}
```

### 开锁

```cpp
vector<string> neighbors(const string& code) {
    vector<string> result;
    for (int i = 0; i < 4; i++) {
        for (int diff = -1; diff <= 1; diff += 2) {
            string nei = code;
            nei[i] = (nei[i] - '0' + diff + 10) % 10 + '0';
            result.push_back(nei);
        }
    }
    return result;
}

int openLock(vector<string>& deadends, string target) {
    unordered_set<string> deadSet(deadends.begin(), deadends.end());
    if (deadSet.count("0000")) return -1;
    queue<string> q;
    q.push("0000");
    int res =0;
    while (!q.empty()) {
        int level = q.size();
        while (level > 0) {
            string cur = q.front();
            q.pop();
            cout<<cur<<endl;
            if (cur == target) return res;
            for (auto nei : neighbors(cur)) {
                if (deadSet.count(nei)) continue;
                deadSet.insert(nei); // Marked as visited
                q.push(nei);
            }
            --level;
        }
        res += 1;
    }
    return -1;
}
```