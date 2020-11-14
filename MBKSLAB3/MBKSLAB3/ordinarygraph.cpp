#include "ordinarygraph.h"
#include <iostream>
using namespace std;

OrdinaryGraph::OrdinaryGraph(): Graph()
{
	this->graph_skeleton_;
	this->tops_deg_;
	this->is_count_edge_ = false;
	this->is_find_skeleton_ = false;
}

void OrdinaryGraph::Dfs(const size_t numb_top, std::vector<bool> &visited)
{
	size_t num_check_top = 0;
	visited[numb_top] = true;
	for (num_check_top = 0; num_check_top < this->matrix_row_; num_check_top++)
		if ((this->graph_matrix_[numb_top][num_check_top] != 0) && (!visited[num_check_top]))
		{
			cout << numb_top + 1 << "-" << num_check_top + 1 << " ";
			this->Dfs(num_check_top, visited);
			this->graph_skeleton_[numb_top][num_check_top] += 1;
			this->graph_skeleton_[num_check_top][numb_top] += 1;
		}
}


bool OrdinaryGraph::FindSkeleton()
{
	std::vector<bool>visited(this->matrix_row_);
	this->graph_skeleton_.resize(this->matrix_row_);
	if (visited.empty() && this->graph_skeleton_.empty())
	{
		if (visited.empty())
		{
			visited.clear();
		}
		cout << "Memory error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		visited[i] = false;
		this->graph_skeleton_[i].resize(this->matrix_row_);
		if (this->graph_skeleton_[i].empty())
		{
			cout << "Memory error" << endl;
			return false;
		}
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
	visited.clear();
	return true;
}

bool OrdinaryGraph::CountDeg()
{
	this->tops_deg_.resize(this->matrix_row_ + 1);
	if (this->tops_deg_.empty())
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
	cout << "3. Write result to console" << endl;
	cout << "4. Exit to main menu" << endl;
}

bool OrdinaryGraph::DoActions(const char idx)
{
	switch (idx)
	{
	case FIND_SKELETON_:
	{
		if (!this->is_find_skeleton_)
		{
			this->is_find_skeleton_ = this->FindSkeleton();
			if (!this->is_find_skeleton_)
			{
				this->CleanResult();
			}
			return this->is_find_skeleton_;
		}
		return true;
	}
	case COUNT_EDGE:
	{
		if (!this->is_count_edge_)
		{
			this->is_count_edge_ = this->CountDeg();
			if (!this->is_count_edge_)
			{
				this->CleanResult();
			}
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

void OrdinaryGraph::CleanResult()
{
	
	this->graph_skeleton_.clear();
	
	this->tops_deg_.clear();
	this->is_count_edge_ = false;
	this->is_find_skeleton_ = false;
	this->top_array.clear();


	this->graph_matrix_.clear();
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}


OrdinaryGraph::~OrdinaryGraph()
{

	this->graph_skeleton_.clear();
	this->tops_deg_.clear();
	this->is_count_edge_ = false;
	this->is_find_skeleton_ = false;
}



