#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\..\..\Module\DataMngr\DvmDataset.h"

class CGridExtendRptTempalte : public CExBaseListGrid
{
public:
	CGridExtendRptTempalte();
	virtual ~CGridExtendRptTempalte();

public:
	virtual void InitGridTitle();
	virtual void InitGrid();

private:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

};
