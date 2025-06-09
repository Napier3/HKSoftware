//XRecordChDataInterface.h  CXRecordChDataInterface

#pragma once

#include "../BaseClass/ExBaseList.h"

class CRecordChDataInterface  : public CExBaseObject
{
public:
	virtual void AddRcdData(WORD wValue) = 0;
	virtual void AddRcdData(long wValue) = 0;
	virtual void AddRcdData(float fValue) = 0;
	virtual void AddRcdData(double dValue) = 0;
	virtual void AddRcdData(WORD wValue, long nPos) = 0;
	virtual void AddRcdData(long wValue, long nPos) = 0;
	virtual void AddRcdData(float fValue, long nPos) = 0;
	virtual void AddRcdData(double dValue, long nPos) = 0;
	virtual void SetPosition(long nPos, long nDataCount) = 0;
};

