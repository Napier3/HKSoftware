//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public: 
	
//˽�г�Ա����
private:
	//static void EndEditCell_AppProgID(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	
//˽�г�Ա�������ʷ���
public:

};

