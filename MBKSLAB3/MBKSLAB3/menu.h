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

enum MainCases
{
	ORDINARY_GRAPH = '1',
	WEIGHT_GRAPH,
	NETWORK,
	EXIT
};

enum  SpecialCases
{
	ORDINARY_PRINT_TO_CONSOLE = '3',
	ORDINARY_BACK_TO_MAIN_MENU,
	WEIGHT_PRINT_TO_CONSOLE = '2',
	WEIGHT_BACK_TO_MENU,
	NETWORK_PRINT_TO_CONSOLE = '4',
	NETWORK_BACK_TO_MENU
};

enum MyEnum
{

};

class Menu
{
public:
	Menu();
	~Menu();
	void CommunUser();
	bool ReadGraph(Graph& graph);
	void ShowCapbility(IResult &graph);
	bool DoActionWithGraph(IResult& graph,const char idx);
	void PrintToConsole(IResult& graph);
	void ClearResult(IResult& graph);

private:
	std::string menu;
	WeightGraph weight_graph_;
	OrdinaryGraph ordinary_graph_;
	Network network_;
	char GetInput(const char* mask);
};



#endif