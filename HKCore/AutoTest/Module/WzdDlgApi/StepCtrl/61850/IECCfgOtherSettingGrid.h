#pragma once
#include "IECCfgDataGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
class CIECCfgOtherSettingGrid : public CIECCfgDataChsGridBase
{
public:
	CIECCfgOtherSettingGrid();
	virtual ~CIECCfgOtherSettingGrid();

private:
	CExBaseList* m_pLastDatas;

	void ShowSMVData(CIecCfg92Data* pIecCfg92Data, long& nRow);
	void ShowGOOSEINData(CIecCfgGooseDataBase* pIecCfgGsData, long& nRow);
	void ShowGOOSEOUTData(CIecCfgGooseDataBase* pIecCfgGsData, long& nRow);
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseList *pData);
	virtual void UpdateData();

	virtual CString GetGridClassID() { return "CIECCfgOtherSettingGrid"; }

	void AddNewLine_StaticString(CExBaseList *pData, long& nRow, 
		CString strName, CString strValue);
	void AddNewLine_Fiber(CExBaseList *pData, long& nRow, 
		CString strName, long* pnFiber, GRID_CELL_EDIT_FUNC pFunc);
	void AddNewLine_Syn(CExBaseList *pData, long&nRow,
		CString strName, long* pnSyn, GRID_CELL_EDIT_FUNC pFunc);
	void AddNewLine_Test(CExBaseList *pData, long& nRow, 
		CString strName, long* pnFiber, GRID_CELL_EDIT_FUNC pFunc);
	void AddNewLine_Long(CExBaseList *pData, long& nRow, 
		CString strName, long* pnNum);
	void AddNewLine_Check(CExBaseList *pData, long& nRow, 
		CString strName, long* pnCheck);
	//static void EndEditCell_Check(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	//static void EndEditCell_Value(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Fiber(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
};

