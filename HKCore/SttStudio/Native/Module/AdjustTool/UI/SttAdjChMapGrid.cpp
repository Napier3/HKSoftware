//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjChMapGrid.h"
#include "..\SttAdjBase.h"
#include "..\SttMesLocalDb.h"

CSttAdjHdChDefGrid::CSttAdjHdChDefGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_HdCh;
}

CSttAdjHdChDefGrid::~CSttAdjHdChDefGrid()
{

}


void CSttAdjHdChDefGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(10);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjHdChDefGrid::InitGridTitle()
{
	CString astrTitle[10] = {_T("���"),_T("����"),_T("ͨ��ID"),_T("ͨ�����"),_T("����ģʽ"),_T("��������"),_T("ͨ��ӳ��"),_T("�������ֵ"),_T("ֱ�����ֵ"), _T("ͨ���ɼ�ӳ��λ��")};
	CString astrAttrs[10] = {_T(""),_T("Name"), _T("ID"), _T("Index"), _T("WorkMode"), _T("EeType"), _T("ChRsIndex"), _T("ChACMaxValue"), _T("ChDCMaxValue"), _T("ChMeasPos")};
	int nWidth[10]={40,110,90,90, 90, 90, 90, 90, 90, 120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 10);
	InitGridColAttrs(astrAttrs, 10);
}

void CSttAdjHdChDefGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pChMap = (CDataGroup*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	//Show_StaticString(pData, nRow, 2, pData->m_strID);

	for (long nCol=2; nCol<m_nCols; nCol++)
	{
		ShowAttrCol(pChMap, nRow, nCol);
	}

	nRow++;
}

CDataType* CSttAdjHdChDefGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}