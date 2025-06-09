//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjHdGearsGrid.h"
#include "..\SttAdjBase.h"

CSttAdjHdGearsGrid::CSttAdjHdGearsGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_HdGear;
}

CSttAdjHdGearsGrid::~CSttAdjHdGearsGrid()
{

}


void CSttAdjHdGearsGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjHdGearsGrid::InitGridTitle()
{
	CString astrTitle[4] = {_T("编号"),_T("名称"),_T("档位ID"),_T("档位数值")};
	CString astrAttrs[4] = {_T(""),_T("Name"), _T("GearID"), _T("GearValue")};
	int nWidth[4]={40,120,100,100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 4);
	InitGridColAttrs(astrAttrs, 4);
}

void CSttAdjHdGearsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	CDataGroup *pHdGear = (CDataGroup*)pData;

	for (long nCol=1; nCol<m_nCols; nCol++)
	{
		ShowAttrCol(pHdGear, nRow, nCol);
	}

	nRow++;
}
