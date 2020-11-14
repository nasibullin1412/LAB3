#ifndef _GRAPH_H_
#define _GRAPH_H_
#pragma once
#include "top.h"
#include "result.h"
#include <vector>

namespace myconst
{
	constexpr unsigned int max_file_name = 100;
	constexpr unsigned int max_file_content = 10000;
	constexpr int infinity = 100000;
}

class Graph: public IResult
{
public:

	Graph();
	~Graph();
	bool ReadGraph();
	bool IsReaded();

protected: 
	std::vector<Top> top_array;
	std::vector<std::vector<int> > graph_matrix_;
	size_t matrix_row_;
	size_t numb_edge_;
};
#endif
