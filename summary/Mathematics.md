# 求绝对众数
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
# 求众数


# 计数质数

![](https://img-blog.csdn.net/20160201110938143)

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
# 快乐数

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
# 最大公约数

gcd(a, b) = gcd(b, a %b)

# 最小公倍数

lcm(a, b) = a * b / gcd(a, b)

# 质因子

先计算10010以内的素数。

素数从小到大循环计算是否是NUM的因子(== 0)，有多少个。

# 大整数 — 用数组存储

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

# 组合数

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

# 阶乘后的0

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