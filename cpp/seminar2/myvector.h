class MyVector
{
private:
        double x, y, z;

public:
        MyVector(double x_coord, double y_coord, double z_coord);
	MyVector* add(const MyVector &B);
	MyVector* sub(const MyVector &B);
	double dot(const MyVector &B);
	double length();
	void print();
};
