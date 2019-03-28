#include <iostream>
#include <string>
using namespace std;

string _toHex(int k) {
	if (k > 10) return string(1, 'A' + k - 10);
	else return to_string(k);
}

string ToHex(int n) {
	string res = "";
	while (n >= 16) {
		int k = n % 16;
		res = _toHex(k) + res;
		n /= 16;
	}
	if (n != 0) res = _toHex(n % 16) + res;
	return res;
}

int main() {
	int n = 31;
	cin>>n;
	cout<<ToHex(n)<<"\n";
	return 1;
}
