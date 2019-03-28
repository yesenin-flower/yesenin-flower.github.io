#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<queue>
using namespace std;

struct order {
	string packno;
	string boxcode;
	pair<string, float> item;
	friend bool operator < (order o1, order o2) {
		if (o1.item.first > o2.item.first) return false;
		else if ((o1.item.first < o2.item.first)) return true;
		return o1.item.second < o2.item.second;
	}
}; 

int main() {
	priority_queue<order> orders;

	ifstream in("a.txt");
	if (!in.is_open()) return 1;
	string line = "";
	while (getline(in, line)){
		stringstream lineStream(line);
		string cell;
		order newOrder;
		if (getline(lineStream, cell, ',')) {
			newOrder.packno = cell;
		}
		if (getline(lineStream, cell, ',')) {
                        newOrder.boxcode = cell;
                }
		if (getline(lineStream, cell, ',')) {
			string itemcode = cell;
			float itemqty = INT_MAX;
			if (getline(lineStream, cell, ','))
				itemqty = stof(cell);
			cout<<itemqty<<" "<<cell<<"\n";
                        newOrder.item = make_pair(itemcode, itemqty);
                }
		orders.push(newOrder);
	}

	
	ofstream out("b.txt");
	if (!out.is_open()) return 1;
	while (!orders.empty()) {
		auto order = orders.top();
		orders.pop();
		//out<<order.packno<<","<<order.boxcode<<","<<order.item.first<<",";
		out<<"("<<order.item.first<<",";
		if (order.item.second == INT_MAX) {
			out<<"Missing)";
		} else {
			out<<order.item.second<<")";
		}
		out<<"["<<order.packno<<","<<order.boxcode<<"]\n";
	}
}
