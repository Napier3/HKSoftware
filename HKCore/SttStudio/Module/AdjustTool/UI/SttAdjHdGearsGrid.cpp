//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjHdGearsGrid.h"
#include "..\SttAdjBase.h"
#ifndef NOT_USE_XLANGUAGE 
#include "../../../Local/SttAdjMain/XLanguageResource_SttAdjMain.h"
#endif

CSttAdjHdGearsGrid::CSttAdjHdGearsGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strChildDataTypeID = "BinGear";
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
#ifndef NOT_USE_XLANGUAGE 
	CString astrTitle[4] = {/*_T("���")*/g_sLangTxt_Index,/*_T("����")*/g_sLangTxt_SttAdjMain_Name,/*_T("������")*/g_sLangTxt_ControlWord,/*_T("��λ��ֵ")*/g_sLangTxt_SttAdjMain_GearNumValue};
#else
	CString astrTitle[4] = {_T("���"),_T("����"),_T("������"),_T("��λ��ֵ")};
#endif
	CString astrAttrs[4] = {_T(""),_T("Name"), _T("GearCode"), _T("GearValue")};
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
