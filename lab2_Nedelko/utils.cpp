#include "utils.h"
#include <iostream>
#include <string>

std::string GetName()
{
    std::string name;
    while (true)
    {
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, name);
        if (!name.empty())
        {
            return name;
        }
        else
        {
            std::cout << "Invalid input. Please input a valid name." << std::endl;
        }
    }
    return std::string();
}
