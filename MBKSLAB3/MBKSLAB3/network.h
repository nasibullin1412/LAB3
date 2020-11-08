#ifndef _NETWORK_H_
#define _NETWORK_H_
#pragma once
#include "graph.h"

class Network: public Graph
{
public:
	Network();
	~Network();
	bool FindMaxMinPath();
	bool FindMaxFlow();
	bool FordBelman();
	void virtual Show—apabilities();
	bool virtual DoActions(const char idx);
	void virtual PrintResultToConsole();
	void virtual CleanResult();
private:
	int* parent_ford_belman_;
	int* distance_max_min_;
	size_t* parent_max_min_;
	int** band_width_;
	int max;
	bool find_max_min_path_;
	bool find_max_flow_;
	bool find_ford_belman;
	int max_flow_;
	int FordFalkerson(int v, int dest, bool* visit, int flow);
	size_t min(const size_t first, const size_t second);
	int FindMax();
};



#endif