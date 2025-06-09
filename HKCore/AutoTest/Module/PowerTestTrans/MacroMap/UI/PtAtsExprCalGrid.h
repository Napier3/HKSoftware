#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\MacroMap.h"

class CPtAtsExprCalGrid : public CExBaseListGrid
{
public:
	CPtAtsExprCalGrid();
	virtual ~CPtAtsExprCalGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

protected:

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
};


