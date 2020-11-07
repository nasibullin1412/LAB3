#include "network.h"
#include <iostream>
#include <fstream>
using namespace std;

Network::Network(): Graph()
{
	this->max = 0;
	this->parent_ford_belman_ = nullptr;
	this->destination_max_min_ = nullptr;
	this->parent_max_min_ = nullptr;
	this->band_width_ = nullptr;
	this->find_ford_belman = false;
	this->find_max_flow_ = false;
	this->find_max_min_path_ = false;
	this->max_flow_ = 0;
}

Network::~Network()
{
	if (this->parent_ford_belman_)
	{
		delete this->parent_ford_belman_;
		this->parent_ford_belman_ = nullptr;
	}
	if (this->destination_max_min_)
	{
		delete this->destination_max_min_;
		this->destination_max_min_ = nullptr;
	}
	if (this->parent_max_min_)
	{
		delete this->parent_max_min_;
		this->parent_max_min_ = nullptr;
	}
	if (this->band_width_)
	{
		delete this->band_width_;
		this->band_width_ = nullptr;
	}
	this->max = 0;
	this->find_ford_belman = false;
	this->find_max_flow_ = false;
	this->find_max_min_path_ = false;
}

bool Network::FindMaxMinPath()
{
	this->parent_max_min_ = new size_t[this->matrix_row_];
	this->destination_max_min_ = new int[this->matrix_row_];
	if (this->parent_max_min_== nullptr || this->destination_max_min_ == nullptr)
	{
		cout << "Memory Error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->destination_max_min_[i] = 0;
		this->parent_max_min_[i] = 0;
	}
	size_t first = 0;
	size_t second = 0;
	cout << "Enter the vertex the path you want to find from: " << endl;
	cin >> first;
	cout << "Enter the vertex the path to which you want to find: " << endl;
	cin >> second;
	if (first > this->matrix_row_ || second > this->matrix_row_)
	{
		cout << "erorr" << endl;
		return false;
	}
	int* max_value_lot = new int[this->matrix_row_+1];
	bool* visited = new bool[this->matrix_row_];
	if (max_value_lot == nullptr || visited == nullptr)
	{
		cout << "Memory Error" << endl;
		return false;
	}
	size_t counts = 2;
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		max_value_lot[i] = -1;
		visited[i] = true;
	}
	max_value_lot[0] = first - 1;
	visited[first - 1] = false;
	int max = 0;
	int maxIdx = 0;
	cout << "S { ";
	for (size_t k = 0; k < counts - 1; k++)
	{
		cout << max_value_lot[k] + 1 << ' ';
	}
	cout << "} " << endl;
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->destination_max_min_[i] = this->graph_matrix_[first - 1][i];
		if (max < this->destination_max_min_[i])
		{
			max = this->destination_max_min_[i];
			maxIdx = i;
		}
	}
	cout << "D: ";
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << this->destination_max_min_[i] << ' ';
	}
	cout << endl;
	cout << "P: ";
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << this->parent_max_min_[i] + 1 << ' ';
	}
	cout << endl << endl;
	visited[maxIdx] = false;
	max_value_lot[1] = maxIdx;
	max = -myconst::infinity;
	maxIdx = 0;
	for (size_t i = 0; i < this->matrix_row_ - 2; i++)
	{
		cout << "S { ";
		for (size_t k = 0; k < counts; k++)
		{
			cout << max_value_lot[k] + 1 << ' ';
		}
		cout << "} " << endl;
		for (size_t k = 0; k < this->matrix_row_; k++)
		{
			if (visited[k] && this->graph_matrix_[max_value_lot[counts - 1]][k] != myconst::infinity)
			{
				if (this->graph_matrix_[max_value_lot[counts - 1]][k] > this->destination_max_min_[k])
				{
					if (this->graph_matrix_[max_value_lot[counts - 1]][k] < this->destination_max_min_[max_value_lot[counts - 1]])
					{
						this->destination_max_min_[k] = this->graph_matrix_[max_value_lot[counts - 1]][k];
					}
					else
					{
						this->destination_max_min_[k] = this->destination_max_min_[max_value_lot[counts - 1]];
					}
					this->parent_max_min_[k] = max_value_lot[counts - 1];
				}
			}
			if (this->destination_max_min_[k] > max && visited[k])
			{
				max = this->destination_max_min_[k];
				if (-max == myconst::infinity)
				{
					break;
				}
				maxIdx = k;
			}
		}
		if (-max == myconst::infinity)
		{
			break;
		}
		if (counts <= this->matrix_row_)
		{
			max_value_lot[counts] = maxIdx;
		}
		else
		{
			return false;
		}
		counts++;
		visited[maxIdx] = false;
		max = -myconst::infinity;
	}
	int i = second - 1;
	if (-(this->destination_max_min_[second - 1]) == myconst::infinity)
	{
		cout << endl;
		cout << "No path was found" << endl;
		return false;
	}
	while (i != first - 1)
	{
		cout << i + 1 << "<-";
		i = this->parent_max_min_[i];
	}
	cout << i + 1 << endl;
	cout << "Total weight: " << this->destination_max_min_[second - 1] << endl;
	delete[] max_value_lot;
	delete[] visited;
	return true;
}


size_t Network::min(const size_t first, const size_t second)
{
	if (first < second)
	{
		return first;
	}
	else
	{
		return second;
	}
}

int Network::FindMax()
{
	int max = -(myconst::infinity);
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			if (this->graph_matrix_[i][j] > max)
			{
				max = this->graph_matrix_[i][j];
			}
		}
	}
	return max;
}


int Network::FordFalkerson(int v, int dest, bool* visit, int flow)
{
	if (v == dest)
	{
		return flow;
	}
	visit[v] = true;
	int curf = 0;
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		if (this->band_width_[v][i] > 0 && !visit[i])
		{
			curf = this->FordFalkerson(i, dest, visit, min(this->band_width_[v][i], flow));
			if (curf > 0)
			{
				this->band_width_[v][i] -= curf;
				this->band_width_[i][v] += curf;
				return curf;
			}
		}
	}
	return 0;
}



bool Network::FindMaxFlow()
{
	int dest = -1;
	int source = -1;
	bool first = false;
	bool second = false;
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			if (this->graph_matrix_[i][j] != 0)
			{
				first = true;
			}
			if (this->graph_matrix_[j][i] != 0)
			{
				second = true;
			}
		}
		if (!first)
		{
			dest = i;
		}
		if (!second)
		{
			source = i;
		}
		first = false;
		second = false;
	}
	
	if (source == -1 || dest == -1)
	{
		cout << "Source or Destination was not founded" << endl;
		return false;
	}

	cout << "Source: " << source + 1 << endl;
	cout << "Destination: " << dest + 1 << endl;
	this->max_flow_ = 0;
	int temp = 0;
	this->band_width_ = new int* [this->matrix_row_];
	if (this->band_width_ == nullptr)
	{
		cout << "Memory error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->band_width_[i] = new int[this->matrix_row_];
		if (this->band_width_[i] == nullptr)
		{
			cout << "Memory error" << endl;
			return false;
		}
		for (size_t j = 0; j < this->matrix_row_; j++)
		{
			this->band_width_[i][j] = this->graph_matrix_[i][j];
		}
	}
	bool* visit = new bool[this->matrix_row_];
	if (visit == nullptr)
	{
		cout << "Memory error" << endl;
		return false;
	}
	int flow = this->FindMax();
	do
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			visit[i] = false;
		}
		temp = this->FordFalkerson(source, dest, visit, flow);
		this->max_flow_ += temp;
	} while (temp != 0);

	delete[] visit;

	return true;
}

bool Network::FordBelman()
{
	this->parent_ford_belman_ = new int[this->matrix_row_];
	if (this->parent_ford_belman_ == nullptr)
	{
		cout << "Memory error" << endl;
		return false;
	}

	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->parent_ford_belman_[i] = 0;
	}

	size_t first = 0;
	size_t second = 0;
	cout << "Enter the vertex the path you want to find from: " << endl;
	cin >> first;
	cout << "Enter the vertex the path to which you want to find: " << endl;
	cin >> second;
	if (first > this->matrix_row_ || second > this->matrix_row_)
	{
		cout << "erorr" << endl;
		return false;
	}
	bool check = true;
	--first;
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->top_array[first][i] = this->graph_matrix_[first][i];
		if (this->top_array[first][i] != myconst::infinity && first != i)
		{
			check = false;
		}
		this->parent_ford_belman_[i] = first;
	}
	if (check)
	{
		cout << "No path was found" << endl;
		return false;
	}
	cout << "D: ";
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << this->top_array[first][i] << ' ';
	}
	cout << endl; cout << "P: ";
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << this->parent_ford_belman_[i] + 1 << ' ';
	}
	cout << endl << endl;
	bool change = true;
	while (change)
	{
		change = false;
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			for (size_t j = 0; j < this->matrix_row_; j++)
			{
				if (this->graph_matrix_[j][i] != myconst::infinity && this->top_array[first][j] != myconst::infinity)
				{
					if (this->top_array[first][i] > this->top_array[first][j] + this->graph_matrix_[j][i])
					{
						this->top_array[first][i] = this->top_array[first][j] + this->graph_matrix_[j][i];
						this->parent_ford_belman_[i] = j;
						change = true;
					}
				}
			}
		}
	}
	int i = second - 1;
	if (this->top_array[first][second - 1] == myconst::infinity)
	{
		cout << "No path was found" << endl;
		return false;
	}
	while (i != first)
	{
		cout << i + 1 << "<-";
		i = this->parent_ford_belman_[i];
	}
	cout << i + 1 << endl;
	cout << "Total weight: " << this->top_array[first][second - 1] << endl;
	return true;
}


void Network::ShowÑapabilities()
{
	cout << "\nYou can do with this graph: " << endl;
	cout << "1. Find min distance from one top to other by Ford-Belman algorithm" << endl;
	cout << "2. Find maximum throughput from one top to other by max-min algorithm" << endl;
	cout << "3. Find maximum flow by Ford-Falkerson alghoritm" << endl;
	cout << "4. Clear result" << endl;
	cout << "5. Write result to console" << endl;
	cout << "6. Exit to main menu" << endl;
}


bool Network::DoActions(char idx)
{
	switch (idx)
	{
	case '1':
	{
		if (!this->find_ford_belman)
		{
			return this->find_ford_belman = this->FordBelman();
		}
		return true;
	}
	case '2':
	{
		if (!this->find_max_min_path_)
		{
			return this->find_max_min_path_ = this->FindMaxMinPath();
		}
		return true;
	}
	case '3':
	{
		if (!this->find_max_flow_)
		{
			return this->find_max_flow_ =  this->FindMaxFlow();
		}
		return true;
	}
	default:
		return false;
	}
}


void Network::PrintResultToConsole()
{
	if (this->find_ford_belman)
	{
		size_t first = -1;
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			size_t j = 0;
			for (j; j < this->matrix_row_; j++)
			{
				if (this->top_array[i][j] != 0)
				{
					break;
				}
			}
			if (j != this->matrix_row_)
			{
				first = i;
				break;
			}
		}
		if (first == -1)
		{
			return;
		}
		cout << "Ford-Belman Alghoritm result: " << endl;
		cout << "D: ";
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			cout << this->top_array[first][i] << ' ';
		}
		cout << endl;
		cout << "P: ";
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			cout << this->parent_ford_belman_[i] + 1 << ' ';
		}
		cout << endl << endl;
	}
	if (this->find_max_flow_)
	{
		cout << "Max flow:  " << endl;
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			for (size_t j = 0; j < this->matrix_row_; j++)
			{
				if (this->graph_matrix_[i][j] == 0)
				{
					cout << "0/0  ";
				}
				else
				{
					cout << this->band_width_[j][i] << "/" << this->graph_matrix_[i][j] << "  ";
				}
			}
			cout << endl;
		}
		cout << endl << endl;
		cout << "Value of max flow in network: " << this->max_flow_ << endl;
	}
	if (this->find_max_min_path_)
	{
		cout << "D: ";
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			cout << this->destination_max_min_[i] << ' ';
		}
		cout << endl;
		cout << "P: ";
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			cout << this->parent_max_min_[i] + 1 << ' ';
		}
		cout << endl << endl;
	}
}


void Network::ClearResult()
{
	this->~Network();
}
