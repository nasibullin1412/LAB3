#include "weighet.h"
#include <iostream>
using namespace std;

WeightGraph::WeightGraph(): Graph()
{
	this->edge_list_;
	this->adj_matrix_skeleton_;
	this->numb_edge_ = 0;
	this->tot_min_weight_ = 0;
	this->is_find_skeleton_ = false;
}

void WeightGraph::PushTask(const Edge& new_elem, const size_t size)
{
	size_t count = 0;
	while (count < size && new_elem.GetWeight() > this->edge_list_[count].GetWeight())
	{
		++count;
	}
	vector<Edge>::iterator it;
	it = this->edge_list_.begin();
	this->edge_list_.insert(it + count, new_elem);
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
	this->adj_matrix_skeleton_.resize(this->matrix_row_);
	if (this->adj_matrix_skeleton_.empty())
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
		this->adj_matrix_skeleton_[i].resize(this->matrix_row_);
		if (this->adj_matrix_skeleton_[i].empty())
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


	//int count = 0;
	size_t size = 0;
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
		size_t first = temp.GetFirstTop();
		size_t second = temp.GetSecTop();
		if (colors[first] != colors[second])
		{
			cout << first + 1 << "-" << second + 1 << " ";
			this->adj_matrix_skeleton_[first][second] = 1;
			this->adj_matrix_skeleton_[second][first] = 1;
			this->tot_min_weight_ += temp.GetWeight();
			size_t color = 0;
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
	cout << "1. Write result to console" << endl;
	cout << "2. Exit to main menu" << endl;
	cout << "3. Find min skeleton of graph by Kruskal alghoritm" << endl;
	
}

bool WeightGraph::DoActions(const char idx)
{
	switch (idx)
	{
	case FIND_SKELETON:
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
	this->edge_list_.clear();
	this->adj_matrix_skeleton_.clear();
	this->numb_edge_ = 0;
	this->is_find_skeleton_ = false;
	this->top_array.clear();
	this->graph_matrix_.clear();
	this->matrix_row_ = 0;
	this->numb_edge_ = 0;
}




WeightGraph::~WeightGraph()
{
	this->edge_list_.clear();
	this->adj_matrix_skeleton_.clear();
	this->numb_edge_ = 0;
	this->is_find_skeleton_ = false;
}
