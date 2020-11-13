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

char Menu::GetInput(const char* mask)
{
	char res = 0;
	while (1) {
		res = tolower(getchar());
		while (getchar() != '\n');
		if (strchr(mask, res)) return res;
		cout << "No such command\nYour choice: ";
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
	getchar();
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
		char idx = 0;
		bool right = true;
		switch (choice)
		{
		case ORDINARY_GRAPH: 
		{

			if (!ReadGraph(this->ordinary_graph_))
			{
				break;
			}
			while (idx != '4')
			{
				this->ShowCapbility(this->ordinary_graph_);
				idx = this->GetInput("12345");
				switch (idx)
				{
				case ORDINARY_PRINT_TO_CONSOLE:
				{
					this->PrintToConsole(this->ordinary_graph_);
					break;
				}
				case ORDINARY_BACK_TO_MAIN_MENU:
				{
					break;
				}
				default:
					right = this->DoActionWithGraph(this->ordinary_graph_, idx);
				}
				if (!right)
				{
					system("pause");
					break;
				}
			}
			break;
		}
		case WEIGHT_GRAPH:
		{

			if (!ReadGraph(this->weight_graph_))
			{
				break;
			}
			while (idx != '3')
			{
				this->ShowCapbility(this->weight_graph_);
				idx = this->GetInput("1234");
				switch (idx)
				{
				case WEIGHT_PRINT_TO_CONSOLE:
				{
					this->PrintToConsole(this->weight_graph_);
					break;
				}
				case WEIGHT_BACK_TO_MENU:
				{
					break;
				}
				default:
					right = this->DoActionWithGraph(this->weight_graph_, idx);
				}
				if (!right)
				{
					system("pause");
					break;
				}
			}
			break;
		}
		case NETWORK:
		{

			if (!ReadGraph(this->network_))
			{
				break;
			}
			while (idx != '5')
			{
				this->ShowCapbility(this->network_);
				idx = this->GetInput("123456");
				switch (idx)
				{
				case NETWORK_PRINT_TO_CONSOLE:
				{
					this->PrintToConsole(this->network_);
					break;
				}
				case NETWORK_BACK_TO_MENU:
				{
					break;
				}
				default:
					right = this->DoActionWithGraph(this->network_, idx);
				}
				if (!right)
				{
					system("pause");
					break;
				}
			}
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
