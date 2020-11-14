#include "graph.h"
#include <fstream>
#include <iostream>
#include <array>
using namespace std;


Graph::Graph()
{

	this->top_array;
	this->graph_matrix_;
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}


bool Graph::ReadGraph()
{
	array<char, myconst::max_file_content>buffer = { '\0' };
	std::string name;
	cout << "Enter name of file (less then 100 symbols): " << endl;
	cin >> name;
	if (name.length() > myconst::max_file_name || name.length() == 0)
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
	fin.getline(buffer.data(), buffer.size());
	size_t idx = 1;
	this->matrix_row_++;
	while (idx != myconst::max_file_content && buffer[idx] != '\0')
	{
		if (buffer[idx] != ' ' && buffer[idx] != '-')
		{
			if (buffer[idx-1] < '0' || buffer[idx-1] > '9')
			{
				++this->matrix_row_;
			}
		}
		++idx;
	}
	
	fin.seekg(0);

	/*this->graph_matrix_ = new int* [this->matrix_row_];
*/
	this->graph_matrix_.resize(this->matrix_row_);
	if (this->graph_matrix_.empty())
	{
		cout << "Memory Error";
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		/*this->graph_matrix_[i] = new int[this->matrix_row_];
		if (this->graph_matrix_[i] == nullptr)
		{
			cout << "Memory Error";
			return false;
		}*/
		this->graph_matrix_[i].resize(this->matrix_row_);
		if (this->graph_matrix_[i].empty())
		{
			cout << "Memory Error";
			return false;
		}
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			string word;
			fin >> word;
			this->graph_matrix_[i][j]=atoi(word.c_str());
		}
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		Top init_top;
		this->top_array.emplace_back(init_top);
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
	return !this->graph_matrix_.empty();
}



Graph::~Graph()
{

	this->top_array.clear();
	this->graph_matrix_.clear();
	/*if (this->graph_matrix_ != nullptr)
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			delete[] this->graph_matrix_[i];
		}
		delete[] this->graph_matrix_;
		graph_matrix_ = nullptr;
	}*/
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}