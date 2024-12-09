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
	cs.name = GetName();
	cout << "Input the number of shops: ";
	cs.shop = GetNumber(1);
	cout << "Input the number of working shops: ";
	cs.workingShop = GetNumber(0, cs.shop);
	cout << "Enter CS efficiency (from 0 to 100): ";
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

void cs::editCS()
{
	if (shop != 0) {
		std::cout << "ID of CS: " << indexcs << endl;
		cout << "The number of shops: ";
		cout << shop << endl;
		cout << "The number of working shops: ";
		cout << workingShop << endl;
		cout << "\nWrite a new number of working shops:" << endl;
		workingShop = GetNumber(0, shop);
	}
	else {
		cout << "You do not have a CS!" << endl;
	}
}

void cs::saveCS(std::ofstream& fout)
{
	fout << indexcs << endl << name << endl << shop << endl << workingShop << endl << effectiveness << endl;
}

void cs::loadCS(ifstream& fin)
{
	fin >> indexcs;
	getline(fin, name);
	getline(fin, name);
	fin >> shop;
	fin >> workingShop;
	fin >> effectiveness;
}

