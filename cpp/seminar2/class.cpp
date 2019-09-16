#include <iostream>

using namespace std;

class EnterPoint
{
private:
	int day, month, year;
	
public:
	EnterPoint(int date_day, int date_month, int date_year)
	{
		setDate(date_day, date_month, date_year);
	}
	void message()
	{
		cout << "Hello!" << endl;
	}
	void setDate(int date_day, int date_month, int date_year)
	{
		day = date_day;
		month = date_month;
		year = date_year;
	}
	void getDate()
	{
		cout << "Date: " << day << "." << month << "." << year << endl;
	}
	~EnterPoint()
	{
		cout << "My battery is low and it's getting dark" << endl;
	}
};

int main()
{
	int day, month, year;
	cout << "Enter current day through space" << endl;
	cin >> day >> month >> year;

	EnterPoint CurrentDate(1, 1, 1992);
	CurrentDate.message();
	CurrentDate.setDate(day, month, year);
	CurrentDate.getDate();

	return 0;
}
