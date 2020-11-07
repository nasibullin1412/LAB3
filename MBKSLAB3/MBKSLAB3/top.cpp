#include "top.h"

Top::Top()
{
	this->distanation_to_oth_ = nullptr;
	this->numb_top_ = 0;
	this->size_ = 0;
}

void Top::Init(const size_t size, const size_t number_top)
{
	this->numb_top_ = number_top;
	this->size_ = size;
	this->distanation_to_oth_ = new int[this->size_+1];
	if (this->distanation_to_oth_)
	{
		for (size_t i = 0; i < size; i++)
		{
			this->distanation_to_oth_[i] = 0;
		}
	}
	else
	{
		this->size_ = 0;
		this->distanation_to_oth_ = nullptr;
	}
}

int& Top::operator[](const size_t count)
{
	if (count > this->size_ || count < 0)
	{
		return this->distanation_to_oth_[size_];
	}
	return this->distanation_to_oth_[count];
}


int Top::GetTopNumb()
{
	return this->numb_top_;
}

Top::~Top()
{
	if (this->distanation_to_oth_)
	{
		delete this->distanation_to_oth_;
		this->distanation_to_oth_ = nullptr;
	}
	this->numb_top_ = 0;
	this->size_ = 0;
}