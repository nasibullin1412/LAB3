#ifndef _NETWORK_H_
#define _NETWORK_H_
#pragma once
#include "graph.h"


enum NETWORK_DO_ACTIONS
{
	FORD_BELMAN_ALGHORITM = '1',
	FIND_MAX_MIN_PATH,
	FIND_MAX_FLOW
};


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
	std::vector<int>parent_ford_belman_;
	std::vector<int>distance_max_min_;
	std::vector<size_t> parent_max_min_;
	std::vector<std::vector<int> > band_width_;
	int max;
	bool find_max_min_path_;
	bool find_max_flow_;
	bool find_ford_belman;
	int max_flow_;
	int FordFalkerson(int v, int dest, std::vector<bool> &visit, int flow);
	size_t min(const size_t first, const size_t second);
	int FindMax();
	void InitAllAndFindSourceDest(size_t &source, size_t &dest);
	bool CheckSourceDest(const size_t first, const size_t second);
	bool SetAndCheckVertex(size_t& first, size_t& second);
	bool PrintPathAndWeight(const size_t first, const size_t second);
	void PrintArray(const std::vector<int> &array_);
};



#endif