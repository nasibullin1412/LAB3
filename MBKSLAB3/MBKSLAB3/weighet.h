#ifndef _WEIGHET_H_
#define _WEIGHET_H_
#pragma once
#include "edge.h"
#include "graph.h"

using namespace std;

class WeightGraph: public Graph
{
public:
	WeightGraph();
	~WeightGraph();
	bool MinSkeletonKraskal();


	void virtual PrintResultToConsole();
	virtual void Show�apabilities() ;
	virtual bool DoActions(char idx);
	void virtual ClearResult();

private:
	Edge *edge_list_;
	size_t** adj_matrix_skeleton_;
	size_t numb_edge_;
	int tot_min_weight_;
	bool is_find_skeleton_;
	void PushTask(const Edge& new_elem, const size_t size);
	Edge& PopTask(const size_t &size);
};


#endif