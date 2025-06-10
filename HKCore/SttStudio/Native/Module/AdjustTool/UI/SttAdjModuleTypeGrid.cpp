//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjModuleTypeGrid.h"
#include "..\SttAdjBase.h"

CSttAdjModuleTypeGrid::CSttAdjModuleTypeGrid()
{
	//初始化属性

	//初始化成员变量
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
	CString astrTitle[4] = {_T("编号"),_T("名称"),_T("模块ID"),_T("VALUE")};
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
