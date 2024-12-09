#include "cs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"

using namespace std;

int cs::max_indexcs = 1;

std::istream& operator>>(std::istream& in, cs& cs)
{
	cout << "Index of the CS: " << cs.indexcs << endl;
	cout << "Enter the name of the CS: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cs.name = GetName();
	cout << "Input the number of shops: ";
	cs.shop = GetNumber(1);
	cout << "Input the number of working shops: ";
	cs.workingShop = GetNumber(0, cs.shop);
	cout << "Enter CS efficiency (from 0 to 10): ";
	cs.effectiveness = GetNumber(0, 100);
	return in;
}

std::ostream& operator<<(std::ostream& out, cs& cs)
{
	out << "Index of CS: " << cs.indexcs << "\nCS info:\nName: " << cs.name << "\nNumber of workshops: " << cs.shop
		<< "\nNumber of working workshops: " << cs.workingShop << "\nEffectiveness: "
		<< cs.effectiveness << endl;
	return out;

}
