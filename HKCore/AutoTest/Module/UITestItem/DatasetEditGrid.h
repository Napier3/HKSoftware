#pragma once
#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\GuideBook\DataSet.h"

#define DATASET_COL_ID_INDEX         0
#define DATASET_COL_ID_NAME          1
#define DATASET_COL_ID_ID	           2
#define DATASET_COL_ID_VALUE	       3
#define DATASET_COL_ID_UNIT          4

#define DATASET_COLS                 5

class CDatasetEditGrid : public CExBaseListGrid
{
public:
	CDatasetEditGrid();
	virtual ~CDatasetEditGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

