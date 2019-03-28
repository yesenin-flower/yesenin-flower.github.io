#include <iostream>
using namespace std;


double IntersectRect ( double top1, double bottom1, double left1, double right1, double top2, double bottom2, double left2, double right2 )
{
	int a = max(bottom1, bottom2);
	int b = min(top1, top2);
	int c = max(left1, left2);
	int d = min(right1, right2);
	cout<<a <<" "<<b <<" "<<c<<" "<<d<<endl;
	if (a < b && c < d) {
		return (b - a) * (d - c);
	}
	return 0;
}

int main() {
	cout<<IntersectRect(2, 0, 0, 2, 1, 0, 1, 3);
}

