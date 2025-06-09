#pragma once


#include "..\..\Module\GridBase\ExBaseListGrid.h"

class CTestAppEditGrid :	public CExBaseListGrid
{
public:
	CTestAppEditGrid(void);
	~CTestAppEditGrid(void);

	virtual void InitGridTitle();
	virtual void InitGrid();

	CDvmDataset *m_pTestAppDefine;
	CDvmDataset *m_pTestApp;

private:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};
