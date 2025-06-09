//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\GridBase\ExBaseListGrid.h"
#include "TestMacrosFileMngr.h"


#define TESTMCACROFILE_COL_INDEX           0
#define TESTMCACROFILE_COL_NAME            1
#define TESTMCACROFILE_COL_APPID           2
#define TESTMCACROFILE_COL_MACROFILE       3
#define TESTMCACROFILE_COL_CMMFILE         4

#define TESTMCACROFILE_COLS                5


class CGridTestMacrosFile : public CExBaseListGrid
{
public:
	CGridTestMacrosFile();
	virtual ~CGridTestMacrosFile();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);

//重载函数
public: 
	
//私有成员变量
private:
	//static void EndEditCell_AppProgID(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	
//私有成员变量访问方法
public:

};

