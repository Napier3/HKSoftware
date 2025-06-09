#pragma once
#include "../WzdDlgStyleGrid.h"
#include "../../../../../Module/API/MathApi.h"
#include "../../../../../Module/GridBase/ExBaseListGrid.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../../../61850/Module/GlobalDataMngr/IecGlobalDataMngr.h"

#define IECCFG_COL_ID_INDEX   0

class CIECCfgGridBase :	public CWzdDlgStyleGrid
{
public:
	CIECCfgGridBase();
	virtual ~CIECCfgGridBase(void);

	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	void SetGridCellFgClr(int nRow,int nCol,COLORREF crFgColor);//zhouhj 20220215 设置表格中某一格的前景色为灰色
	void SetRowFgClr(int nRow,int nBeginCol ,int nEndCol,COLORREF crFgColor);
};

