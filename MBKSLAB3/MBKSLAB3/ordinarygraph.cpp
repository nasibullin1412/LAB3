#include "ordinarygraph.h"
#include <iostream>
using namespace std;

OrdinaryGraph::OrdinaryGraph(): Graph()
{
	this->graph_skeleton_ = nullptr;
	this->tops_deg_ = nullptr;
	this->is_count_edge_ = false;
	this->is_find_skeleton_ = false;
}

void OrdinaryGraph::Dfs(const size_t numb_top, bool* visited)
{
	size_t num_check_top = 0;
	visited[numb_top] = true;
	for (num_check_top = 0; num_check_top < this->matrix_row_; num_check_top++)
		if ((this->graph_matrix_[num_check_top] != 0) && (!visited[num_check_top]))
		{
			cout << numb_top + 1 << "-" << num_check_top + 1 << " ";
			this->Dfs(num_check_top, visited);
			this->graph_skeleton_[numb_top][num_check_top] += 1;
			this->graph_skeleton_[num_check_top][numb_top] += 1;
		}
}


bool OrdinaryGraph::FindSkeleton()
{
	bool* visited = new bool[this->matrix_row_];
	this->graph_skeleton_ = new unsigned short* [this->matrix_row_];
	if (visited == nullptr && this->graph_skeleton_ == nullptr)
	{
		if (visited)
		{
			delete[] visited;
		}
		cout << "Memory error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		visited[i] = false;
		this->graph_skeleton_[i] = new unsigned short[this->matrix_row_];
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			this->graph_skeleton_[i][j] = 0;
		}
	}
	cout << "The sequence of adding edges to the skeleton: ";
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->Dfs(i, visited);
	}
	delete[] visited;
	return true;
}

bool OrdinaryGraph::CountDeg()
{
	this->tops_deg_ = new unsigned short[this->matrix_row_ + 1];
	if (this->tops_deg_ == nullptr)
	{
		cout << "Memory error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		short deg = 0;
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			if (this->graph_matrix_[i][j] != 0)
			{
				deg += this->graph_matrix_[i][j];
			}
		}
		this->tops_deg_[i] = deg;
	}
	return true;
}

void OrdinaryGraph::Show—apabilities()
{
	cout << "\nYou can do with this graph: " << endl;
	cout << "1. Find skeleton" << endl;
	cout << "2. Count degree" << endl;
	cout << "3. Clear result" << endl;
	cout << "4. Write result to console" << endl;
	cout << "5. Exit to main menu" << endl;
}

bool OrdinaryGraph::DoActions(char idx)
{
	switch (idx)
	{
	case '1':
	{
		if (!this->is_find_skeleton_)
		{
			this->is_find_skeleton_ = this->FindSkeleton();
			return this->is_find_skeleton_;
		}
		return true;
	}
	case '2':
	{
		if (!this->is_count_edge_)
		{
			this->is_count_edge_ = this->CountDeg();
			return this->is_count_edge_;
		}
		return true;
	}
	default:
		return false;
	}
	
}

void OrdinaryGraph::PrintResultToConsole()
{
	if (this->is_find_skeleton_)
	{
		cout << "Graph Skeleton: " << endl;
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			for (size_t j = 0; j < this->matrix_row_; j++)
			{
				cout << this->graph_skeleton_[i][j];
				cout << " ";
			}
			cout << endl;
		}
	}
	if (this->is_count_edge_)
	{
		cout << "Tops degree: " << endl;
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			cout << this->tops_deg_[i] << ' ';
		}
	}
}

void OrdinaryGraph::ClearResult()
{
	this->~OrdinaryGraph();
}


OrdinaryGraph::~OrdinaryGraph()
{
	if (this->graph_skeleton_)
	{
		delete this->graph_skeleton_;
		this->graph_skeleton_ = nullptr;
	}
	if (this->tops_deg_)
	{
		delete this->tops_deg_;
		this->tops_deg_ = nullptr;
	}
	this->is_count_edge_ = false;
	this->is_find_skeleton_ = false;
}



