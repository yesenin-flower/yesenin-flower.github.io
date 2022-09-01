##  反转整数(溢出)

输入数值范围是 $ [−2^{31},  2^{31} − 1] $。根据这个假设，如果反转后的整数溢出，则返回 0。

注意判断溢出的方法。

```cpp
int reverse(int x) {
        int t = 0;
        while(x!=0){
            if (t>INT_MAX/10|t<INT_MIN/10)
                return 0;
            t = t*10 + x%10;
            //或者：
            //if (x < 0 && t > 0) return 0;
            //else if (x > 0 && t < 0) return 0;
            x /= 10;
        }
        return t;
}
```

### [Counting Bits](https://leetcode.com/problems/counting-bits/)

For every numbers **i** in the range **0 ≤ i ≤ num** calculate the number of 1's in their binary representation and return them as an array.

eg let X = 7and Y = 3, then 7 / 2 = 3;

7 -> 1 1 1 **number of set bit are 3**
3 -> 0 1 1 **number of set bit are 2**

another eg X = 12 and y = 6, then 12 / 2 = 6;

12 -> 1100 **number of set bit are 2**
6 -> 0110 **number of set bit are 2**

**if X is ODD**

- then the (LSB) Least Significant Bit will always be set and dividing by 2 means right shifting the number by 1 bit.
- so if last bit is set and right shift it by 1 bit than the last set bit will be lost.
- so when X is ODD, no of set bit in X = 1 + no of set bit in Y

**if X is Even**

- then *LSB will be equal to 0*, therefore even we do right shift by1 bit then only this 0 bit will be lost and no set bit got lost

- When we have X has Even, no of set bit in X = no of set bit in Y

```cpp
vector<int> countBits(int num) {
  vector<int>res(num+1);
  res[0]=0;
  for(int i=1;i<num+1;i++)
  {
    if(i%2!=0)
      res[i]=res[i/2]+1;
    else
      res[i]=res[i/2];
  }
  return res;
}
```

```cpp
vector<int> countBits(int num) {
    vector<int> res(num+1,0);
    for(int i=1;i<=num;i++){
        res[i]=res[i&(i-1)]+1;
    }
    return res; 
}
```

二进制长度

(int)log2(i)+1

###[Minimum Numbers of Function Calls to Make Target Array](https://zxi.mytechroad.com/blog/bit/leetcode-1558-minimum-numbers-of-function-calls-to-make-target-array/)

两种操作：1、对某一位+1；2、所有数*2

```cpp
  int minOperations(vector<int>& nums) {
    int ans = 0;
    int high = 0;
    for (int x : nums) {
        if (x!=0)
            high = max(high, (int)log2(x));
        ans += std::bitset<32>(x).count();
    }
    return ans + high;
  }
```



##  颠倒二进制位

```cpp
uint32_t reverseBits(uint32_t n) {
        uint32_t m=0;
        for(int i=0;i<32;i++){
            m<<=1;//m向左移1位；
            m = m|(n & 1);//m的末位设置为n的末位
            n>>=1;//n向右移1位
        }
        return m;
}
```

（1）&(与)–有0则0；无0则1； 

（2）|（或）–有1则1，无1则0； 

（3）^（亦或xor）–相同为0，不同为1； 

（4）>>右移（最右边的位被抛弃） 

正数，最左边添0；00001010>>3=00000001 

负数，最左边添1；10001010>>3=11110001 

（5）<<左移（最左边的位被抛弃）–最右边统一添0； 

（正数）00001010<<3=01010000 

（负数）10001010<<3=01010000 

##  二进制中1的个数

```cpp
int NumberOf1(int n)//有符号的n
{
    int count=0;
    int flag=1;
    while (flag)
    {
        if (n&flag)
        {
            count++;
        }
        flag=flag<<1;//左移一位
    }  
    return count;
}
```

##  数组中只出现一次的数

```cpp
int singleNumber(vector<int>& nums) {
    int ret = 0;
    for (int i = 0; i<nums.size(); ++i) {
        ret ^= nums[i];
    }
    return ret;
}
```

```cpp
vector<int> singleNumber(vector<int>& nums) {
  vector<int> result(2,0);
  int xor_res  = 0;
  for (int i = 0; i < nums.size();++i){
    xor_res ^= nums[i]; 
  }

  int mask = xor_res ^ ( xor_res & (xor_res-1) );

  int p=0;
  int q=0;
  for (int i=0;i<nums.size();++i){
    if ( (nums[i] & mask) == 0){
      p ^= nums[i];
    }else{
      q ^= nums[i];
    }
  }

  result[0] = p;
  result[1] = q;

  return result;
}
```

##  [缺失数字](https://leetcode-cn.com/problems/missing-number/)

```cpp
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int sum = n * (n + 1) / 2;
    
    for (int i = 0; i < nums.size(); ++i) {
        sum -= nums[i];
    }
    return sum;
}
//
int missingNumber(vector<int>& nums) {
    int ret = 0;
    for (int i = 0; i<nums.size(); ++i) {
        ret ^= nums[i];
        ret ^= i;
    }
    ret ^= nums.size();
    return ret;
}
```
[448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

```cpp
vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int>  result;
    for (int i = 0; i < nums.size(); ++i) {
        int index = abs(nums[i]) - 1;
        if (nums[index] > 0)
            nums[index] = -nums[index]; 
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            result.push_back(i+1);
        }
    }
    return result;
}
```
##  两整数和

```cpp
int getSum(int a, int b) {
    if(a==0) return b;  
    if(b==0) return a;  
    int sum,i;  
    i=a^b;  
    sum=(a&b)<<1;  
    return getSum(sum,i);  
}
```
##  十六进制

```cpp
char* hex = "0123456789abcdef";  
string toHex(int num) {  
    return toHexEx(num);  
}  
  
string toHexEx(unsigned int num) {  
    string s;  
    if (num > 15) {  
        unsigned int sub = num % 16;  
        s += hex[sub];  
        return toHexEx(num >> 4) + s;  
    } else {  
        s += hex[num];  
        return s;  
    }  
} 
```
##  汉明距离

```cpp
int hammingDistance(int x, int y) {
    int cnt = 0;
    
    while (x != 0 || y != 0) {
        if ((x & 1) ^ (y & 1)) ++cnt;
        x>>=1;
        y>>=1;
    }
    return cnt;
}
```

##  补数

```cpp
int findComplement(int num) {
     int mask = 1, temp = num;
     while(temp > 0) {
          mask = mask << 1;
          temp = temp >> 1;
     }
     return num^(mask-1);
}
```

##  二进制位交替

```cpp
bool hasAlternatingBits(int n) {
    int last = n & 1;
    n >>= 1;
    while (n) {
        int t = (n & 1);
        if (t == last) return false;
        last = t;
        n >>= 1;
    }
    return true;
}
```

##  汉明距离总和

```cpp
int totalHammingDistance(vector<int>& nums) {
    int res = 0, n = nums.size();
    for (int i = 0; i < 32; ++i) {
        int cnt = 0;
        for (int num : nums) {
            if (num & (1 << i)) ++cnt;
        }
        res += cnt * (n - cnt);
    }
    return res;
}
```

##  两数相除

```cpp
int divide(int dividend, int divisor) {
    long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
    if (m < n) return 0;    
    while (m >= n) {
        long long t = n, p = 1;
        while (m > (t << 1)) {
            t <<= 1;
            p <<= 1;
        }
        res += p;
        m -= t;
    }
    if ((dividend < 0) ^ (divisor < 0)) res = -res;
    return res > INT_MAX ? INT_MAX : res;
}
```

##  [可被 5 整除的二进制前缀](https://leetcode-cn.com/problems/binary-prefix-divisible-by-5/)

数值 * 2 那么他 % 5 的 商 * 2 余数 * 2 由于 商 * 除数的部分 根本不影响 取模的操作 所以只要存下 余数 供下一个值使用就可以了 这样就能避免数值溢出了

```cpp
vector<bool> prefixesDivBy5(vector<int>& A) {
    int sums = 0;
    vector<bool> res;
    for (int i = 0; i < A.size(); ++i) {
        sums = (sums<<1) + A[i];
        res.push_back(sums % 5 == 0);
        sums %= 5;
    }
    return res;
}
```

###[1442. Count Triplets That Can Form Two Arrays of Equal XOR](https://blog.csdn.net/qq_39378221/article/details/107054473)

给你一个整数数组 arr 。

现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。

a 和 b 定义如下：

- a = arr[i] ^ arr[i + 1] ^ … ^ arr[j - 1]
- b = arr[j] ^ arr[j + 1] ^ … ^ arr[k]

注意：^ 表示 按位异或 操作。

请返回能够令 a == b 成立的三元组 (i, j , k) 的数目



我们将a,b同时异或b就会发现，只要i到k的元素异或等于0，那么j取i,k之间的任意值都可以满足条件。

