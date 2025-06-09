//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public: 
	
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
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

//���غ���
public: 
	
//˽�г�Ա����
private:
	BOOL m_bIsDvmMapEditGrid;

//˽�г�Ա�������ʷ���
public:
	static void EndEditCell_Script (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

