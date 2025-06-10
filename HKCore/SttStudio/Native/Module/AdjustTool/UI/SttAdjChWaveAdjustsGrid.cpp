//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjChWaveAdjustsGrid.h"
#include "..\SttAdjBase.h"

CSttAdjChWaveAdjustsGrid::CSttAdjChWaveAdjustsGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_GearAdjust;
}

CSttAdjChWaveAdjustsGrid::~CSttAdjChWaveAdjustsGrid()
{

}


void CSttAdjChWaveAdjustsGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(6);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjChWaveAdjustsGrid::InitGridTitle()
{
	CString astrTitle[6] = {_T("���"),_T("��λ"), _T("��λֵ"), _T("��ֵϵ��"),_T("��Ư"),_T("��λУ׼")};
	CString astrAttrs[6] = {_T(""),_T("GearValue"),  _T("GearValue"), _T("Coef"),_T("Zero"), _T("Angle")};
	int nWidth[6]={40,120, 120, 120,120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 6);
	InitGridColAttrs(astrAttrs, 6);
}

void CSttAdjChWaveAdjustsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pGear = (CDataGroup*)pData;
	CDvmData *pDvmData = (CDvmData *)pGear->FindByID(_T("GearValue"));
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pGear->m_strName);
	Show_String(pData, nRow, 2,  &pDvmData->m_strValue);

	CDataGroup *AdjustItem = (CDataGroup*)pGear->FindByDataType(STT_ADJ_DATA_TYPE_AdjustItem);

	if (AdjustItem != NULL)
	{
		for (long nCol = 3; nCol <= 5; nCol++)
		{
			ShowAttrCol(AdjustItem, nRow, nCol);
		}
	}

	nRow++;
}
