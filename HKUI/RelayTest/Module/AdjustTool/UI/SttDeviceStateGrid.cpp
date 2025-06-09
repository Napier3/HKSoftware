//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttDeviceStateGrid.h"
#include "..\SttAdjBase.h"

CSttDeviceStateGrid::CSttDeviceStateGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_Channel;
}

CSttDeviceStateGrid::~CSttDeviceStateGrid()
{

}


void CSttDeviceStateGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttDeviceStateGrid::InitGridTitle()
{
	CString astrTitle[5] = {_T("编号"),_T("通道"),_T("最大电压"),_T("最小电压"),_T("是否过载")};
	CString astrAttrs[5] = {_T(""),_T("Name"), _T("VoltMax"),_T("VoltMin"), _T("IsOverLoad")};
	int nWidth[5]={40,120,120,120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 5);
	InitGridColAttrs(astrAttrs, 5);
}

void CSttDeviceStateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pChannel = (CDataGroup*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pChannel->m_strName);

	for (long nCol = 2; nCol <= 4; nCol++)
	{
		ShowAttrCol(pChannel, nRow, nCol);
	}

	nRow++;
}
