#include "weighet.h"
#include <iostream>
using namespace std;

WeightGraph::WeightGraph(): Graph()
{
	this->edge_list_ = nullptr;
	this->adj_matrix_skeleton_ = nullptr;
	this->numb_edge_ = 0;
	this->tot_min_weight_ = 0;
	this->is_find_skeleton_ = false;
}

void WeightGraph::PushTask(const Edge& new_elem, const size_t size)
{
	size_t count = 0;
	Edge temp;
	while (count < size && new_elem.GetWeight() >= this->edge_list_[count].GetWeight())
	{
		++count;
	}
	temp = edge_list_[count];
	edge_list_[count] = new_elem;
	size_t idx = size;
	while (count < idx)
	{
		this->edge_list_[idx] = this->edge_list_[idx - 1];
		--idx;
	}
	++count;
	this->edge_list_[count] = temp;
}

Edge& WeightGraph::PopTask(const size_t &size)
{
	return this->edge_list_[this->numb_edge_ - size];
}

bool WeightGraph::MinSkeletonKraskal()
{
	size_t* colors = new size_t[this->matrix_row_];
	if (colors == nullptr)
	{
		cout << "Memory Error" << endl;
		return false;
	}
	this->adj_matrix_skeleton_ = new size_t* [this->matrix_row_];
	if (this->adj_matrix_skeleton_ == nullptr)
	{
		if (colors)
		{
			delete[] colors;
		}
		cout << "Memory Error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->adj_matrix_skeleton_[i] = new size_t[this->matrix_row_];
		if (this->adj_matrix_skeleton_[i] == nullptr)
		{
			if (colors)
			{
				delete[] colors;
			}
			cout << "Memory Error" << endl;
			return false;
		}
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			this->adj_matrix_skeleton_[i][j] = 0;
		}
	}


	int count = 0;
	size_t size = 0;
	this->edge_list_ = new Edge[this->matrix_row_ * this->matrix_row_ / 2];
	if (this->edge_list_ == nullptr)
	{
		cout << "Memory Error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		colors[i] = i;
		for (size_t j = i; j < this->matrix_row_; j++)
		{
			if (this->graph_matrix_[i][j] != 0)
			{
				Edge temp;
				temp.SetFirstTop(i);
				temp.SetSecTop(j);
				temp.SetWeight(this->graph_matrix_[i][j]);
				this->PushTask(temp, size);
				++size;
			}
		}
	}

	this->numb_edge_ = size;
	while (size != 0)
	{
		Edge temp = this->PopTask(size);
		--size;
		int first = temp.GetFirstTop();
		int second = temp.GetSecTop();
		if (colors[first] != colors[second])
		{
			cout << first + 1 << "-" << second + 1 << " ";
			this->adj_matrix_skeleton_[first][second] = 1;
			this->adj_matrix_skeleton_[second][first] = 1;
			this->tot_min_weight_ += temp.GetWeight();
			int color = 0;
			if (colors[first] < colors[second])
			{
				color = colors[second];
				for (size_t k = 0; k < this->matrix_row_; k++)
				{
					if (colors[k] == color)
					{
						colors[k] = colors[first];
					}
				}
			}
			else
			{
				color = colors[first];
				for (size_t k = 0; k < this->matrix_row_; k++)
				{
					if (colors[k] == color)
					{
						colors[k] = colors[second];
					}
				}
			}
		}
	}
	if (colors)
	{
		delete[] colors;
	}
	return true;
}

void WeightGraph::PrintResultToConsole()
{
	if (!this->is_find_skeleton_)
	{
		return;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			cout << this->adj_matrix_skeleton_[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << "Weight: " << this->tot_min_weight_ << endl;
}

void WeightGraph::ShowÑapabilities()
{
	cout << "\nYou can do with this graph: " << endl;
	cout << "1. Find min skeleton of graph by Kruskal alghoritm" << endl;
	cout << "2. Write result to console" << endl;
	cout << "3. Exit to main menu" << endl;
}

bool WeightGraph::DoActions(const char idx)
{
	switch (idx)
	{
	case '1':
	{
		if (!this->is_find_skeleton_)
		{
			this->is_find_skeleton_ = this->MinSkeletonKraskal();
			if (!this->is_find_skeleton_)
			{
				this->CleanResult();
			}
			return this->is_find_skeleton_;
		}
		return true;
	}
	default:
		return false;
	}
	
}


void WeightGraph::CleanResult()
{
	if (this->edge_list_)
	{
		unsigned int size = this->matrix_row_ * this->matrix_row_ / 2;
		for (size_t i = 0; i < size; i++)
		{
			edge_list_[i].~Edge();
		}
		this->edge_list_ = nullptr;
	}
	if (this->adj_matrix_skeleton_)
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			delete[] this->adj_matrix_skeleton_[i];
		}
		delete[] this->adj_matrix_skeleton_;
	}
	this->numb_edge_ = 0;
	this->is_find_skeleton_ = false;
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




WeightGraph::~WeightGraph()
{
	if (this->edge_list_)
	{
		unsigned int size = this->matrix_row_ * this->matrix_row_ / 2;
		for (size_t i = 0; i < size; i++)
		{
			edge_list_[i].~Edge();
		}
		this->edge_list_ = nullptr;
	}
	if (this->adj_matrix_skeleton_)
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			delete[] this->adj_matrix_skeleton_[i];
		}
		delete[] this->adj_matrix_skeleton_;
	}
	this->numb_edge_ = 0;
	this->is_find_skeleton_ = false;
}
