#ifndef _MENU_H_
#define _MENU_H_
#pragma once
#include "weighet.h"
#include "ordinarygraph.h"
#include "result.h"
#include "network.h"
#include <string>
#include <iostream>
using namespace std;

enum class MainCases: char
{
	ORDINARY_GRAPH = '1',
	WEIGHT_GRAPH,
	NETWORK,
	EXIT
};

enum SpecialCases
{
	PRINT_TO_CONSOLE = '1',
	BACK_TO_MAIN_MENU
};

enum class GraphType: size_t
{
	ORDINARY_GRAPH = 0,
	WEIGHT_GRAPH,
	NETWORK_GRAPH
};

class Menu
{
public:
	Menu();
	~Menu();
	void CommunUser();
	void SecondMenu(const size_t choice, const std::string &mask);
	bool ReadGraph(const size_t choice);
	

private:
	std::string menu;
	std::vector<Graph *> graphs;
	char GetInput(const std::string  &mask);
};



#endif