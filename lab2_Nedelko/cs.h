#pragma once
#include <iostream>
#include <fstream>
#include <string>

class cs
{
    int shop = 0, workingShop = 0;
    int effectiveness = 0;
    int indexcs = 1;
public:
    std::string name = "";
    static int max_indexcs;
    cs()
    {
        indexcs = max_indexcs++;
    }
    friend std::istream& operator>> (std::istream& in, cs& cs);
    friend std::ostream& operator<< (std::ostream& out, cs& cs);
    void editCS();
    void saveCS(std::ofstream& file);
    void loadCS(std::ifstream& file);
    int IdCs() { return indexcs; }
    double get_unused() { return (((double)shop - (double)workingShop) / (double)shop) * 100; }
};

