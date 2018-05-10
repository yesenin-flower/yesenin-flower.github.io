# vector

```cpp
vector<typename> v;
vector<pair<int,int> > vp;//注意>>是位移符号
vector<int> va[10];//10个vector<int>

v.push_back(item);
v.insert(v.begin()+k,item);				//O(N)
v.erase(v.begin()+k);					//O(N)
v.erase(v.begin()+k,v.begin()+k2);		//O(N)
v.popback();							//O(1)
v.size();								//O(1)
v.clear();								//O(N)

sort(v.begin(),v.end());

```

# set 

自动递增，去重

```cpp
set<typename> s;

s.insert(item);							//O(logN)
s.erase(item);							//O(logN)
s.size();								//O(1)
s.clear();								//O(N)

auto it = s.find(item);					//O(logN)
if (it != s.end()) 
	s.erase(it, s.end());
```

# map

```cpp
map<typename1, typename2> mp;

mp[key] = value;
mp.erase(key);
mp.erase(mp.begin(),mp.end());
mp.size();
mp.clear();

auto it = mp.find(item);
if (it != mp.end())
    cout<<it->first<<" "<<it->second;

bool less_second(const typename1& m1, const typename2& m2) {
  	return m1.second < m2.second;
}
vector v(map.begin(),map.end());
sort(v.begin(),v.end(),less_second);
```

# stack

```cpp
stack<typename> s;

s.push(item);
s.pop();
s.top();
s.size();
s.empty();
```

# queue

```cpp
queue<typename> q;

q.push(item);
q.front();
q.back();
q.pop();
q.empty();
q.size();
```

# priority_queue

```cpp
priority_queue<typename> pq;

pq.push(item);
pq.top();
pq.pop();
pq.empty();
pq.size();

//typename越小优先级越大
priority_queue<typename, vector<typename>, greater<int> > gpq;
//typename越大优先级越大
priority_queue<typename, vector<typename>, less<int> > lpq;
//结构体定义
struct name {
	typename t1;
 	typename t2;
  	friend bool operator < (name n1, name n2) {
      return n1.t1 < n2.t2;
  	}
};
priority_queue<name> pq;
```

# pair

```cpp
pair<typename,typename> p1(item1, item2);
pair<typename,typename> p2 = make_pair(item1,item2);
p.first = item1;
p.second = item2;

p1 <= p2;	//先first后second
```

# string

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
str.find(str2);						//O(nm)
str.find_first_of(c, pos);
str.find_first_not_of(c, pos);
str.find_last_of(c, pos);

reverse(str.begin(),str.end()); 

//int to string
to_string(item);
stringstream ss;
ss<<item;
ss.str();

//string to int
atoi(str.c_str())
```

# 常用函数

```cpp
memset(list,value,sizeof(list));

//algorithm
max(x, y);
min(x, y);
swap(x, y);
abs(x);
reverse(it1, it2);
fill(list, list + k, value);
sort(it1, it2, cmp);
lower_bound(first, last, val); //[first, last) 第一个值>= val的元素
upper_bound(first, last, val); //[first, last) 第一个值> val的元素
```


