#pragma once
#include <iostream>
#include <fstream>
#include <string>

class pipe
{
private:
    int length = 0, diametr = 0;
    int indexp = 1;
    
public:
    std::string name = "";
    static int max_indexp;
    bool status = 0;
    pipe()
    {
        indexp = max_indexp++;
    }
    friend std::istream& operator >> (std::istream& in, pipe& p);
    friend std::ostream& operator << (std::ostream& out, pipe& p);
    void editPipe();
    //void statusPipe();
    int IdPipe() { return indexp; }
    void savePipe(std::ofstream&);
    void loadPipe(std::ifstream&);
};

