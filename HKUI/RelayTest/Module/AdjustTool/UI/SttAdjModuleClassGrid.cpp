//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjModuleClassGrid.h"
#include "..\SttAdjBase.h"
#include "..\SttMesLocalDb.h"

CSttAdjModuleClassGrid::CSttAdjModuleClassGrid()
{
	//初始化属性

	//初始化成员变量
	//m_strChildDataTypeID = STT_ADJ_DATA_TYPE_SttModuleClass;
}

CSttAdjModuleClassGrid::~CSttAdjModuleClassGrid()
{

}


void CSttAdjModuleClassGrid::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(11);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModuleClassGrid::InitGridTitle()
{
	CString astrTitle[11] = {_T("编号"), _T("名称"), _T("模块ID"),_T("模块类型"),  _T("模块硬件位置")
		, _T("频率"), _T("通道数"), _T("型号"), _T("Idc通道最大值")
		, _T("Udc通道最大值"), _T("通道最大值")};
	CString astrAttrs[11] = {_T(""),_T("Name"), _T("ID"), _T("ModuleType"), _T("ModulePos"), _T("Freq"), _T("ChannelCount"), _T("Model"), _T("UdcMax"), _T("IdcMax"), _T("ChMax") };
	
	int nWidth[11] = {40,160,100,100,100,60,60,100,100,100,100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 11);
	InitGridColAttrs(astrAttrs, 11);
}

void CSttAdjModuleClassGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pDataGroup  =  (CDataGroup*)pData;
	Show_Index(pData,  nRow,  0);
	Show_String(pData, nRow,  1,  &pData->m_strName, EndEditCell_String_Name);//Show_StaticString(pData, nRow,  1,  pData->m_strName)
	Show_String(pData, nRow,  2,  &pData->m_strID, EndEditCell_String_ID);

	for (long nCol = 3;  nCol  <  m_nCols;   nCol++)
	{
		ShowAttrCol(pDataGroup, nRow, nCol);
	}

	nRow++;

}

CDataType* CSttAdjModuleClassGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}

