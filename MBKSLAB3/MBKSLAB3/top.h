#ifndef _TOP_H_
#define _TOP_H_
#pragma once
#include <vector>
class Top
{
public:
	Top();
	~Top();
	bool Init(const size_t size, const size_t number_top);
	int& operator[](const size_t count);
	int GetTopNumb();

private:
	int* distance_to_oth_;
	size_t size_;
	size_t numb_top_;
};





#endif