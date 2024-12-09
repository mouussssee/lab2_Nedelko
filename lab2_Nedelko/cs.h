#pragma once
#include <iostream>
#include <fstream>
#include <string>

class cs
{
    std::string name = "";
    int shop = 0, workingShop = 0;
    int effectiveness = 0;
    int indexcs = 1;
public:
    static int max_indexcs;
    cs();
    friend std::istream& operator>> (std::istream& in, cs& cs);
    friend std::ostream& operator<< (std::ostream& out, cs& cs);
};

