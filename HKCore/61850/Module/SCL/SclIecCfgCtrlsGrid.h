#pragma once
#include "../../../Module/GridBase/ExBaseListGrid.h"

class CSclIecCfgCtrlsGrid :public CExBaseListGrid
{
public:
	CSclIecCfgCtrlsGrid(void);
	virtual ~CSclIecCfgCtrlsGrid(void);

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual CDataType* FindDataType(const CString &strDataType);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
//	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType);
};
