#pragma once

#include "..\DvmDevice.h"
#include "..\..\GridBase\ExBaseListGrid.h"
#include "DsvScript.h"

class CDsvViewDatasetGrid : public CExBaseListGrid
{
public:
	CDsvViewDatasetGrid();
	virtual ~CDsvViewDatasetGrid();

	virtual void InitGrid();

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	void ViewDsvElement(CDsvElement *pDsvElement);

};

