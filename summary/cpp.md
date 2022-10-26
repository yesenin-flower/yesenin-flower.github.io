

## vector

```cpp
vector<typename> v(list, list+length);
vector<int> v = {0,1};
vector<int> vect1{1, 2, 3, 4}; 
vector<pair<int,int> > vp;//注意>>是位移符号
vector<int> va[10];//10个vector<int>
vector<vector <int> > ivec(m ,vector<int>(n,0)); //m*n的二维vector，所有元素初始化为0

v.push_back(item);
v.insert(v.begin()+k,item);				//O(N)
v.erase(v.begin()+k);					//O(N)
v.erase(v.begin()+k,v.begin()+k2);		//O(N)
v.pop_back();							//O(1)
v.back();// last item
v.size();								//O(1)
v.clear();								//O(N)
v.resize(k);    //return v[0:k]

sort(v.begin(),v.end());
sort(freq.begin(), freq.end(), greater<int>());
//median should be out of function
sort(arr.begin(), arr.end(), [this](int a, int b){
  if(abs(a - median) != abs(b - median)) return abs(a - median) > abs(b - median);
  return a > b;
});
find(wordList.begin(), wordList.end(), endWord) == wordList.end()
```

 ## set

自动递增，去重

```cpp
set<typename> s;
std::vector<int> v;
std::unordered_set<int> s(v.begin(), v.end());

s.insert(item);							//O(logN)
s.erase(item);							//O(logN)
s.size();								//O(1)
s.clear();								//O(N)
s.merge(s);
s.upper_bound(item);  //第一个>item 的位置
s.lower_bound(item); //第一个>=item 的位置 std::set<int>::iterator
//*it

auto it = s.find(item);					//O(logN)
if (it != s.end()) 
	s.erase(it, s.end());

//set::rbegin() && set::rend() ++it
  
for(set<int>::iterator it=numSet.begin() ;it!=numSet.end();it++)
    {
        cout<<*it<<" occurs "<<endl;
    }
```

## map

```cpp
//Time complexity of map operations is O(Log n). while for unordered_map, it is O(1) on average.
  
map<typename1, typename2> mp;
map<typename1, typename2> tmp(mp);
map<int, string, greater <int> > mymap;

mp[key] = value;
mp.erase(key); //log(n)  unorder O(1)
mp.erase(mp.begin(),mp.end());
mp.size();
mp.clear();
mp.cout(key); //as find function
//mp: a b c d e
mp.lower_bound('b');   //the first element whose key is not less than k. //point->b
mp.upper_bound('d');   //pointing to the next element that is not less than k. //point->e

auto it = mp.find(item);
if (it != mp.end())
    cout<<it->first<<" "<<it->second;

bool less_second(const pair<T1, T2>& m1, const pair<T1, T2>& m2) {
  	return m1.second < m2.second;
}
vector<pair<int, int>> v(map.begin(),map.end());
sort(v.begin(),v.end(),less_second);
sort(v.begin(),v.end(),[this](pair<int, int> a, pair<int, int> b){
              return a.second < b.second;
            });

for(iter = _map.begin(); iter != _map.end(); iter++) {
  cout << iter->first << " : " << iter->second << endl;
}
```

## stack

```cpp
stack<typename> s;

s.push(item);
s.pop();//O(1)
s.top();
s.size();
s.empty();
```

## queue

```cpp
queue<typename> q;

q.push(item);
q.front();
q.back();
q.pop();//O(1)
q.empty();
q.size();
```

## priority_queue

```cpp
//complete binary tree
priority_queue<typename> pq;

pq.push(item);//O(log(N))
pq.top();//O(1)
pq.pop();//O(log(N))
pq.empty();
pq.size();

//typename越小优先级越大  min heap;
priority_queue<typename, vector<typename>, greater<int> > gpq;
//typename越大优先级越大
priority_queue<typename, vector<typename>, less<int> > lpq;
lpq.push();
lpq.top();
lpq.pop();
//结构体定义
struct name {
	typename t1;
 	typename t2;
  name(int _t1, char _t2) :t1(_t1), t2(_t2) {}
  friend bool operator < (name n1, name n2) {
    return n1.t1 < n2.t2;
  }
};
priority_queue<name> pq;
```

## Heap

```cpp
vector<int> ivec;
make_heap(ivec.begin(), ivec.end());
//第三个参数传入greater<int>()得到最小堆
make_heap(_First, _Last, _Comp);	

//先在容器里push，再在heap里push
ivec.push_back(99); 
push_heap(ivec.begin(), ivec.end());  

//先在heap里pop，再在容器里pop
pop_heap(ivec.begin(), ivec.end());
ivec.pop_back();  
```

## deque

```cpp
deque<typename> q;

q.push_back(item);
q.push_front(item);
q.pop_back();
q.pop_front();
q.front();
q.back();
q.empty();
q.size();
```

## pair

```cpp
pair<typename,typename> p1(item1, item2);
pair<typename,typename> p2 = make_pair(item1,item2);
p.first = item1;
p.second = item2;

p1 <= p2;	//先first后second
```

## string

```cpp
string str = "";


str += "1";
str == "1";							//true 字典序

str.length();						//O(1)
str.insert(pos, str2);				//O(N)
str.erase(pos, len);				//O(N)
str.erase(str.begin() + k);			//O(N)
str.erase(str.begin(), str.end());	//O(N)
str.clear();						//O(1)
str.substr(pos, len);				//O(len)
str.replace(pos, len, str2);		//O(N)
str.find(str2, pos);		!=string::npos				//O(nm)
str.find_first_of(c, pos);			//c中任意字符
str.find_first_not_of(c, pos);
str.find_last_of(c, pos);

reverse(str.begin(),str.end()); 
//char to string
string(1, 'a');

//repeat char
string(5,'a');

//int to string
to_string(item);
stringstream ss;
ss<<item;
ss.str();

//string to int
atoi(str.c_str());
//int to char
itoa(i);

//string to long
stol(s.c_str());
//string to int
std::stoi(s.c_str(), NULL, 10)
//int to char
a + '0';

//char array to string
char res[sz];
return string(res, sz);
```

## 常用函数

```cpp
typename a[k];
typename b[k];
memset(a,value,sizeof(a));
memcpy(b,a,sizeof(int)*k); 

//algorithm
max(x, y);
min(x, y);
swap(x, y);
abs(x);
floor(x);
ceil(x);
sqrt(pow(a, 2) + pow(b, 2));
reverse(it1, it2);
fill(a, a + k, value);
sort(it1, it2, cmp);
std::vector<int>::iterator it = lower_bound(data.begin(), data.end(), val); //[first, last) 第一个值>= val的元素
idx = it - data.begin();
upper_bound(first, last, val); //[first, last) 第一个值> val的元素
count(s.begin(),s.end(),'char');
rand(); //0-INTMAX
rand()%a+b; //b-a+b


CDialog* MyDialog = new CDialog;
// use MyDialog
delete MyDialog;

int* set = new int[100];
//use set[]
delete [] set;

UDType (*UDArr)[7] = new UDType[5][7];
// Use the array syntax to delete the array of objects.
delete [] UDArr;

struct blocknode
{
    unsigned int bsize;
    bool free;
    unsigned char *bptr;
    blocknode *next;
    blocknode *prev;
		blocknode():bsize(0), free(0), bptr(NULL), prev(NULL), next(NULL){};
    blocknode(unsigned int sz, unsigned char *b, bool f = true,
              blocknode *p = 0, blocknode *n = 0) :
              bsize(sz), free(f), bptr(b), prev(p), next(n) {}
};
```



### Exception

```cpp
class MyCustomException : public std::exception {
    public:
char * what () {
        return "Custom C++ Exception";
    }
};

try {
  std::string().at(1); // this generates an std::out_of_range
} catch(MyCustomException& e) {
  std::cout << e.what();
} catch(const std::exception& e) //it would not work if you pass by value
{
  std::cout << e.what();
} catch(...) {
  eptr = std::current_exception(); // capture
}
```



### class

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
public:
    Person() {}
    Person(string _n, int _a): name(_n), age(_a) {}
    virtual void getdata() {};
    virtual void putdata() {};
protected:
    string name;
    int age;
};

class Professor : public Person {
public:
    Professor() {}
    static int id1;
protected:
    int publications = 0, cur_id = 0;
    
    void getdata() {
        cin>>name>>age>>publications;
        cur_id = id1;
        id1 += 1;
    }
    void putdata() {
        std::cout<<this->name<<" "<<this->age<<" "<<publications<<" "<<cur_id<<endl;
    }
};

class Student : public Person {
public:
    Student() {}
    static int id2;
protected:
    int marks[6];
    int cur_id;
    
    void getdata() {
        cin>>name>>age;
        for (int i = 0; i < 6; ++i) {
            cin>>marks[i];
        }
        cur_id = id2;
        id2 += 1;
    }
    void putdata() {
        int ans = 0;
        for (auto m: marks) {
            ans += m;
        }
        std::cout<<this->name<<" "<<this->age<<" "<<ans<<" "<<cur_id<<endl;
    }
};
int Professor::id1 = 1;
int Student::id2 = 1;
```



