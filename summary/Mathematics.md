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
绝对众数是指在数列 a中出现次数严格大于 N / 2 的数。
1. 快速排序之后在数列中间的数是绝对众数。
2. 摩尔投票法 
   在每一轮投票过程中，从数组中找出一对不同的元素，将其从数组中删除。循环执行这一操作，直到无法再进行投票，如果数组为空，则没有任何元素出现的次数超过该数组长度的一半（无绝对众数）。如果只存在一种元素，那么这个元素则可能为绝对众数。 

记m为候选绝对众数，出现次数为c，初始化为0。

遍历数组A：

若c==0，则m=A[i]；

若c≠0且m≠A[i]，则同时删掉m和A[i]；

若c≠0且m==A[i]，则c++;

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