#include "menu.h"



Menu::Menu()
{
	this->menu = "Please select one of the graph:\n 1. Ordinary graph\n 2. Weighet graph\n 3. Network graph\n 4. Exit \nYour choice: ";
	Graph* p_ordinary_graph = new OrdinaryGraph();
	this->graphs.emplace_back(p_ordinary_graph);
	Graph* p_weighet_graph = new WeightGraph();
	this->graphs.emplace_back(p_weighet_graph);
	Graph* p_network = new Network();
	this->graphs.emplace_back(p_network);
}

char Menu::GetInput(const std::string &mask)
{
	std::string res;
	cin >> res;
	if (res.length() == 1)
	{
		if (mask.find(res) != std::string::npos)
		{
			return res[0];
		}
	}
	cout << "No such command\nYour choice: ";
	return 0;
}


void Menu::SecondMenu(const size_t choice, const std::string &mask)
{
	if (!ReadGraph(choice))
	{
		return;
	}
	char idx = 0;
	bool right = false;
	while (idx != BACK_TO_MAIN_MENU)
	{
		this->graphs[choice]->ShowÑapabilities();
		idx = this->GetInput(mask);
		if (idx == PRINT_TO_CONSOLE)
		{
			this->graphs[choice]->PrintResultToConsole();
		}
		else
		{
			if (idx == BACK_TO_MAIN_MENU)
			{
				return;
			}
			right = this->graphs[choice]->DoActions(idx);
			if (!right)
			{
				system("pause");
			}
		}
	
	}
}

bool Menu::ReadGraph(const size_t idx)
{
	if (this->graphs[idx]->IsReaded())
	{
		cout << "Do you want read this graph again (y/n): ";
		char choice = this->GetInput("yn");
		if (choice == 'n')
		{
			return true;
		}
		this->graphs[idx]->CleanResult();
	}
	if (!this->graphs[idx]->ReadGraph())
	{
		cout << "Error Read Graph..." << endl;
		return false;
	}
	return true;
}


void Menu::CommunUser()
{
	while (true)
	{
		system("cls");
		cout << this->menu;
		char choice = this->GetInput("1234");
		switch (static_cast<MainCases>(choice))
		{
		case MainCases::ORDINARY_GRAPH:
		{
			std::string mask = "1234";
			this->SecondMenu(static_cast<size_t>(GraphType::ORDINARY_GRAPH), mask);
			break;
		}
		case MainCases::WEIGHT_GRAPH:
		{
			std::string mask = "123";
			this->SecondMenu(static_cast<size_t>(GraphType::WEIGHT_GRAPH), mask);
			break;
		}
		case MainCases::NETWORK:
		{
			std::string mask = "12345";
			this->SecondMenu(static_cast<size_t>(GraphType::NETWORK_GRAPH), mask);
			break;
		}
		case MainCases::EXIT:
			return;
		}
	}
}

Menu::~Menu()
{
	this->menu.~basic_string();
	this->graphs.clear();
}
