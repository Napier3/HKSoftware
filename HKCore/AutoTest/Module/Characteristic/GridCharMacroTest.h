//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CharacteristicTmplate.h"


#define CHARMACROTEST_COL_INDEX        0
#define CHARMACROTEST_COL_TYPE         1
#define CHARMACROTEST_COL_AXISMODE     2
#define CHARMACROTEST_COL_TESTMACROID  3
#define CHARMACROTEST_COL_BXID         4
#define CHARMACROTEST_COL_BYID         5
#define CHARMACROTEST_COL_SETXID       5
#define CHARMACROTEST_COL_SETYID       6
#define CHARMACROTEST_COL_EXID         7
#define CHARMACROTEST_COL_EYID         8
#define CHARMACROTEST_COL_ACTXID       10
#define CHARMACROTEST_COL_ACTYID       11

#define CHARMACROTEST_COLS             12


class CGridCharMacroTest : public CExBaseListGrid
{
public:
	CGridCharMacroTest();
	virtual ~CGridCharMacroTest();

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

