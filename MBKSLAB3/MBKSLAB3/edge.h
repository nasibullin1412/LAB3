#ifndef _EDGE_H_
#define _EDGE_H_
#pragma once

class Edge
{
public:
	Edge();
	void SetFirstTop(const size_t top);
	size_t GetFirstTop() const;
	void SetSecTop(const size_t top);
	size_t GetSecTop() const;
	void SetWeight(const int weight);
	int GetWeight() const;
	~Edge();

private:
	int weight_;
	size_t first_top_;
	size_t second_top_;
};

#endif