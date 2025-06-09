//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\GridBase\ExBaseListGrid.h"
#include "..\DvmDataset.h"

enum GridType
{
	UNKNOWN_TABLE = 0,                  //δ֪����
	CLIENT_TABLE,                        //�ͻ���
	SOFTDOG_TABLE,                       //�������
	CLIENT_NEW_TEMPLATE_TABLE,           //�ͻ�ģ���
	CLIENT_OLD_TEMPLATE_TABLE,           //�ͻ���ʷģ���
	DEVELOP_TASK_TABLE,                  //���������
	OLD_DEVELOP_TASK_TABLE,              //��ʷ���������
	DEVELOPER_TEMPLATE_STATISTICS_TABLE, //������Աģ�忪��ͳ�Ʊ�
	DEVELOPER_CLIENT_STATISTICS_TABLE,   //�ͻ���λģ�忪��ͳ�Ʊ�
	MAX_TABLE_TYPE,
};

class CDvmDatasetGrid : public CExBaseListGrid
{
public:
	CDvmDatasetGrid();
	virtual ~CDvmDatasetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType)	;

	void UpdateIedTestState();
	void SetTableType(GridType nTableType);


//���غ���
public: 
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

//˽�г�Ա����
private:
	CDataType m_oDataType;

	GridType m_nTableType;
	int m_nTableColNum;
//˽�г�Ա�������ʷ���
public:
};

