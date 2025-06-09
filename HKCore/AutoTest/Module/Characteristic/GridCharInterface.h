//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARINTERFACE_COL_INDEX      0
#define CHARINTERFACE_COL_ID         1
#define CHARINTERFACE_COL_VALUE      2
#define CHARINTERFACE_COL_SCRIPT     3

#define CHARINTERFACE_COLS           3
#define CHARINTERFACEMAP_COLS        4


class CGridCharInterface : public CExBaseListGrid
{
public:
	CGridCharInterface();
	virtual ~CGridCharInterface();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	
//私有成员变量
private:

//私有成员变量访问方法
public:
	static void EndEditCell_Value (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};


class CGridCharInterfaceMap : public CGridCharInterface
{
public:
	CGridCharInterfaceMap();
	virtual ~CGridCharInterfaceMap();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	
//私有成员变量
private:
	BOOL m_bIsDvmMapEditGrid;

//私有成员变量访问方法
public:
	static void EndEditCell_Script (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

