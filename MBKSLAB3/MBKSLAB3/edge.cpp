#include "edge.h"


Edge::Edge()
{
	this->first_top_ = 0;
	this->second_top_ = 0;
	this->weight_ = 0;
}


void Edge::SetFirstTop(const size_t top)
{
	this->first_top_ = top;
}

size_t Edge::GetFirstTop() const
{
	return this->first_top_;
}

void Edge::SetSecTop(const size_t top)
{
	this->second_top_ = top;
}

size_t Edge::GetSecTop() const
{
	return this->second_top_;
}

void Edge::SetWeight(const int weight)
{
	this->weight_ = weight;
}


int Edge::GetWeight() const
{
	return this->weight_;
}


Edge::~Edge()
{
	this->first_top_ = 0;
	this->second_top_ = 0;
	this->weight_ = 0;
}