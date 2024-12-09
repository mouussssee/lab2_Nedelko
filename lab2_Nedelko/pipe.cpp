#include "pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include "utils.h"
using namespace std;

std::istream& operator>>(std::istream& in, pipe& p)
{
	cout << "Index of the pipe: " << p.indexp << endl;
	cout << "Input name: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	p.name = GetName();
	cout << "Input lenght: ";
	p.length = GetNumber(1);
	cout << "Input diametr: ";
	p.diametr = GetNumber(1);
	cout << "Choose status of pipe:\n0.if repairing \n1.if works\n";
	p.status = GetNumber(0, 1);
	return in;
}

std::ostream& operator<<(std::ostream& out, pipe& p)
{
	out << "\nIndex of pipe: " << p.indexp << "\nPipe info: " << "\nName: " << p.name << "\nLenght: " << p.length << "\nDiameter : " << p.diametr
		<< "\nStatus: " << (p.status?"working":"in maintenance") << endl;
	return out;
}
