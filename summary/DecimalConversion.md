# 反转整数(溢出)

输入数值范围是 $ [−2^31,  2^31 − 1] $。根据这个假设，如果反转后的整数溢出，则返回 0。

注意判断溢出的方法。

```cpp
int reverse(int x) {
        int t = 0;
        while(x!=0){
            if (t>INT_MAX/10|t<INT_MIN/10)
                return 0;
            t = t*10 + x%10;
            x /= 10;
        }
        return t;
}
```

# 颠倒二进制位

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
（3）^（亦或）–相同为0，不同为1； 
（4）>>右移（最右边的位被抛弃） 
正数，最左边添0；00001010>>3=00000001 
负数，最左边添1；10001010>>3=11110001 
（5）<<左移（最左边的位被抛弃）–最右边统一添0； 
（正数）00001010<<3=01010000 
（负数）10001010<<3=01010000 

# 二进制中1的个数

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

#数组中只出现一次的数

```cpp
int singleNumber(vector<int>& nums) {
    int ret = 0;
    for (int i = 0; i<nums.size(); ++i) {
        ret ^= nums[i];
    }
    return ret;
}
```
