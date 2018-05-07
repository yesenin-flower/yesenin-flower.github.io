#include<stdio.h>
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

int PATB1001() {
	int n;
	cin>>n;
	int i = 0;
	while (n != 1) {
		if (n % 2 == 0) {
			n /= 2;
		} else {
			n = (3*n+1)/2;
		}
		++i;
	}
	return i;
}

bool less_second(const pair<int,int>& a, const pair<int,int>& b) {
	return a.second > b.second;
}
int PATB1032() {
	int n;
	cin>>n;
	map<int,int> res;
	while (n > 0) {
		--n;
		int k,v;
		cin>>k>>v;
		auto it = res.find(k);
		if (it == res.end()) {
			res[k] = v;
		} else {
			res[k] += v;
		}
	}
	vector< pair<int,int> > vec(res.begin(),res.end());
	sort(vec.begin(),vec.end(),less_second);
	return vec[0].second;
}
bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 !=0) || (year % 400 == 0);
}
int Codeup1928() { 
	string day1,day2;
	cin>>day1>>day2;
	int y1 = atoi(day1.substr(0,4).c_str()), y2 = atoi(day2.substr(0,4).c_str());
	int m1 = atoi(day1.substr(4,2).c_str()), m2 = atoi(day2.substr(4,2).c_str());
	int d1 = atoi(day1.substr(6,2).c_str()), d2 = atoi(day2.substr(6,2).c_str());
	cout<<y1<<" "<<y2<<endl;
	cout<<m1<<" "<<m2<<endl;
	cout<<d1<<" "<<d2<<endl;
	int md[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	int res = 0, start = 0;
	while (y1 != y2 || m1 != m2 || d1 != d2) {
		++d1;
		if (isLeap(y1)) {	
			if (m1 == 2 && (d1-1)/28 == 1) {
				++m1;
				d1 = 1;
			} else if ((d1-1)/md[m1-1] == 1) {
				++m1;
				d1 = 1;
			}
		} else if ((d1-1)/md[m1-1] == 1) {
				++m1;
				d1 = 1;
		}
		if (m1 == 13) {
			++y1;
			m1 = 1;
		}
		++res;
	}
	return res;
}

void B1008() {
	int m,n;
	cin>>n>>m;
	int A[n];
	for (int i = 0; i < n; ++i) {
		int tmp;
		cin>>tmp;
		A[i] = tmp;
	}
	for (int i = n-1; i >= n - m; --i) {
		int tmp = A[n-1];
		for (int j = n - 2; j >= 0; --j) {
			A[j+1] = A[j];
		}
		A[0] = tmp;
	}
	for (int i = 0; i < n; ++i) {
		cout<<A[i]<<" ";
	}
}

void B1018() {
	int n;
	cin>>n;
	int p1[3] = {0};
	int p2[3] = {0};
	map<char,int>  m;
	m['C'] = 0;
	m['J'] = 1;
	m['B'] = 2;
	char mp[3] = {'C', 'J', 'B'};
	int ba = 0;
	for (int i = 0; i < n; ++i) {
		char k1,k2;
		cin>>k1>>k2;
		//if (m[k2]-m[k1] == 1 || m[k2]-m[k1] == 2)
		if ((m[k1] + 1) % 3 == m[k2])
			++p1[m[k1]];		
		else if (m[k1]-m[k2] == 0)
			++ba;	
		else
			++p2[m[k2]];
	}
	int sum1 = 0, sum2 = 0;
	int max1 = 0, max2 = 0;
	for (int i = 0; i < 3; ++i) {
		sum1 += p1[i];
		sum2 += p2[i];
		if (p1[i] > p1[max1]) max1 = i;
		if (p2[i] > p2[max2]) max2 = i;
	}
	cout<< sum1 << " "<<ba<<" "<<sum2<<endl;
	cout<< sum2 << " "<<ba<<" "<<sum1<<endl;
	cout<< mp[max1] <<" "<<mp[max2]<<endl;
	
}

void A1046() {
	int N;
	cin>>N;
	int dis[N];
	int sum = 0;
	for (int i = 1; i <= N; ++i) {
		int tmp;
		cin>>tmp;
		sum += tmp;
		dis[i] = sum;
	}
	cin>>N;
	for (int i = 0; i < N; ++i) {
		int start, end;
		cin>>start>>end;
		if (start > end) swap(start,end);
		int tmp = dis[end-1] - dis[start - 1];
		tmp = min(tmp, sum - tmp);
		cout<<tmp<<endl;
        }
}
int main() {
	//cout<<PATB1001();
	//cout<<PATB1032();
	//cout<<Codeup1928();
	//B1008();
	//B1018();
	A1046();
}
