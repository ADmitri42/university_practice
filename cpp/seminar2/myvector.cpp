#include <math.h>
#include <iostream>
#include "myvector.h"


MyVector::MyVector(double x_coord, double y_coord, double z_coord)
{
	z = z_coord;
	x = x_coord;
	y = y_coord;
}
MyVector* MyVector::add(const MyVector &B)
{
	return new MyVector(x+B.x, y+B.y, z+B.z);
}
MyVector* MyVector::sub(const MyVector &B)
{
	return new MyVector(x-B.x, y-B.y, z-B.z);
}
double MyVector::dot(const MyVector &B)
{
	return x*B.x + y*B.y + z*B.z;
}
double MyVector::length()
{
	return sqrt(x*x + y*y + z*z);
}
void MyVector::print()
{
	std::cout << "Vector (" << x << ", " << y << ", " << z << ")" << std::endl;
}
