#include "network.h"
#include <iostream>
#include <fstream>
using namespace std;

Network::Network(): Graph()
{
	this->max = 0;
	this->parent_ford_belman_ = nullptr;
	this->distance_max_min_ = nullptr;
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
	if (this->distance_max_min_)
	{
		delete this->distance_max_min_;
		this->distance_max_min_ = nullptr;
	}
	if (this->parent_max_min_)
	{
		delete this->parent_max_min_;
		this->parent_max_min_ = nullptr;
	}
	if (this->band_width_)
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			delete[] this->band_width_[i];
		}
		delete[] this->band_width_;
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
	this->distance_max_min_ = new int[this->matrix_row_];
	if (this->parent_max_min_== nullptr || this->distance_max_min_ == nullptr)
	{
		cout << "Memory Error" << endl;
		return false;
	}
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->distance_max_min_[i] = 0;
		this->parent_max_min_[i] = 0;
	}
	size_t first = 0;
	size_t second = 0;
	
	if (!this->SetAndCheckVertex(first, second))
	{
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
	/*for (size_t k = 0; k < counts - 1; k++)
	{
		cout << max_value_lot[k] + 1 << ' ';
	}*/
	PrintArray(max_value_lot);
	cout << "} " << endl;
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		this->distance_max_min_[i] = this->graph_matrix_[first - 1][i];
		if (max < this->distance_max_min_[i])
		{
			max = this->distance_max_min_[i];
			maxIdx = i;
		}
	}
	cout << "D: ";
	/*for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << this->distance_max_min_[i] << ' ';
	}*/
	PrintArray(this->distance_max_min_);
	cout << endl;
	cout << "P: ";
	/*for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << this->parent_max_min_[i] + 1 << ' ';
	}*/
	PrintArray((int*)this->parent_max_min_);
	cout << endl << endl;
	visited[maxIdx] = false;
	max_value_lot[1] = maxIdx;
	max = -myconst::infinity;
	maxIdx = 0;
	for (size_t i = 0; i < this->matrix_row_ - 2; i++)
	{
		cout << "S { ";
		/*for (size_t k = 0; k < counts; k++)
		{
			cout << max_value_lot[k] + 1 << ' ';
		}*/
		this->PrintArray(max_value_lot);
		cout << "} " << endl;
		for (size_t k = 0; k < this->matrix_row_; k++)
		{
			if (visited[k] && this->graph_matrix_[max_value_lot[counts - 1]][k] != myconst::infinity)
			{
				if (this->graph_matrix_[max_value_lot[counts - 1]][k] > this->distance_max_min_[k])
				{
					if (this->graph_matrix_[max_value_lot[counts - 1]][k] < this->distance_max_min_[max_value_lot[counts - 1]])
					{
						this->distance_max_min_[k] = this->graph_matrix_[max_value_lot[counts - 1]][k];
					}
					else
					{
						this->distance_max_min_[k] = this->distance_max_min_[max_value_lot[counts - 1]];
					}
					this->parent_max_min_[k] = max_value_lot[counts - 1];
				}
			}
			if (this->distance_max_min_[k] > max && visited[k])
			{
				max = this->distance_max_min_[k];
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
	if (-(this->distance_max_min_[second - 1]) == myconst::infinity)
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
	cout << "Total weight: " << this->distance_max_min_[second - 1] << endl;
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

void Network::InitAllAndFindSourceDest(size_t& source, size_t& dest)
{
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
}

bool Network::CheckSourceDest(const size_t source, const size_t dest)
{
	if (source == this->matrix_row_ || dest == this->matrix_row_)
	{
		cout << "Source or Destination was not founded" << endl;
		return false;
	}
	return true;
}

bool Network::FindMaxFlow()
{

	size_t dest = this->matrix_row_;
	size_t source = this->matrix_row_;
	this->InitAllAndFindSourceDest(source, dest);


	if (!CheckSourceDest(source, dest))
	{
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


bool Network::SetAndCheckVertex(size_t &first, size_t &second)
{
	cout << "Enter the vertex the path you want to find from: " << endl;
	cin >> first;
	cout << "Enter the vertex the path to which you want to find: " << endl;
	cin >> second;
	if (first > this->matrix_row_ || second > this->matrix_row_)
	{
		cout << "erorr" << endl;
		return false;
	}
	--first;
	return true;
}


bool Network::PrintPathAndWeight(const size_t first, const size_t second)
{
	size_t i = second - 1;
	if (this->top_array[first][second - 1] == myconst::infinity)
	{
		cout << "No path was found" << endl;
		return false;
	}
	bool* check_top = new bool[this->matrix_row_];
	if (check_top == nullptr)
	{
		cout << "Memory Error" << endl;
		return false;
	}
	for (size_t j = 0; j < this->matrix_row_; j++)
	{
		check_top[j] = false;
	}
	while (i != first && !check_top[i])
	{
		cout << i + 1 << "<-";
		check_top[i] = true;
		i = this->parent_ford_belman_[i];
	}
	delete[] check_top;
	if (i != first)
	{
		cout << endl << "Error graph" << endl;
		return false;
	}
	cout << i + 1 << endl;
	cout << "Total weight: " << this->top_array[first][second - 1] << endl;
	return true;
}

void Network::PrintArray(const int* array_)
{
	for (size_t i = 0; i < this->matrix_row_; i++)
	{
		cout << array_[i]+1 << ' ';
	}
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
	if (!this->SetAndCheckVertex(first, second))
	{
		return false;
	}
	bool check = true;
	this->top_array[first].Init(this->matrix_row_, first);

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
	PrintArray(this->parent_ford_belman_);
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

	
	this->PrintPathAndWeight(first, second);
	return true;
}


void Network::Show—apabilities()
{
	cout << "\nYou can do with this graph: " << endl;
	cout << "1. Find min distance from one top to other by Ford-Belman algorithm" << endl;
	cout << "2. Find maximum throughput from one top to other by max-min algorithm" << endl;
	cout << "3. Find maximum flow by Ford-Falkerson alghoritm" << endl;
	cout << "4. Write result to console" << endl;
	cout << "5. Exit to main menu" << endl;
}


bool Network::DoActions(const char idx)
{
	switch (idx)
	{
	case FORD_BELMAN_ALGHORITM:
	{
		if (!this->find_ford_belman)
		{
			this->find_ford_belman = this->FordBelman();
			if (!this->find_ford_belman)
			{
				this->CleanResult();
			}
			return this->find_ford_belman;
		}
		return true;
	}
	case FIND_MAX_MIN_PATH:
	{
		if (!this->find_max_min_path_)
		{
			this->find_max_min_path_ = this->FindMaxMinPath();
			if (!this->find_max_min_path_)
			{
				this->CleanResult();
			}
			return this->find_max_min_path_;
		}
		return true;
	}
	case FIND_MAX_FLOW:
	{
		if (!this->find_max_flow_)
		{
			this->find_max_flow_ =  this->FindMaxFlow();
			if (!this->find_max_flow_)
			{
				this->CleanResult();
			}
			return this->find_max_flow_;
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
		size_t first = this->matrix_row_;
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
		if (first == this->matrix_row_)
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
			cout << this->distance_max_min_[i] << ' ';
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


void Network::CleanResult()
{
	if (this->parent_ford_belman_)
	{
		delete this->parent_ford_belman_;
		this->parent_ford_belman_ = nullptr;
	}
	if (this->distance_max_min_)
	{
		delete this->distance_max_min_;
		this->distance_max_min_ = nullptr;
	}
	if (this->parent_max_min_)
	{
		delete this->parent_max_min_;
		this->parent_max_min_ = nullptr;
	}
	if (this->band_width_)
	{
		for (size_t i = 0; i < this->matrix_row_; i++)
		{
			delete[] this->band_width_[i];
		}
		delete[] this->band_width_;
		this->band_width_ = nullptr;
	}
	this->max = 0;
	this->find_ford_belman = false;
	this->find_max_flow_ = false;
	this->find_max_min_path_ = false;
	this->top_array.clear();

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
