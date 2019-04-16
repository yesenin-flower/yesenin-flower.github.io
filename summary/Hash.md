# 特殊等价字符串组
```cpp
class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) {
        set<pair<int, int> > res;
        int group = 0;
        for (auto i : A) {
            pair<int, int> tmp = split(i, A.size());
            if (res.find(tmp) == res.end()) {
                res.insert(tmp);
                ++group;
            }  
        }
        return group;
    }
private:
    pair<int, int> split(string str, int Asize) {
        int odd = 0;
        int even = 0;
        for (int i = 0; i < str.size(); ++i) {
            if (i % 2 == 0) {
                odd += str[i]*str[i];
            } else {
               even += str[i]*str[i];
            }
        }
        return make_pair(odd, even);
    }
};
```
