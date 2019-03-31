'''
问题3：输入一个词典termDict.txt，每行一个单词，同时输入一个不含空格的字符串，例如：ilovedthisgame，输出包含空格的英文句子，例如I love this game。
要求：
	•	编码实现该函数，如果有多种可能输出，输出所有可能
	•	建议先考虑整体流程，再进行优化，若时间有限，可使用部分伪代码
	•	分析并讨论：如果有多种可能输出，如何选择最有可能的输出

'''
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<set>
#include<vector>
using namespace std;

set<string> readFile() {
	set<string> res;
	ifstream in("test/termDict.txt");
	if (!in.is_open()) return res;
	string line = "";
	while (getline(in, line)){
		res.insert(line);
	}
	return res;
}

vector<string> _search(int _start, string input, set<string> dict){
	vector<string> res;
	for (int i = _start; i < input.size(); ++i) {
		string _tmp = input.substr(_start, i - _start + 1);
		if (dict.find(_tmp) != dict.end()) {
			res.push_back(_tmp);
	        } 
	}
	return res;
}

void findSentence(set<string> dict, string input, int start, vector<string>& res, string tmp) {
	if (start == input.size()) {
		res.push_back(tmp.substr(1, tmp.size()-1));
		return ;
	}
	for (int i = start; i < input.size(); ++i) {
		vector<string> _tmp = _search(i, input, dict);
		if (_tmp.size() != 0) {
			for (auto sub :  _tmp) {
				findSentence(dict, input, i + sub.size(), res, tmp +" "+ sub);
			}
		} 
		return;
	}
}

int main() {
	set<string> dict = readFile();
	string input;
	cin>>input;
	vector<string> res;
	string tmp = "";
	findSentence(dict, input, 0, res, tmp);
	for (auto item :  res) {
		cout<<item<<endl;
	}
}

