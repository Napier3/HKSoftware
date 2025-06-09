#pragma once
#include "IecCfgGridBase.h"

#include "..\CfgDataMngr\IecCfgDataBase.h"
#include "IecCfgDataChsGridBase.h"

#define IECCFG_COL_ID_DATA_CHECK   1



class CIecCfgDataGridBase : public CIecCfgGridBase
{
public:
	CIecCfgDataGridBase();
	virtual ~CIecCfgDataGridBase();
	
	void AttachRefChsGrid(CIecCfgDataChsGridBase *pRefChsGrid)		{	m_pRefChsGrid = pRefChsGrid;	}
	void Update_RefChsGrid(long nSelected);//
	virtual CString GetAppPortDataType()	{	return g_strAppPortDataType_Fiber;	}
	virtual CString GetSynModeDataType()	{	return g_strSynModeDataType_Fiber;	}
	CString GetSynModeDataTypeValue(long nSyn);//zhouhj 20220211 直接获取数据值

protected:
	CIecCfgDataChsGridBase *m_pRefChsGrid;

	virtual BOOL ValidateIecCfgDatFiberIndex(CIecCfgDataBase *pIecCfgData);

public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void  Show_ChNum(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnChannelNum, BOOL bSetColor=TRUE);
	static void EndEditCell_ChNum (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	static void EndEditCell_IecCfgDataCheck (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_Fiber2(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);
	static void EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Fiber2 (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual void  Show_Syn(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSyn, GRID_CELL_EDIT_FUNC pFunc=NULL);
	static void EndEditCell_Syn (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Priority(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20211030  用于优先级限制
	static void EndEditCell_Delay(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20211118  用于限制采样延时输入值
	static void EndEditCell_VlanID(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20211112  用于现在VID
	virtual void  Show_VlanID(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue,BOOL bCanEdit = TRUE, BOOL bSetColor=TRUE);

public:
	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);
};

