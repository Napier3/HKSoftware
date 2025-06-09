#pragma once
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\..\..\Module\API\MathApi.h"

#include "../GuideBook/GuideBookInterface.h"


class CSafetyTestGrid :	public CExBaseListGrid
{
public:
	CSafetyTestGrid();
	virtual ~CSafetyTestGrid(void);

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
// 	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
// 	static void EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

