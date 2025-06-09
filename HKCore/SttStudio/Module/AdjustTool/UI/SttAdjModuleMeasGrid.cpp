//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjModuleMeasGrid.h"
#include "..\SttAdjBase.h"
#ifndef NOT_USE_XLANGUAGE
#include "..\..\..\Local\SttAdjMain\XLanguageResource_SttAdjMain.h"
#endif
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
#ifndef NOT_USE_XLANGUAGE
	CString astrTitle[6] = {/*_T("���")*/g_sLangTxt_Index,/*_T("ͨ��")*/g_sLangTxt_SttAdjMain_Channel,/*_T("г��")*/g_sLangTxt_SttAdjMain_Harmonic,/* _T("��ֵ")*/g_sLangTxt_SttAdjMain_Mag,/*_T("��λ")*/g_sLangTxt_SttAdjMain_Phase, /*_T("Ƶ��")*/g_sLangTxt_Frequency};
#else
	CString astrTitle[6] = {_T("���"),_T("ͨ��"),_T("г��"), _T("��ֵ"),_T("��λ"), _T("Ƶ��")};
#endif
	CString astrAttrs[6] = {_T("Index"),_T("Channel"),_T("Harm"),_T("Mag"),  _T("Angle"), _T("Freq")};
	int nWidth[6]={60, 80, 80, 80, 80, 80};

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
		Show_Index(pData, nRow, 0);

		for (nCol=3; nCol<m_nCols; nCol++)
		{
			ShowAttrCol(pVector, nRow, nCol);
		}

		nRow++;
		InsertRow(_T(""));
	}
	
	if (nRow > nRowBegin)
	{//�ϲ�ͨ��
		Merge(nRowBegin, 1, nRow-1, 1);
	}
}
