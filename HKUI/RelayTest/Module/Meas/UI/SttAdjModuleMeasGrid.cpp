//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权?


#include "stdafx.h"
#include "SttAdjModuleMeasGrid.h"
#include "..\SttAdjBase.h"

CSttAdjModuleMeasGrid::CSttAdjModuleMeasGrid()
{
	//初始化属性

	//初始化成员变量
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_Channel;
}

CSttAdjModuleMeasGrid::~CSttAdjModuleMeasGrid()
{

}


void CSttAdjModuleMeasGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(6);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModuleMeasGrid::InitGridTitle()
{
	CString astrTitle[6] = {_T("编号"),_T("通道"),_T("谐波"), _T("幅值"),_T("相位"), _T("频率")};
	CString astrAttrs[6] = {_T("Index"),_T("Channel"),_T("Harm"),_T("Mag"),  _T("Ang"), _T("Freq")};
	int nWidth[6]={40, 100, 100, 100, 100, 100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 6);
	InitGridColAttrs(astrAttrs, 6);
}

void CSttAdjModuleMeasGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	//通道
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	long nRowBegin = nRow; //用于合并通道名称
	CDataGroup *pChannel = (CDataGroup*)pData;
	long nCol = 0;
	POS pos = pChannel->GetHeadPosition();
	CDataGroup *pVector = NULL;

	while (pos != NULL)
	{
		pVector = (CDataGroup *)pChannel->GetNext(pos);
		Show_StaticString(pVector, nRow, 2, pVector->m_strName);

		for (nCol=3; nCol<m_nCols; nCol++)
		{
			ShowAttrCol(pVector, nRow, nCol);
			nRow++;
		}
	}
	
	if (nRow > nRowBegin)
	{//合并通道
		Merge(nRowBegin, 1, nRow, 1);
	}
}
