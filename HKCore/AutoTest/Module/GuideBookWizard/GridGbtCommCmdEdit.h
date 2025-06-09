//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "GbtCommCmdEdit.h"

#define WM_COMMCMDEDIT_DATA_CHANGED  (WM_USER+6753)


#define GBTCMDEDIT_COL_INDEX        0
#define GBTCMDEDIT_COL_NAME         1
#define GBTCMDEDIT_COL_ID           2
#define GBTCMDEDIT_COL_DATASET      3


#define GBTCMDEDIT_COLS             4


class CGridGbtCommCmdEdit : public CExBaseListGrid
{
public:
	CGridGbtCommCmdEdit();
	virtual ~CGridGbtCommCmdEdit();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual long GetDatasCount();

//重载函数
public: 
	
//私有成员变量
private:
	CExBaseList m_listDatasets;
	long GetCmdEditCount();

	CString GetMmsDsKey(CStringArray &astrMmsDsKey);

//私有成员变量访问方法
public:
	//填充comboList cell
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	static void EndEditCell_CmbDataset(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_CmbExpandDataset(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

