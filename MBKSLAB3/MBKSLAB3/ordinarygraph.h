#ifndef _ORDINARYGRAPH_H_
#define _ORDINARYGRAPH_H_
#pragma once

#include "graph.h"


class OrdinaryGraph : public Graph
{
public:
	OrdinaryGraph();
	~OrdinaryGraph();
	bool FindSkeleton();
	bool CountDeg();
	virtual void Show—apabilities();
	virtual bool DoActions(const char idx);
	virtual void PrintResultToConsole();
	virtual void CleanResult();

private:
	unsigned short** graph_skeleton_;
	unsigned short* tops_deg_;
	bool is_find_skeleton_;
	bool is_count_edge_;
	void Dfs(const size_t numb_top, bool *visited);
};



#endif