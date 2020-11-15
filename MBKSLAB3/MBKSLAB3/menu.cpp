#include "menu.h"



Menu::Menu()
{
	this->menu = "Please select one of the graph:\n 1. Ordinary graph\n 2. Weighet graph\n 3. Network graph\n 4. Exit \nYour choice: ";
	WeightGraph weighet_graph;
	this->weight_graph_ = weighet_graph;
	OrdinaryGraph ordinary_graph;
	this->ordinary_graph_ = ordinary_graph;
	Network network;
	this->network_ = network;
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


void Menu::SecondMenu(IResult& graph, const std::string &mask)
{
	if (!ReadGraph(this->ordinary_graph_))
	{
		return;
	}
	char idx = 0;
	bool right = false;
	while (idx != BACK_TO_MAIN_MENU)
	{
		this->ShowCapbility(this->ordinary_graph_);
		idx = this->GetInput(mask);
		if (idx == PRINT_TO_CONSOLE)
		{
			this->PrintToConsole(this->ordinary_graph_);
		}
		else
		{
			if (idx == BACK_TO_MAIN_MENU)
			{
				return;
			}
			right = this->DoActionWithGraph(this->ordinary_graph_, idx);
			if (!right)
			{
				system("pause");
			}
		}
	
	}
}

bool Menu::ReadGraph(Graph& graph)
{
	if (graph.IsReaded())
	{
		cout << "Do you want read this graph again (y/n): ";
		char choice = this->GetInput("yn");
		if (choice == 'n')
		{
			return true;
		}
		graph.CleanResult();
	}
	if (!graph.ReadGraph())
	{
		cout << "Error Read Graph..." << endl;
		return false;
	}
	return true;
}

bool Menu::DoActionWithGraph(IResult& graph, const char idx)
{
	return graph.DoActions(idx);
}

void Menu::ShowCapbility(IResult& graph)
{
	graph.ShowÑapabilities();
}

void Menu::PrintToConsole(IResult& graph)
{
	graph.PrintResultToConsole();
}

void Menu::ClearResult(IResult &graph)
{
	graph.CleanResult();
}

void Menu::CommunUser()
{
	while (true)
	{
		system("cls");
		cout << this->menu;
		char choice = this->GetInput("1234");
		switch (choice)
		{
		case ORDINARY_GRAPH:
		{
			std::string mask = "1234";
			this->SecondMenu(this->ordinary_graph_, mask);
			break;
		}
		case WEIGHT_GRAPH:
		{
			std::string mask = "123";
			this->SecondMenu(this->weight_graph_, mask);
			break;
		}
		case NETWORK:
		{
			std::string mask = "12345";
			this->SecondMenu(this->network_, mask);
			break;
		}
		case EXIT:
			return;
		}
	}
}

Menu::~Menu()
{
	this->menu.~basic_string();
}
