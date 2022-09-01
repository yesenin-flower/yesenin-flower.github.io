## 求绝对众数

绝对众数是指在数列 a中出现次数严格大于 N / 2 的数。
1. 快速排序之后在数列中间的数是绝对众数。
2. 摩尔投票法 
   在每一轮投票过程中，从数组中找出一对不同的元素，将其从数组中删除。循环执行这一操作，直到无法再进行投票，如果数组为空，则没有任何元素出现的次数超过该数组长度的一半（无绝对众数）。如果只存在一种元素，那么这个元素则可能为绝对众数。 

记m为候选绝对众数，出现次数为count，初始化为0。

```cpp
int majorityElement(vector<int>& nums) {
    int count = 0;
    int m = nums[0];
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (count == 0) {
            m = nums[i];
            count = 1;
        } else if (m == nums[i]) ++count;
        else --count;
    }
    return m;
}
```
## 求众数

## 计数质数

```cpp
int countPrimes(int n) {
    if (n < 2) return 0;
    bool prime[n+1] = {1};
    memset(prime,1,sizeof(prime));
    for (int i = 2; i < n; ++i) {
        if (prime[i]) {
            for(int j = i*2; j < n; j += i) {
                prime[j] = false;
            }
        }
    }
    int count = 0;
    for(int i = 2; i < n; ++i) {
        if(prime[i]) 
            ++count;
    }
    return count;
}
```
## 快乐数

发现当在迭代循环判断是否为1的过程中时，若进入了这种无限循环，最终都会出现4，故一旦遇见4即可知道进入了无限循环，判断是非快乐数字，减少了时间复杂度。

```cpp
bool isHappy(int n) {
    while (n != 1) {
        int res = 0, m;
        while (n) {
            m = n % 10;
            res += m * m;
            n = n / 10;
        }
        n = res;
        if (n == 4) return false;
    }
    return true;
}
```
## 最大公约数

gcd(a, b) = gcd(b, a %b)

```cpp
int gcd(int a, int b) {
    if (b == 0) 
        return a; 
    return gcd(b, a % b);
}
```
## 最小公倍数

lcm(a, b) = a * b / gcd(a, b)

## 质因子

先计算10010以内的素数。

素数从小到大循环计算是否是NUM的因子(== 0)，有多少个。

## 大整数 — 用数组存储

```cpp
vector<int> plusOne(vector<int>& digits) {
        int m = 1;
        for ( int i = digits.size() - 1; i>=0; --i ) {
            m += digits[i];
            digits[i] = m % 10;
            m = m / 10;
            if ( m == 0 ) break;
        }
        if ( m == 1 )
            digits.insert(digits.begin(), m);
        return digits;
}
```

## 组合数

![](https://ws1.sinaimg.cn/large/006tKfTcly1fr5fl5294rj308g01u74e.jpg)

递归，记录计算过的C(n, m)，以减少重复计算。

```cpp
int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
} 
  
// Returns factorial of n 
int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 
```

OR

```cpp
int comb(int n, int r) {
  long ans = 1;
  for (int i = 1, j = n - r + 1; i <= r; ++i, ++j) ans = ans * j / i;
  return ans;
}
```

### [排列数]()

```cpp
int permutation(int n,int m)
{
    int perm=factorial(n)/factorial(n-m);
    return perm;
}
```

## 阶乘后的0

n!有多少个质因子p，

```cpp
int trailingZeroes(int n, int p) {
    int sum=0;
    while(n>0){
        sum+=n/p;
        n/=p;
    }
    return sum;
}
```
因此 求 阶乘后的0：

要求末尾有多少个零，则该数应为x*10k 的形式等于x*（2k *5k），也就是求该数分解质因子后有几个5就行

## NIM游戏

```cpp
bool canWinNim(int n) {
    return n % 4 != 0;
}
```

## 回旋镖的数量

```cpp
int numberOfBoomerangs(vector<pair<int, int>>& points) {
    int res = 0;
    for (int i = 0; i < points.size(); ++i) {
        unordered_map<int, int> m;
        for (int j = 0; j < points.size(); ++j) {
            int a = points[i].first - points[j].first;
            int b = points[i].second - points[j].second;
            ++m[a * a + b * b];
        }
        for (auto it = m.begin(); it != m.end(); ++it) {
            res += it->second * (it->second - 1);
        }
    }
    return res;
}
```
## 第N个数字

```cpp
int findNthDigit(int n) {
    long digit = 1, ith = 1, base = 9;  
    while(n > base*digit)  
    {  
        n -= base*(digit++);  
        ith += base;  
        base *= 10;  
    }  
    return to_string(ith+(n-1)/digit)[(n-1)%digit]-'0';
}
```
## 随机数

rand3()生成 1- 3 的随机数，用其实现一个rand7()。

```cpp
int rand9() {
	int a = rand3();
	int b = rand3();
	return 3 * (a - 1) + b;
}
int rand7() {
    int a;
    do {
      a = rand9();
    } while(a > 7);
  	
    return a;
}
```

注意：

A. 类似的，有rand7生成rand5，就一直摇rand7，直到出现1-5。可以用等比数列证明，一定是等概率的。

B. 两个生成随机数的函数Randa， Randb。Randa和Randb分别产生1到a的随机数和1到b的随机数，a，b不相等。用Randa实现Randb：

1. 用Randa 构造Randak，如3就构造3\*1，3\*2...3\*k。

   构造方法是  Randa2 = 2 * (Randa – 1) + Randa， 表示生成1到a2 随机数的函数。如果a2 仍小于b，继教构造 Randa3 = a * (Randa – 1) + Randa…直到ak > b。

2. 用下面这个生成randb，一直摇Randak，直到出现的值是b的倍数

   ```cpp
   int Randb(){
       int x = ~(1<<31); // max int
       while(x > b*(ak/b)) // b(ak/b)表示最接近A且小于A的b的倍数
           x = Randak();
       return x%b + 1;
   }
   ```

C. 同理可构造Randab，生成1到a*b的随机数。

```cpp
Randab = b * (Randa - 1) + Randb;
Randab = a * (Randb - 1) + Randa;
```

D. 一般化，有一个随机生成a到b的函数， 用它去实现一个随机生成c到d的函数。可转化为一个生成1, b-a+1 的函数，实现1, d-c+1的函数。

```cpp
Randabk = (b-a+q) * (Randab - a) + Randab - a + 1;
```

## 最大三角形面积

[面积](https://en.wikipedia.org/wiki/Shoelace_formula):

![{\displaystyle \mathbf {A} ={\frac {1}{2}}{\begin{vmatrix}1&1&1\\x_{1}&x_{2}&x_{3}\\y_{1}&y_{2}&y_{3}\end{vmatrix}}}](https://wikimedia.org/api/rest_v1/media/math/render/svg/940282e9e70fada00cd4eba14532d09c6c9d3c54)

###[Valid Triangle Number]()

```cpp
int triangleNumber(vector<int>& v) {
    if (v.size() <3) return 0;
    sort(v.begin(), v.end());
    int res = 0;
    for (int i = 0; i < v.size() ; ++i) {
        for (int j = i+1; j < v.size(); ++j) {
            int target = v[i] + v[j];
            int l = j + 1, r = v.size()-1;
            while(l < r) {
                int med = (l + r) / 2;
                if (v[med] < target) l = med+1;
                else r = med;
            }
            if (r <= j) continue;
            if (v[r] >= target)
                res += r - j - 1;
            else if (v[r] < target)
                res += r - j;
            //cout<<i<<" "<<v[i]<<" "<<j<<" "<<v[j]<<" "<<r<<" "<<v[r]<<" "<<res<<endl;
        }
    }
    return res;
}
```
## 两个矩形重叠

```cpp
bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    return Math.max(rec1[0],rec2[0])<Math.min(rec1[2],rec2[2]) && Math.max(rec1[1],rec2[1])<Math.min(rec1[3],rec2[3]);
}
```

## 最大回文数乘积

```cpp
int largestPalindrome(int n) {
    if (n == 1) return 9;
    int maxn = pow(10, n) - 1;
    for (int i = maxn; i > maxn / 10; --i) {
        string s = to_string(i);
        reverse(s.begin(),s.end());
        s = to_string(i)+s;
        unsigned long pa = stol(s.c_str());
        int paj = pa / maxn;
        for (int j = maxn; paj < maxn; --j) {
            if (pa % j == 0) {
                return pa % 1337;
            }
            paj = pa / j;
        }
    }
}
```
## zigzag

```cpp
string convert(string s, int numRows) {
    if (nRows <= 1) return s;
    string res = "";
    int size = 2 * nRows - 2;
    for (int i = 0; i < nRows; ++i) {
        for (int j = i; j < s.size(); j += size) {
            res += s[j];
            int tmp = j + size - 2 * i;
            if (i != 0 && i != nRows - 1 && tmp < s.size()) res += s[tmp];
        }
    }
    return res;
}
```
## 加密解密

```cpp
// Encodes a URL to a shortened URL.
string encode(string longUrl) {
    int K;
    if (urltoindex.find(longUrl) != urltoindex.end()) {
        K = urltoindex[longUrl];
    } else K = ++size;
    urltoindex[longUrl] = K;
    indextourl[K] = longUrl;
    
    string res = "";
    while (K) {
        res += s[K % 62];
        K /= 62;
    }
    return res;
}

// Decodes a shortened URL to its original URL.
string decode(string shortUrl) {
    int K = s.find_first_of(shortUrl[0]);
    for (int i = 1; i < shortUrl.size(); ++i) {
        K = K*62 + s.find_first_of(shortUrl[i]);
    }
    return indextourl[K];
}

string s="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int size = 0;
map<string, int> urltoindex;
map<int, string> indextourl;
```

## [旋转图像](https://leetcode.com/problems/rotate-image/)

先对角线，再对折

另一种思路，找到对应关系，按对应关系移动

```cpp
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; ++i) {
        for (int j = i; j < n - i - 1; ++j) {
            int prev = matrix[i][j];
            int r1 = i, c1 = j;
            for (int k = 0; k < 4; ++k) {
                int r2 = c1, c2 = n - 1 - r1;
                //cout<<r1<<" "<<c1<<" "<<r2<<" "<<c2<<endl;
                int tmp = matrix[r2][c2];
                matrix[r2][c2] = prev;
                prev = tmp;
                r1 = r2;
                c1 = c2;
            }
        }
    }
}
```
### 1260. Shift 2D Grid

- Element at `grid[i][j]` moves to `grid[i][j + 1]`.
- Element at `grid[i][n - 1]` moves to `grid[i + 1][0]`.
- Element at `grid[m - 1][n - 1]` moves to `grid[0][0]`.

```cpp
vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size(),  n = grid[0].size(), mn = (m * n);
    if (k % mn == 0) return grid;
    vector<vector<int>> res(m, vector<int>(n, 0));
    for (int i = 0; i < mn; ++i) {
        int tmp = (i + k) % (mn);
        res[tmp/n][tmp%n] = grid[i/n][i%n]; 
    }
    return res;
}
```

## [平方数之和](https://leetcode-cn.com/problems/sum-of-square-numbers/)

```cpp
bool judgeSquareSum(int c) {
    int high = sqrt(c), low = 0;
    
    while (low <= high) { 
        int _h = high * high;
        int _l = low * low;
        if (_h + _l == c) {
            return true;
        } else if (_h + _l > c) {
            --high;
        } else {
            ++low;
        }
    }
    return false;
}
```
## [到达终点数字](https://leetcode-cn.com/problems/reach-a-number/)

首先由于对称性，target是正是负影响不大。

因为比如达到target=2=1-2+3.

如果是-2，那就是-2=-1+2-3

所以相当于是完全对称的一个选择。

那么不妨设这个target是正的（用abs函数）

所以我们尽量往右移动就可以达到目的地。

假设1+2+3+...+k=sum

如果sum=target，毫无疑问那么k就是最终答案。#1

如果sum>target，而且sum-target是一个偶数，那么我们可以翻转一个数字的符号来完成等式。

比如sum-target=4，那么我们把2变成-2，那么sum减小了4.

这是由于（1+2+3+...k）-（1-2+3...k）=4

也就是可以归结为：

当sum-target为偶数，1+...-（sum-target）/2+...+k=target，那么答案依然是k。#2

当sum-target为奇数，那么sum-target+1是一个偶数

类似#2的证明，1+...-(sum-target+1)/2+...k=target-1

此时再考虑k的奇偶性。

如果k是偶数并且k>sum-target+1

那么1+...-(sum-target+1)/2+....-(k/2)...+k+(k+1)=target

由#2相似可证，相当于在1+2....+k+(k+1)减去了sum-target+1和k。

等价于sum+（k+1）-sum+target-1-k=>target也就是答案是k+1.#3

如果k=sum-target+1，由#3可知依然是k+1.#4

如果k是奇数：

1+2+...-(sum-target+1)/2.....+k-(k+1)+(k+2)=sum-(sum-target+1)+1=target,

因此答案是k+2.#5

```cpp
int reachNumber(int target) {
    int t=abs(target);
    int s=0;
    int dis=0;
    while(dis<t){
        s++;
        dis+=s;
    }
    int dt=dis-t;
    if(dt%2==0)
        return s;
    else{
        if(s%2==0)
            return s+1;
        else
            return s+2;
    }
}
```
## 公平的糖果交换

```cpp
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        int sumsa = 0, sumsb = 0;
        for (auto i : A) {
            sumsa += i;
        }
        for (auto i : B) {
            sumsb += i;
        }
        int diff = (sumsb - sumsa)/2;
        vector<int> res;
        
        for (auto i : A) {
            if (find(B.begin(), B.end(), diff+i) != B.end()) {
                res.push_back(i);
                res.push_back(diff+i);
                return res;
            }
        }
        return res;
    }

```

## 三维形体的表面积

```cpp
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size(); if(n<=0) return 0;
        int m = grid[0].size(); if(m<=0) return 0;
        
        int res = 0;
        int dx[] = {1, 0, -1, 0};
        int dy[] = {0, 1, 0, -1};
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                //计算位置i，j贡献的表面积
                if(grid[i][j]<=0) continue;
                int tmp = 2+grid[i][j]*4; 
                for(int k=0; k<4; k++){
                    int tx=i+dx[k], ty=j+dy[k];
                    if(tx>=0 && tx<n && ty>=0 && ty<m){
                        tmp -= min(grid[i][j], grid[tx][ty]);
                    }
                }
                res += tmp;
            }
        }
        
        return res;
    }
```

## [最小差值 I](https://leetcode-cn.com/problems/smallest-range-i/)

```cpp
int smallestRangeI(vector<int>& A, int K) {
    if(A.length<1){
        return 0;
    }
    int max=A[0];
    int min=A[0];
    for(int i=1;i<A.length;i++){
        if(A[i]>max){
            max=A[i];
        }            
        if(A[i]<min){
            min=A[i];
        }
    }
    if(max-min<K*2){
        return 0;
    }else{
        return max-min-K*2;      
    }  
}
```

### [闰年](https://leetcode.com/problems/day-of-the-week/)

四年一闰，百年不闰，四百年再闰

(year % 4 == 0 && year % 100 !=0)||(year % 400 ==0 )

### [Reveal Cards In Increasing Order](https://leetcode.com/problems/reveal-cards-in-increasing-order/solution/)

[跨过一个未访问过的元素](https://blog.csdn.net/qq_24133491/article/details/84950456)

[反向递推初始序列](https://blog.csdn.net/InNoVaion_yu/article/details/88354023)

###[Pancake Sorting](https://blog.csdn.net/Orientliu96/article/details/103273797)

逐一将目前list中的最大数移到list的最后一位，最终完成变换。

###[Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

Given an array of integers `nums` containing `n + 1` integers where each integer is in the range `[1, n]` inclusive.

There is only **one duplicate number** in `nums`, return *this duplicate number*.

龟兔赛跑

```java
  public int findDuplicate(int[] nums) {
    // Find the intersection point of the two runners.
    int tortoise = nums[0];
    int hare = nums[0];
    do {
      tortoise = nums[tortoise];
      hare = nums[nums[hare]];
    } while (tortoise != hare);

    // Find the "entrance" to the cycle.
    tortoise = nums[0];
    while (tortoise != hare) {
      tortoise = nums[tortoise];
      hare = nums[hare];
    }

    return hare;
  }
```

### [Task Scheduler](https://leetcode.com/problems/task-scheduler/)

1. 如果有两种或两种以上的任务具有相同的最多的任务数，如：AAAABBBBCCDE，n=3。那么我们将具有相同个数的任务A和B视为一个任务对，最终满足要求的分配为：ABXXABXXABXXAB，剩余的任务在不违背要求间隔的情况下穿插进间隔位置即可，空缺位置补idle。
2. 由上面的分析我们可以得到最终需要最少的任务时间：**（最多任务数-1）\*（n + 1） + （相同最多任务的任务个数）**。

有上面的例子来说就是：(num(A)-1) * (3+1) + (2)。

其中，（最多任务数-1）*（n + 1）代表的是ABXXABXXABXX，（相同最多任务的任务个数）代表的是最后的AB.

最后，别忘了要对任务数求最大值，毕竟每个任务都是要调度一遍的

```cpp
    int leastInterval(vector<char>& tasks, int n) {
        if (n == 0) return tasks.size();
        vector<int> count(26, 0);        
        for (const char task : tasks) 
            ++count[task - 'A'];
        const int max_count = *max_element(count.begin(), count.end());
        size_t ans = (max_count - 1) * (n + 1);
        ans += count_if(count.begin(), count.end(),
                        [max_count](int c){ return c == max_count; });
        return max(tasks.size(), ans);
    }
```

###[Maximum Binary String After Change](https://leetcode.com/problems/maximum-binary-string-after-change/)

```
Operation 1: If the number contains the substring "00", you can replace it with "10".
For example, "00010" -> "10010"
Operation 2: If the number contains the substring "10", you can replace it with "01".
For example, "00010" -> "00001"
// 1) shift all '1's to right 
// 00000011
// 2) convert each '00' pair to '10',
//    only 1 '0' remains and and z-1 '0' change to '1'
string ans = string(st, '1') + string(z-1, '1') + "0" + string(en-st+1-z, '1') + string(n-1-en, '1');
//            prefix of '1's  +  z-1 '1's +  remaining '0' + remaining 1's    + suffix of 1's'        
```

```cpp
string maximumBinaryString(string binary) {
        int n = binary.size();
        string result = string(n, '1');
        int zero_count = count(binary.begin(), binary.end(), '0');
        if (zero_count == 0) {
            return result;
        }
        int first_zero = binary.find('0');
        result[first_zero+zero_count-1] = '0';
        return result;
}
```

### 29. Divide Two Integers

```cpp
int divide(int dividend, int divisor) {
  if (divisor == 1) return dividend;
  else if (dividend == INT_MIN && divisor == -1)  return INT_MAX;
  else if (dividend == INT_MAX && divisor == -1) return -INT_MAX;
  bool neg = (dividend < 0) ^ (divisor < 0);
  long _dividend = abs(dividend);
  long _divisor = abs(divisor);
  if (_divisor > _dividend) return 0;
  else if (_divisor == _dividend) return neg ? -1 :  1;
  int res = 0;
  for (int x = 31; x >= 0; --x) {
    if (_dividend >> x >= _divisor) {
      res += 1 << x;
      _dividend -= _divisor << x;
    }
  }
  //cout<<res<<" "<<_divisor<<endl;
  return neg ? -res :  res;
}
```

### 858. Mirror Reflection

```cpp
class Solution {
public:
    int mirrorReflection(int p, int q) {
        while (p % 2 == 0 && q % 2 == 0){ 
            p/=2;
            q/=2;
        }
        return 1 - p % 2 + q % 2;
    }
};
```

