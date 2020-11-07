#ifndef _RESULT_H_
#define _RESILT_H_
#pragma once

class IResult
{
public:
	virtual void Show—apabilities() = 0;
	virtual bool DoActions(char idx) = 0;
	virtual void PrintResultToConsole() = 0;;
	virtual void ClearResult() = 0;

};



#endif