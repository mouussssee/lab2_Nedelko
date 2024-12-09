#pragma once
#include <iostream>
#include <fstream>
#include <string>

class pipe
{
private:
    int length = 0, diametr = 0;
    int indexp = 1;
    std::string name = "";
public:
    static int max_indexp;
    bool status = 0;
    pipe();

    friend std::istream& operator >> (std::istream& in, pipe& p);
    friend std::ostream& operator << (std::ostream& out, pipe& p);
};

