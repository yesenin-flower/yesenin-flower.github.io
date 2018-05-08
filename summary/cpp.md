vector

sort(vector.begin(),vector.end())

vector.size()

vector.push_back(item)

a.clear()

a.insert(a.begin()+1,5);

------

map

auto it =  map.find(key);

if (it == map.end()){}

bool less_second(const myclass & m1, const myclass & m2) {

return m1.second < m2.second;

}

vector vec(map.begin(),map.end());

sort(vec.begin(),vec.end(),less_second);

------

stack

1. s.empty()               如果栈为空返回true，否则返回false  
2. s.size()                返回栈中元素的个数  
3. s.pop()                 删除栈顶元素但不返回其值  
4. s.top()                 返回栈顶的元素，但不删除该元素  
5. s.push()                在栈顶压入新元素  

------

queue

1. q.empty()               如果队列为空返回true，否则返回false  
2. q.size()                返回队列中元素的个数  
3. q.pop()                 删除队列首元素但不返回其值  
4. q.front()               返回队首元素的值，但不删除该元素  
5. q.push()                在队尾压入新元素  
6. q.back() 

------

string

reverse(str.begin(),str.end()); 

str.length();

string substr(int pos = 0,int n = npos) const;//返回pos开始的n个字符组成的字符串

int find_first_of(char c, int pos = 0) const;//从pos开始查找字符c第一次出现的位置

int find_first_not_of(char c, int pos = 0) const;

int find_last_of(char c, int pos = npos) const;

------

int to string

to_string();

stringstream ss;

ss<<item;

ss.str();

------

string to int

atoi(str.c_str())

------

memset(list,value,sizeof(list))