//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public: 
	
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

};

