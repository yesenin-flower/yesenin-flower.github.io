## 岛屿的最大面积

```cpp
int dfs(vector<vector<int>>& grid, int x0, int y0){  
    int n, m, sum=1;  
    n = grid.size();  
    m = grid[0].size();  
  
    grid[x0][y0] = 0; //当前元素设置为0，避免再次搜索到  
    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};  
  
    for(int i=0; i<4; i++){  
        int x = x0 + dir[i][0];  
        int y = y0 + dir[i][1];  
        if(x>=0&&x<n&&y>=0&&y<m&&grid[x][y]==1)  
            sum+=dfs(grid, x, y);  
    }  
    return sum;  
  
}  
int maxAreaOfIsland(vector<vector<int>>& grid)   
{  
    int mx = 0, n, m;  
    n = grid.size();  
    m = grid[0].size();  
    for(int i=0; i<n; i++)  
        for(int j=0; j<m; j++)  
        {  
            if(grid[i][j] == 1)     
                mx = max(dfs(grid,i,j), mx);  
        }  
    return mx;  
} 
```

## 生成括号

```cpp
void dfs(int n, int r, int l, string tmp, vector<string>& res) {
    if (r == l && r== n) {
        res.push_back(tmp);
        return;
    }
    if(r < n) {
        dfs(n, r+1, l, tmp+"(", res); 
    }
    if (l < r) {
        dfs(n, r, l+1, tmp+")", res); 
    }
}
```

###[Minimum Number of Vertices to Reach All Nodes]()

Such questions can be solved using the concept of indegree

All the nodes having indegree 0 can not be reached from any other vertex and therefore we have to include them in our answer

```cpp
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        set<int>s;
        vector<int>answer;


        // we insert the values having indegree more than 1
        for(int i=0;i<edges.size();i++){
            s.insert(edges[i][1]);
        }

        /// here we check for the missing value and whenever we find the such node we push it in our vector
        for(int i=0;i<n;i++){
            if(s.find(i)==s.end())answer.push_back(i);
        }
        return answer;
    }
```

### Min Cost to Connect All Points

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h1nkoyuq23j20pc0iwgm9.jpg" style="zoom:40%;" />



```cpp
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int mstCost = 0;
        int edgesUsed = 0;
        
        // Track nodes which are visited.
        vector<bool> inMST(n);
        
        vector<int> minDist(n, INT_MAX);
        minDist[0] = 0;
        
        while (edgesUsed < n) {
            int currMinEdge = INT_MAX;
            int currNode = -1;
            
            // Pick least weight node which is not in MST.
            for (int node = 0; node < n; ++node) {
                if (!inMST[node] && currMinEdge > minDist[node]) {
                    currMinEdge = minDist[node];
                    currNode = node;
                }
            }
            
            mstCost += currMinEdge;
            edgesUsed++;
            inMST[currNode] = true;
            
            // Update adjacent nodes of current node.
            for (int nextNode = 0; nextNode < n; ++nextNode) {
                int weight = abs(points[currNode][0] - points[nextNode][0]) + 
                             abs(points[currNode][1] - points[nextNode][1]);
                
                if (!inMST[nextNode] && minDist[nextNode] > weight) {
                    minDist[nextNode] = weight;
                }
            }
        }
        
        return mstCost;
    }
};
```

### if graph is Bipartite

Following is a simple algorithm to find out whether a given graph is Bipartite or not using Breadth First Search (BFS). 

1. Assign RED color to the source vertex (putting into set U). 
2. Color all the neighbors with BLUE color (putting into set V). 
3. Color all neighbor’s neighbor with RED color (putting into set U). 
4. This way, assign color to all vertices such that it satisfies all the constraints of m way coloring problem where m = 2. 
5. While assigning colors, if we find a neighbor which is colored with same color as current vertex, then the graph cannot be colored with 2 vertices (or graph is not Bipartite) 

### 399. Evaluate Division

```cpp
class Solution {
public:
void dfs(string start,string end,map<string,double>& mp,map<string,vector<string>>& graph,double& val,map<string,int>& visited,bool& found){
        visited[start]=1;
    
        if(found==true)
            return ;
        for(auto child:graph[start]){
            if(visited[child]!=1){
                // cout<<start<<" "<<child<<"\n";
                val*=mp[start+"->"+child];
                if(end==child){
                    // cout<<end<<" -- "<<child<<"\n";
                    found=true;
                    return ;
                }
                dfs(child,end,mp,graph,val,visited,found);
                if(found==true){
                    return ;
                }
                else{
                    val/=mp[start+"->"+child];
                }
            }
        }
       
        
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        vector<double> ans;
        map<string,double> mp;
        map<string,vector<string>> graph;
        for(int i=0;i<equations.size();i++){
            string u=equations[i][0];
            string v=equations[i][1];
            mp[u+"->"+v]=values[i];
            mp[v+"->"+u]=1/values[i];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        for(int i=0;i<queries.size();i++){
            string start=queries[i][0];
            string end=queries[i][1];
            if(graph.find(start)==graph.end()||graph.find(end)==graph.end()){
                ans.push_back(-1);
            }
            else{
                // ans.push_back(1);
                double val=1;
                map<string,int> visited;
                bool found=false;
                if(start==end) found=true;
                else dfs(start,end,mp,graph,val,visited,found);
                if(found==true) ans.push_back(val);
                else ans.push_back(-1);
            }
        }
        return ans;
    }
};
```

