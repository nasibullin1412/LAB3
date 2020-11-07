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

char Menu::get_input(const char* mask)
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
		char choice = this->get_input("yn");
		if (choice == 'n')
		{
			return true;
		}
		graph.ClearResult();
	}
	if (!graph.ReadGraph())
	{
		cout << "Error Read Graph..." << endl;
		return false;
	}
	return true;
}

void Menu::DoActionWithGraph(IResult& graph, const char idx)
{
	graph.DoActions(idx);
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
	graph.ClearResult();
}

void Menu::CommunUser()
{
	while (true)
	{

		system("cls");
		cout << this->menu;
		char choice = this->get_input("1234");
		char idx = 0;
		switch (choice)
		{
		case '1': 
		{

			if (!ReadGraph(this->ordinary_graph_))
			{
				break;
			}
			while (idx != '5')
			{
				this->ShowCapbility(this->ordinary_graph_);
				idx = this->get_input("12345");
				switch (idx)
				{
				case '3':
				{
					this->ClearResult(this->ordinary_graph_);
					break;
				}
				case '4':
				{
					this->PrintToConsole(this->ordinary_graph_);
					break;
				}
				case '5':
				{
					break;
				}
				default:
					this->DoActionWithGraph(this->ordinary_graph_, idx);
				}
			}
			break;
		}
		case '2':
		{

			if (!ReadGraph(this->weight_graph_))
			{
				break;
			}
			while (idx != '4')
			{
				this->ShowCapbility(this->weight_graph_);
				idx = this->get_input("1234");
				switch (idx)
				{
				case '2':
				{
					this->ClearResult(this->weight_graph_);
					break;
				}
				case '3':
				{
					this->PrintToConsole(this->weight_graph_);
					break;
				}
				case '4':
				{
					break;
				}
				default:
					this->DoActionWithGraph(this->weight_graph_, idx);
				}
			}
			break;
		}
		case '3':
		{

			if (!ReadGraph(this->network_))
			{
				break;
			}
			while (idx != '6')
			{
				this->ShowCapbility(this->network_);
				char idx = this->get_input("123456");
				switch (idx)
				{
				case '4':
				{
					this->ClearResult(this->network_);
					break;
				}
				case '5':
				{
					this->PrintToConsole(this->network_);
					break;
				}
				case '6':
				{
					break;
				}
				default:
					this->DoActionWithGraph(this->network_, idx);
				}
			}
			break;
		}
		case '4':
			return;
		}

	}
}

Menu::~Menu()
{
	this->menu.~basic_string();
	this->network_.~Network();
	this->ordinary_graph_.~OrdinaryGraph();
	this->weight_graph_.~WeightGraph();
}
