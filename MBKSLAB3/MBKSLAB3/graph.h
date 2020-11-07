#ifndef _GRAPH_H_
#define _GRAPH_H_
#pragma once
#include "top.h"
#include "result.h"


namespace myconst
{
	constexpr unsigned int max_file_name = 100;
	constexpr unsigned int max_file_content = 10000;
	constexpr unsigned int max_word_size = 20;
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
	Top* top_array;
	int** graph_matrix_;
	size_t matrix_row_;
	size_t numb_edge_;
};
#endif
