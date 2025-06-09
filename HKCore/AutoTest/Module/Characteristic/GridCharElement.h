//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARELEMENT_COL_INDEX      0
#define CHARELEMENT_COL_TYPE       1
#define CHARELEMENT_COL_POINTS     2
#define CHARELEMENT_COL_ERROR      3
#define CHARELEMENT_COL_DETAIL     4

#define CHARELEMENT_COLS           5


class CGridCharElementDev : public CExBaseListGrid
{
public:
	CGridCharElementDev();
	virtual ~CGridCharElementDev();

	void SetViewElementDetail(BOOL b=TRUE)	{	m_bViewElementDetail = b;	}
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	
//私有成员变量
private:
	BOOL m_bViewElementDetail;
	static void EndEditCell_ErrorLength (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_TestPoints(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
//私有成员变量访问方法
public:
	//virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

};

