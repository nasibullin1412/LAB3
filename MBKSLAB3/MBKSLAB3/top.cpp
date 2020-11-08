#include "top.h"

Top::Top()
{
	this->distance_to_oth_ = nullptr;
	this->numb_top_ = 0;
	this->size_ = 0;
}

bool Top::Init(const size_t size, const size_t number_top)
{
	this->numb_top_ = number_top;
	this->size_ = size;
	this->distance_to_oth_ = new int[this->size_ + 1];
	if (this->distance_to_oth_)
	{
		for (size_t i = 0; i < size; i++)
		{
			this->distance_to_oth_[i] = 0;
		}
		return true;
	}

	this->size_ = 0;
	this->distance_to_oth_ = nullptr;
	return false;
}

int& Top::operator[](const size_t count)
{
	if (count > this->size_ || count < 0)
	{
		return this->distance_to_oth_[size_];
	}
	return this->distance_to_oth_[count];
}


int Top::GetTopNumb()
{
	return this->numb_top_;
}

Top::~Top()
{
	if (this->distance_to_oth_)
	{
		delete this->distance_to_oth_;
		this->distance_to_oth_ = nullptr;
	}
	this->numb_top_ = 0;
	this->size_ = 0;
}