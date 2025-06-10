//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjModuleOutputGrid.h"
#include "..\SttAdjBase.h"

CSttAdjModuleOutputGrid::CSttAdjModuleOutputGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_Channel;
}

CSttAdjModuleOutputGrid::~CSttAdjModuleOutputGrid()
{

}


void CSttAdjModuleOutputGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModuleOutputGrid::InitGridTitle()
{
	CString astrTitle[4] = {_T("编号"),_T("通道"),_T("幅值"),_T("相位")};
	CString astrAttrs[4] = {_T(""),_T("name"),  _T("Mag"), _T("Ang")};
	int nWidth[4]={40,100,100,100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 4);
	InitGridColAttrs(astrAttrs, 4);
}

void CSttAdjModuleOutputGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	
	CDataGroup *pVector = (CDataGroup*)pData;

	for (long nCol=2; nCol<m_nCols; nCol++)
	{
		ShowAttrCol(pVector, nRow, nCol);
	}

	nRow++;
}
