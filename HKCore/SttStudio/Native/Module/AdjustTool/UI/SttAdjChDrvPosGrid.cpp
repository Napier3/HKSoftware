//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjChDrvPosGrid.h"
#include "..\SttAdjBase.h"

CSttAdjChDrvPosGrid::CSttAdjChDrvPosGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	//m_strChildDataTypeID = STT_ADJ_DATA_TYPE_ChDrvPos;
}

CSttAdjChDrvPosGrid::~CSttAdjChDrvPosGrid()
{

}


void CSttAdjChDrvPosGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjChDrvPosGrid::InitGridTitle()
{
	CString astrTitle[4] = {_T("���"),_T("����"),_T("ͨ��ID"),_T("ͨ�����")};
	CString astrAttrs[4] = {_T(""),_T("Name"), _T("ID"), _T("Index")};
	int nWidth[4]={40,120,100,100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 4);
	InitGridColAttrs(astrAttrs, 4);
}

void CSttAdjChDrvPosGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)//DTMCLASSID_CDATAGROUP
	{
		return;
	}

	CDvmData *pChDrvPos = (CDvmData*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, &pData->m_strName);
	Show_StaticString(pData, nRow, 2, pData->m_strID);
	Show_String(pData, nRow, 3, &pChDrvPos->m_strValue);

	//for (long nCol=2; nCol<m_nCols; nCol++)
	//{
	// 	ShowAttrCol(pChDrvPos, nRow, nCol);
	//}

	nRow++;
}
