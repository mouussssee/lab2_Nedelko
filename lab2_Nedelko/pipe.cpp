#include "pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include "utils.h"
using namespace std;

int pipe::max_indexp = 1;

std::istream& operator>>(std::istream& in, pipe& p)
{
	cout << "Index of the pipe: " << p.indexp << endl;
	cout << "Input name: ";	
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


void pipe::editPipe()
{
	if (length != 0) {
		cout << "ID of pipe: " << indexp << endl;
		//statusPipe(status);
		cout << "\nWrite a new status of pipe: \n0.if repairing \n1.if works" << endl;
		status = GetNumber(0, 1);
		//statusPipe(p.status);
	}
	else {
		cout << "You do not have a pipe!" << endl;
	}
}


void pipe::savePipe(std::ofstream& fout)
{
	fout << indexp << endl << name << endl << length << endl << diametr << endl << status << endl;
}

void pipe::loadPipe(std::ifstream& fin)
{
	fin >> indexp;
	getline(fin, name);
	getline(fin, name);
	fin >> length;
	fin >> diametr;
	fin >> status;
}