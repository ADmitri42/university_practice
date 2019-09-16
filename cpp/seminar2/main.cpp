#include <iostream>
#include "myvector.h"

using namespace std;

int main()
{
	double x, y, z;
	cout << "Vector a:" << endl;
	cin >> x >> y >> z;
	MyVector vector1(x, y, z);
	cout << "Vector b:" << endl;
	cin >> x >> y >> z;
	MyVector vector2(x, y, z);
	MyVector *sum = vector1.add(vector2);
	MyVector *diff = vector1.sub(vector2);
	double length = vector1.length();
	double scal = vector1.dot(vector2);
	cout << "Vector a: ";
	vector1.print();
	cout << "vector b: ";
	vector2.print();
	cout << "a + b: ";
	sum->print();
	cout << "a - b: ";
	diff->print();
	cout << "|a|=" << length << endl << "a.b=" << scal << endl;
	delete sum, diff;
	return 0;
}
