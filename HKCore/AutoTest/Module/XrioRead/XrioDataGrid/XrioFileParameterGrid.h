#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"

class CXrioFileParameterGrid : public CExBaseListGrid
{
public:
	CXrioFileParameterGrid();
	virtual ~CXrioFileParameterGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	//���غ���
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};


