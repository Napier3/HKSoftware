//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjModuleMeasGrid.h"
#include "..\SttAdjBase.h"

CSttAdjModuleMeasGrid::CSttAdjModuleMeasGrid()
{
	//��ʼ������

	//��ʼ����Ա����
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
	CString astrTitle[6] = {_T("���"),_T("ͨ��"),_T("г��"), _T("��ֵ"),_T("��λ"), _T("Ƶ��")};
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

	//ͨ��
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	long nRowBegin = nRow; //���ںϲ�ͨ������
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
	{//�ϲ�ͨ��
		Merge(nRowBegin, 1, nRow, 1);
	}
}
