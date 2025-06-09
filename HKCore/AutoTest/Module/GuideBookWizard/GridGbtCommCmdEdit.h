//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public: 
	
//˽�г�Ա����
private:
	CExBaseList m_listDatasets;
	long GetCmdEditCount();

	CString GetMmsDsKey(CStringArray &astrMmsDsKey);

//˽�г�Ա�������ʷ���
public:
	//���comboList cell
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	static void EndEditCell_CmbDataset(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_CmbExpandDataset(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

