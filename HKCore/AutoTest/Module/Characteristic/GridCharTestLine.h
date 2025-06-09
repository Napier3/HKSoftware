//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARTESTLINE_COL_INDEX        0
#define CHARTESTLINE_COL_TYPE         1
#define CHARTESTLINE_COL_POS          2
#define CHARTESTLINE_COL_ROTATEANGLE  3
#define CHARTESTLINE_COL_ANGLEDEF     4

#define CHARTESTLINE_COLS             5


class CGridCharTestLine : public CExBaseListGrid
{
public:
	CGridCharTestLine();
	virtual ~CGridCharTestLine();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//重载函数
public: 
	
//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

};

