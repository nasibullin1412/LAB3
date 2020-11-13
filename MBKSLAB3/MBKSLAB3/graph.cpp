#include "graph.h"
#include <fstream>
#include <iostream>
#include <array>
using namespace std;


Graph::Graph()
{
	this->top_array = nullptr;
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
	//char buffer[myconst::max_file_content] = { '\0' };
	//char name[myconst::max_file_name] = { '\0' };
	array<char, myconst::max_file_content>buffer = { '\0' };
	array<char, myconst::max_file_name>name = { '\0' };
	cout << "Enter name of file (less then 100 symbols): " << endl;
	cin >> name.data();
	if (name.size())
	{
		cout << "Name is very big..." << endl;
		return false;
	}
	ifstream fin;
	fin.open(name.data());
	if (!fin.is_open())
	{
		cout << "Error open file" << endl;
		return false;
	}
	fin.getline(buffer.data(), myconst::max_file_content);
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
	if (this->graph_matrix_ == nullptr)
	{
		cout << "Memory Error";
		return false;
	}
	
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->graph_matrix_[i] = new int[this->matrix_row_];
		if (this->graph_matrix_[i] == nullptr)
		{
			cout << "Memory Error";
			return false;
		}
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			char word[myconst::max_word_size] = { '\0' };
			fin >> word;
			this->graph_matrix_[i][j] = atoi(word);
		}
	}

	this->top_array = new Top[this->matrix_row_];
	if (this->top_array == nullptr)
	{
		cout << "Memory Error";
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		if (!top_array[i].Init(this->matrix_row_, i))
		{
			cout << "Memory Error";
			return false;
		}
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
		this->top_array = nullptr;
	}
	if (this->graph_matrix_ != nullptr)
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			delete[] this->graph_matrix_[i];
		}
		delete[] this->graph_matrix_;
		graph_matrix_ = nullptr;
	}
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}