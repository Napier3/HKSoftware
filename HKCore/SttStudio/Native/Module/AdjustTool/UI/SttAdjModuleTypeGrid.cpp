//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjModuleTypeGrid.h"
#include "..\SttAdjBase.h"

CSttAdjModuleTypeGrid::CSttAdjModuleTypeGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	//m_strChildDataTypeID = STT_ADJ_DATA_TYPE_SttModuleType;
}

CSttAdjModuleTypeGrid::~CSttAdjModuleTypeGrid()
{

}

void CSttAdjModuleTypeGrid::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModuleTypeGrid::InitGridTitle()
{
	CString astrTitle[4] = {_T("���"),_T("����"),_T("ģ��ID"),_T("VALUE")};
	int nWidth[4]={40,120,100,100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 4);
}

void CSttAdjModuleTypeGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATATYPEVALUE)
	{
		return;
	}

	CDataTypeValue *pDataTypeValue = (CDataTypeValue*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, &pDataTypeValue->m_strName);
	Show_StaticString(pData, nRow, 2, &pDataTypeValue->m_strID);
	Show_StaticString(pData, nRow, 3, &pDataTypeValue->m_strIndex);

	nRow++;
}
