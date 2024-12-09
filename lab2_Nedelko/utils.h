#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include "pipe.h"
#include "cs.h"

template <typename N>
N GetNumber(const N left_border = 0, const N right_border = std::numeric_limits<N>::max())
{
	N x;
	while (((std::cin >> x).fail()) || (std::cin.peek() != '\n') || (x < left_border) || (x > right_border))
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Wrong input! Please, input correct number:" << std::endl;
	}
	std::cerr << x << std::endl;
	return x;
}

std::string GetName();

template <typename T>
using filter_pipe = bool (*) (pipe& p, T par);

template <typename T>
std::vector <int> findPipeByParametr(std::unordered_map <int, pipe>&pipe_group, filter_pipe<T> f, T par)
{
	std::vector <int> id;
	for (auto& pipe : pipe_group) {
		if (f(pipe.second, par))
			id.push_back(pipe.second.IdPipe());
	}
	return id;
}

template <typename T>
using filter_cs = bool (*) (cs& cs, T par);

template <typename T>
std::vector <int> findCSByParametr(std::unordered_map <int, cs>& cs_group, filter_cs<T> f, T par)
{
	std::vector <int> id;
	for (auto& CS : cs_group)
	{
		if (f(CS.second, par))
			id.push_back(CS.second.IdCs());
	}
	return id;
}
