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

OR

```cpp
long long c(long long n, long long m) {
  long long ans = 1;
  for (long long i = 1; i <= m; i++) {
    ans = ans * (n - m + 1) / i;
  }
  return ans;
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

   构造方法是  Randa2 = a * (Randa – 1) + Randa， 表示生成1到a2 随机数的函数。如果a2 仍小于b，继教构造 Randa3 = a * (Randa2 – 1) + Randa…直到ak > b。

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

## 旋转图像

先对角线，再对折

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