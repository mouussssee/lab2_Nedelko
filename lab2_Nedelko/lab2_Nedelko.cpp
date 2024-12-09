#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pipe.h"
#include "cs.h"
#include <unordered_map>
#include <unordered_set>
#include "utils.h"
#include "redirect_output_wrapper.h"
#include <format>
#include <chrono>
using namespace std;

ostream& operator<<(ostream& out, unordered_set <int>& par) {
	out << "Exiting id: ";
	for (auto& i : par) {
		out << i << " ";
	}
	out << endl;
	return out;
}

//проверки для поиска
bool testPipeName(pipe& p, string name) {
	return (p.name.find(name) != string::npos);
}

bool testPipeStatus(pipe& p, bool status) {
	return (p.status == status);
}

bool testCSName(cs& cs, string name) {
	return(cs.name.find(name) != string::npos);
}

bool testUnworking(cs& cs, double p) {
	return(cs.get_unused() == p);
}

//просмотр всех объектов
void viewAll(unordered_map<int, pipe>& pipe_group, unordered_map<int, cs>& cs_group) {
	if (pipe_group.size() != 0) {
		for (auto& pipe : pipe_group) {
			cout << pipe.second << endl;
		}
	}
	else {
		cout << "You don't have pipes!" << endl;
	}
	if (cs_group.size() != 0) {
		for (auto& CS : cs_group) {
			cout << CS.second << endl;
		}
	}
	else {
		cout << "You don't have CSs!" << endl;
	}
}

//поиск трубы
vector <int> searchPipe(unordered_map<int, pipe>pipe_group) {
	vector<int> idp;
	int x;
	cout << "Search pipe by: 1.name 2.status" << endl;
	x = GetNumber(1, 2);
	if (x == 1) {
		string name;
		cout << "Enter the name of pipe: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		idp = findPipeByParametr(pipe_group, testPipeName, name);
	}
	else {
		bool n;
		cout << "Enter the status of pipe(0 or 1): ";
		n = GetNumber(0, 1);
		idp = findPipeByParametr(pipe_group, testPipeStatus, n);
	}
	return idp;
}
//поиск КСки
vector<int>searchCS(unordered_map<int, cs>& cs_group) {
	int x;
	vector <int> idcs;
	cout << "Search CS by: 1.name 2.% of unused shops" << endl;
	x = GetNumber(1, 2);
	if (x == 1) {
		string name;
		cout << "Enter the name of CS: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		idcs = findCSByParametr(cs_group, testCSName, name);
	}
	else {
		double n;
		cout << "Enter the % of unused shops: ";
		n = GetNumber(0, 100);
		idcs = findCSByParametr(cs_group, testUnworking, n);
	}
	return idcs;
}
//добавление трубы
void addPipe(unordered_map<int, pipe>& pipe_group) {
	pipe p;
	cin >> p;
	pipe_group.insert({ p.IdPipe(),p });
}
//добавление КС
void addCS(unordered_map<int, cs>& cs_group) {
	cs cs;
	cin >> cs;
	cs_group.insert({ cs.IdCs(),cs });
}
//редактирование трубы
void editPipes(unordered_map<int, pipe>& pipe_group) {
	int edit;
	int id;
	int x;
	if (pipe_group.size() != 0) {
		cout << "1.Edit one pipe \n2.Edit pipes \n3.Delete pipe" << endl;
		edit = GetNumber(1, 3);
		if (edit == 1) {
			cout << "Your pipes: " << endl;
			for (auto& pipe : pipe_group) {
				cout << pipe.second << endl;
			}
			cout << "Choose id of pipe to edit: ";
			id = GetNumber(0, (int)pipe_group.size());
			if (pipe_group.find(id) != pipe_group.end()) {
				pipe_group[id].editPipe();
			}
			else {
				cout << "You don't have such pipe!" << endl;
			}
		}
		if (edit == 2) {
			bool n;
			vector <int> indexp;
			cout << "Choose pipes by 1.filter 2.id" << endl;
			x = GetNumber(1, 2);
			if (x == 1) {
				auto idp = searchPipe(pipe_group);
				if (idp.size() != 0) {
					cout << "Enter a new status of pipe: ";
					n = GetNumber(0, 1);
					for (auto& i : idp)
						pipe_group[i].status = n;
				}
				else {
					cout << "You don't have such pipe!" << endl;
				}
			}
			if (x == 2) {
				int n;
				int id;
				unordered_set <int> ids;
				cout << "Your pipes: " << endl;
				for (auto& pipe : pipe_group) {
					cout << pipe.second << endl;
				}
				cout << "Enter the number of id of pipes you want to edit: ";
				n = GetNumber(1, (int)pipe_group.size());
				cout << "Enter id of pipes: " << endl;
				for (int i = 0; ids.size() < n; i++) {
					id = GetNumber(0, pipe::max_indexp - 1);
					if (pipe_group.find(id) != pipe_group.end()) {
						ids.insert(id);
					}
					else {
						cout << "You don't have such pipe!" << endl;
					}
				}
				for (auto& i : ids)
					pipe_group[i].editPipe();
			}
		}
		if (edit == 3) {
			int k;
			int n;
			cout << "You want to delete:\n1.one pipe \n2. more than one pipe" << endl;
			k = GetNumber(1, 2);
			if (k == 1) {
				cout << "Your pipes: " << endl;
				for (auto& pipe : pipe_group) {
					cout << pipe.second << endl;
				}
				cout << "Enter the id of pipe you want to delete: ";
				n = GetNumber(0, pipe::max_indexp - 1);
				while (pipe_group.find(n) == pipe_group.end()) {
					cout << "You don't have such pipe!" << endl;
					n = GetNumber(0, pipe::max_indexp - 1);
				}
				pipe_group.erase(pipe_group.find(n));
			}
			else {
				unordered_set <int> ids;
				cout << "Delete by: 1.filter 2.id" << endl;
				int d = GetNumber(1, 2);
				if (d == 1) {
					auto idp = searchPipe(pipe_group);
					if (idp.size() != 0) {
						for (auto& i : idp) {
							pipe_group.erase(pipe_group.find(i));
						}
					}
					else {
						cout << "You don't have such pipe!";
					}
				}
				else {
					cout << "Your pipes: " << endl;
					for (auto& pipe : pipe_group) {
						cout << pipe.second << endl;
					}
					cout << "Input the id of pipes you want to delete: ";
					int s =GetNumber(0, pipe::max_indexp - 1);
					while (s != 0) {
						if (pipe_group.find(s) != pipe_group.end()) {
							ids.insert(s);
						}
						else
							cout << "You don't have such pipe!" << endl;
						s = GetNumber(0, pipe::max_indexp - 1);
					}
					for (auto& id : ids) {
						pipe_group.erase(pipe_group.find(id));
					}
				}
			}
		}
	}
	else {
		cout << "You don't have pipe to edit!" << endl;
	}
}
//редактирование КСки
void editCSs(unordered_map<int, cs>& cs_group) {
	vector <int> ids;
	int edit;
	int id;
	int x;
	if (cs_group.size() != 0) {
		cout << "1.Edit one CS \n2.Edit more CS \n3.Delete CS" << endl;
		edit = GetNumber(1, 3);
		if (edit == 1) {
			cout << "Your CS: " << endl;
			for (auto& i : cs_group) {
				cout << i.second << endl;
			}
			cout << "Enter ID of CS to edit: ";
			id = GetNumber(0, (int)cs_group.size());
			if (cs_group.find(id) != cs_group.end()) {
				cs_group[id].editCS();
			}
			else {
				cout << "You don't have such pipe!" << endl;
			}
		}
		if (edit == 2) {
			bool n;
			unordered_set <int> idk;
			cout << "Choose CS by 1.filter 2.id" << endl;
			x = GetNumber(1, 2);
			if (x == 1) {
				cout << "Your CS: " << endl;
				for (auto& CS : cs_group) {
					cout << CS.second << endl;
				}
				auto idp = searchCS(cs_group);
				if (idp.size() != 0) {
					for (auto& i : idp)
						cs_group[i].editCS();
				}
				else {
					cout << "You don't have such pipe!" << endl;
				}
			}
			if (x == 2) {
				int n;
				int y;
				cout << "Your CS: " << endl;
				for (auto& CS : cs_group) {
					cout << CS.second << endl;
				}
				cout << "Enter the number of CSs you want to edit: ";
				n = GetNumber(1, (int)cs_group.size());
				cout << "Enter id of CS: ";
				for (int i = 0; idk.size() < n; i++) {
					cin >> y;
					if (cs_group.find(y) != cs_group.end()) {
						idk.insert(y);
					}
					else {
						cout << "You don't have such CS!" << endl;
					}
				}
				for (auto& i : idk)
					cs_group[i].editCS();
			}
		}
		if (edit == 3) {
			int k;
			int n;
			cout << "You want to delete:\n1.one CS \n2. more than one CS: " << endl;
			k = GetNumber(1, 2);
			if (k == 1) {
				cout << "Your CS: " << endl;
				for (auto& CS : cs_group) {
					cout << CS.second << endl;
				}
				cout << "Enter the id of CS you want to delete: ";
				n = GetNumber(0, cs::max_indexcs - 1);
				while (cs_group.find(n) == cs_group.end()) {
					cout << "You don't have such CS!" << endl;
					n = GetNumber(0, cs::max_indexcs - 1);
				}
				cs_group.erase(cs_group.find(n));
			}
			else {
				unordered_set <int> ids;
				cout << "Delete by: 1.filter 2.id" << endl;
				int d = GetNumber(1, 2);
				if (d == 1) {
					auto idp = searchCS(cs_group);
					if (idp.size() != 0) {
						for (auto& i : idp) {
							cs_group.erase(cs_group.find(i));
						}
					}
					else {
						cout << "You don't have such pipe!";
					}
				}
				else {
					cout << "Your CS: " << endl;
					for (auto& CS : cs_group) {
						cout << CS.second << endl;
					}
					cout << "Input the id of CS you want to delete: ";
					int s = GetNumber(0, cs::max_indexcs - 1);
					while (s != 0) {
						if (cs_group.find(s) != cs_group.end()) {
							ids.insert(s);
						}
						else
							cout << "You don't have such CS!" << endl;
						s = GetNumber(0, cs::max_indexcs - 1);
					}
					for (auto& i : ids) {
						cs_group.erase(cs_group.find(i));
					}
				}
			}
		}
	}
	else {
		cout << "You don't have CS to edit!" << endl;
	}
}

//менюшка
void menu() {
	cout << "\nChoose operation:" << endl
		<< " 1.Add pipe" << endl
		<< " 2.Add CS" << endl
		<< " 3.View all objects" << endl
		<< " 4.Edit pipe" << endl
		<< " 5.Edit CS" << endl
		<< " 6.Save" << endl
		<< " 7.Download" << endl
		<< " 8.Search pipe" << endl
		<< " 9.Search CS" << endl
		<< " 0.Exit" << endl;
}
//загрузка в файл
void saveData(unordered_map<int, pipe>& pipe_group, unordered_map<int, cs>& cs_group) {
	string data;
	cout << "Enter the name of file: ";
	cin >> data;
	ofstream fout;
	fout.open(data + ".txt", ios::out);
	if (!fout) {
		cout << "ERROR! no no no" << endl;
	}
	else {
		fout << pipe_group.size() << " " << cs_group.size() << endl;
		for (auto pipe : pipe_group)
			pipe.second.savePipe(fout);
		for (auto CS : cs_group)
			CS.second.saveCS(fout);
		cout << "Your data is saved!" << endl;
	}
}
//выгрузка из файла
void loadData(unordered_map<int, pipe>& pipe_group, unordered_map<int, cs>& cs_group) {
	string data;
	int numberp, numbercs;
	pipe newp;
	cs newcs;
	cout << "Enter the name of file: ";
	cin >> data;
	ifstream fin;
	fin.open(data + ".txt", ios::out);
	if (!fin) {
		cout << "ERROR! no no no" << endl;
	}
	else {
		pipe::max_indexp = 1;
		cs::max_indexcs = 1;
		pipe_group.clear();
		cs_group.clear();
		fin >> numberp >> numbercs;
		for (int i = 0; i < numberp; i++) {
			newp.loadPipe(fin);
			pipe_group.insert({ newp.IdPipe(),newp });
			if (pipe::max_indexp <= newp.IdPipe()) {
				pipe::max_indexp = newp.IdPipe() + 1;
			}
		}
		for (int i = 0; i < numbercs; i++) {
			newcs.loadCS(fin);
			cs_group.insert({ newcs.IdCs(),newcs });
			if (cs::max_indexcs <= newcs.IdCs()) {
				cs::max_indexcs = newcs.IdCs() + 1;
			}
		}
		cout << "Your data is loaded!" << endl;
	}
}


int main()
{
    redirect_output_wrapper cer_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
    {
        cer_out.redirect(logfile);
    }

	int operation = -1;
	unordered_map<int, pipe> pipe_group;
	unordered_map<int, cs> cs_group;

	while (true) {
		menu();
		operation = GetNumber(0, 9);
		switch (operation) {
			//добавление трубы
		case 1: {
			addPipe(pipe_group);
			break;
		}
			  //добавление КС
		case 2: {
			addCS(cs_group);
			break;
		}
			  //просмотр всех объектов
		case 3: {
			viewAll(pipe_group, cs_group);
			break;
		}
			  // редактирование статуса трубы
		case 4: {
			editPipes(pipe_group);
			break;
		}
			  // редактирование количества рабочих цехов
		case 5: {
			editCSs(cs_group);
			break;
		}
			  // сохранение данных в блокнот
		case 6: {
			saveData(pipe_group, cs_group);
			break;
		}
			  // выгрузка данных из блокнота
		case 7: {
			loadData(pipe_group, cs_group);
			break;
		}
			  // поиск трубы
		case 8: {
			if (pipe_group.size() != 0) {
				auto p = searchPipe(pipe_group);
				if (p.size() != 0) {
					for (auto& i : p)
						cout << pipe_group[i] << endl;
				}
				else {
					cout << "You don't have such pipe!" << endl;
				}
			}
			else {
				cout << "You don't have a pipe!" << endl;
			}
		}
			  // поиск КСки
		case 9: {
			if (cs_group.size() != 0) {
				auto c = searchCS(cs_group);
				if (c.size() != 0) {
					for (auto& i : c)
						cout << cs_group[i] << endl;
				}
				else {
					cout << "You don't have such CS!" << endl;
				}
			}
			else {
				cout << "You don't have a CS!" << endl;
			}
			break;
		}
			  // выход 
		case 0: {
			return 0;
		}
		default: {
			cout << "Error!\nInput correct value!\n";
			break;
		}
		}
	}
}


