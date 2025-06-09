//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjTRangeGrid.h"
#include "..\SttAdjBase.h"

CSttAdjTRangeGrid::CSttAdjTRangeGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_TRange;
}

CSttAdjTRangeGrid::~CSttAdjTRangeGrid()
{

}


void CSttAdjTRangeGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjTRangeGrid::InitGridTitle()
{
	CString astrTitle[3] = {_T("编号"),_T("温区"),_T("温度")};
	CString astrAttrs[3] = {_T(""),_T("Name"), _T("Temperature")};
	int nWidth[3]={40,80,80};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 3);
	InitGridColAttrs(astrAttrs, 3);
}

void CSttAdjTRangeGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pT_Range = (CDataGroup*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pT_Range->m_strName);

	ShowAttrCol(pT_Range, nRow, 2);

	nRow++;
}
