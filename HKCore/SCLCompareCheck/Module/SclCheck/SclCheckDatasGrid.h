#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"

#define IDC_GRID_SCLCHECK_CTRL   21010


#include "..\..\..\Module\DataMngr\DvmDataset.h"


class CSclCheckCtrlGrid : public CExBaseListGrid
{
public:
	CSclCheckCtrlGrid();
	virtual ~CSclCheckCtrlGrid();

public:
	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	void ShowData_Check(CExBaseList *pGsOut,int nRow);
protected:
	UINT m_nOldSclIecCfgClassID;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
