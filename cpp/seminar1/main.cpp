#include <iostream>
#include <string>

using namespace std;

struct pizza_t {
	string name;
	int diametr;
	double weight;
	string city;
};

int main() {
	pizza_t *pizza = new pizza_t;
	cout << "Welcome to Pizza The Hutt pizzeria" << endl;
	cout << "I will take your order" << endl;
	cout << "Which pizza do you want? ";
	getline(cin, pizza->name);
	cout << "Perfect\nWhat is the diameter? ";
	cin >> pizza->diametr;
	cout << "Cool\nWhat is the weight? ";
	cin >> pizza->weight;
	cout << "Perfect\nFrom what city? ";
	cin.ignore();
	getline(cin, pizza->city);
	cout << "Name: " << pizza->name << endl;
	cout << "Diametr: " << pizza->diametr << endl;
	cout << "Weight: " << pizza->weight << endl;
	cout << "City: " << pizza->city <<endl;
}
