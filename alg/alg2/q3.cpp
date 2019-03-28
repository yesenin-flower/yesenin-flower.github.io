#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<set>
#include<vector>
using namespace std;

set<string> readFile() {
	set<string> res;
	ifstream in("termDict.txt");
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

