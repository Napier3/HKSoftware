//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\GridBase\ExBaseListGrid.h"
#include "..\DataGroup.h"
#include "DataGroupListView.h"

#define DATAMNGRFOLDER_COL_INDEX      0
#define DATAMNGRFOLDER_COL_NAME       1
#define DATAMNGRFOLDER_COL_SEL        2//�豸�ͺ�
#define DATAMNGRFOLDER_COL_VALUE      3//IED����

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

//���غ���
public: 
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

