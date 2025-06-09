//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "TestTasksMngr.h"

#define XTEST_FUNCTEST_STATE_NONE		0		//测试未开始
#define XTEST_FUNCTEST_STATE_GOING		1		//测试进行中
#define XTEST_FUNCTEST_STATE_FINISH		2		//测试完成
#define XTEST_FUNCTEST_STATE_STOP		3		//测试中途停止
#define XTEST_FUNCTEST_STATE_ERROR		4		//测试具有不合格项
#define XTEST_FUNCTEST_STATE_ARCHIVED	5		//报告已生成

#define XTestDb_SEL_GRID_SEL_ALL                    0X089304
#define XTestDb_SEL_GRID_CANCEL_ALL                 0X089305
#define XTestDb_SEL_GRID_INVERSE_ALL                0X089306


//////////////////////////////////////////////////////////////////////////
//CXTestDbGrid
class CXTestDbGrid :	public CExBaseListGrid
{
public:
	CXTestDbGrid(void);
	virtual ~CXTestDbGrid(void);

	CTestTasksMngr *m_pTestTasksMngr;
	CDvmDataset *m_pFirstDvmAttr;
	long m_nDeviceAttrEndCol;
	CExBaseList m_listAllDatas;

	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);

	virtual void InitGridTitle();
	virtual BOOL UpdateData(CExBaseObject *pData);

	void UpdateDatasEx(BOOL bClearSelect);
	void ClearAllDatasCheck();
	void UpdateAllCheck();
	void SetSingleSel(BOOL bSingleSel){m_bSingleSel = bSingleSel;}

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE)	{}
	
	void ShowDataState(CExBaseObject *pData, int& nRow, const CString &strState, BOOL bInsertRow=TRUE);
	void ShowDatas_List(CExBaseList &listDatas, int &nRowIndex, const CString &strState);

	static void EndEditCell_XTestCheck (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

private:
	BOOL m_bSingleSel;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnSelectAll_MenuOpr();
	afx_msg void OnCancelAll_MenuOpr();
	afx_msg void OnInverseAll_MenuOpr();
};
