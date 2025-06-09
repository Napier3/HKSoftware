//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\GridBase\ExBaseListGrid.h"
#include "..\DataGroup.h"
#include "DataGroupListView.h"

#define DATAMNGRFOLDER_COL_INDEX      0
#define DATAMNGRFOLDER_COL_NAME       1
#define DATAMNGRFOLDER_COL_SEL        2//设备型号
#define DATAMNGRFOLDER_COL_VALUE      3//IED描述

#define DATAMNGRFOLDER_COLS           4


class CDataGroupGrid : public CExBaseListGrid
{
public:
	CDataGroupGrid();
	virtual ~CDataGroupGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType)	;

	void UpdateIedTestState();

	CDataGroupListView *m_pDataGroupListViewRef;
	CDataTypes *m_pDataTypesRef;

//重载函数
public: 
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

