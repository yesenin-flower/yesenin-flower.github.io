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

# 数组中只出现一次的数

```cpp
int singleNumber(vector<int>& nums) {
    int ret = 0;
    for (int i = 0; i<nums.size(); ++i) {
        ret ^= nums[i];
    }
    return ret;
}
```

# 两整数和

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
# 十六进制

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
# 汉明距离

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

# 补数

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

# 二进制位交替

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
