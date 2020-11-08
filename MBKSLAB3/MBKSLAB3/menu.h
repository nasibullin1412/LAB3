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