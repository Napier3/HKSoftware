#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\MacroMap.h"

class CPtAtsValueMapGrid : public CExBaseListGrid
{
public:
	CPtAtsValueMapGrid();
	virtual ~CPtAtsValueMapGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

protected:

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
};


