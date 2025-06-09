//SttXDeviceMngrGrid.h  CSttXDeviceMngrGrid

#pragma once

#include "../../../Module/DataMngr/UI/XDataGroupGridBase.h"

class CSttXDeviceMngrGrid : public CXDvmGrid_DataRow
{
public:
	CSttXDeviceMngrGrid();
	virtual ~CSttXDeviceMngrGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

