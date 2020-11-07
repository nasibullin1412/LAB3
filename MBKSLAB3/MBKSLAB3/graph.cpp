#include "graph.h"
#include <fstream>
#include <iostream>
using namespace std;


Graph::Graph()
{
	this->top_array = new Top[100];
	if (top_array == nullptr)
	{
		top_array = nullptr;
	}
	this->graph_matrix_ = nullptr;
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}


bool Graph::ReadGraph()
{
	char buffer[myconst::max_file_content] = { '\0' };
	char name[myconst::max_file_name] = { '\0' };
	cout << "Enter name of file (less then 100 symbols): " << endl;
	cin >> name;
	if (name == nullptr)
	{
		cout << "Name is very big..." << endl;
		return false;
	}
	ifstream fin;
	fin.open(name);
	if (!fin.is_open())
	{
		cout << "Error open file" << endl;
		return false;
	}
	fin.getline(buffer, myconst::max_file_content);
	size_t idx = 1;
	this->matrix_row_++;
	while (idx != myconst::max_file_content && buffer[idx] != '\0')
	{
		if (buffer[idx] != ' ' && buffer[idx] != '-')
		{
			if (buffer[idx-1] < '0' || buffer[idx-1] > '9')
			{
				this->matrix_row_++;
			}
		}
		++idx;
	}
	fin.seekg(0);

	this->graph_matrix_ = new int* [this->matrix_row_];
	
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->graph_matrix_[i] = new int[this->matrix_row_];
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			char word[myconst::max_word_size] = { '\0' };
			fin >> word;
			this->graph_matrix_[i][j] = atoi(word);
		}
	}

	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		top_array[i].Init(this->matrix_row_, i);
	}

	cout << "Matrix, wich was readed: \n";
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			cout << this->graph_matrix_[i][j] << ' ';
		}
		cout << endl;
	}
	return true;
}

bool Graph::IsReaded()
{
	if (this->graph_matrix_)
	{
		return true;
	}
	return false;
}



Graph::~Graph()
{
	if (this->top_array != nullptr)
	{
		for (unsigned int i = 0; i < this->matrix_row_; i++)
		{
			this->top_array[i].~Top();
		}
	}
	if (this->graph_matrix_ != nullptr)
	{
		delete graph_matrix_;
		graph_matrix_ = nullptr;
	}
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}