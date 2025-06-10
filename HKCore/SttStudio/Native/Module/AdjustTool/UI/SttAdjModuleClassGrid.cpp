//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjModuleClassGrid.h"
#include "..\SttAdjBase.h"
#include "..\SttMesLocalDb.h"

CSttAdjModuleClassGrid::CSttAdjModuleClassGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	//m_strChildDataTypeID = STT_ADJ_DATA_TYPE_SttModuleClass;
}

CSttAdjModuleClassGrid::~CSttAdjModuleClassGrid()
{

}


void CSttAdjModuleClassGrid::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(11);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModuleClassGrid::InitGridTitle()
{
	CString astrTitle[11] = {_T("���"), _T("����"), _T("ģ��ID"),_T("ģ������"),  _T("ģ��Ӳ��λ��")
		, _T("Ƶ��"), _T("ͨ����"), _T("�ͺ�"), _T("Idcͨ�����ֵ")
		, _T("Udcͨ�����ֵ"), _T("ͨ�����ֵ")};
	CString astrAttrs[11] = {_T(""),_T("Name"), _T("ID"), _T("ModuleType"), _T("ModulePos"), _T("Freq"), _T("ChannelCount"), _T("Model"), _T("UdcMax"), _T("IdcMax"), _T("ChMax") };
	
	int nWidth[11] = {40,160,100,100,100,60,60,100,100,100,100};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 11);
	InitGridColAttrs(astrAttrs, 11);
}

void CSttAdjModuleClassGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pDataGroup  =  (CDataGroup*)pData;
	Show_Index(pData,  nRow,  0);
	Show_String(pData, nRow,  1,  &pData->m_strName, EndEditCell_String_Name);//Show_StaticString(pData, nRow,  1,  pData->m_strName)
	Show_String(pData, nRow,  2,  &pData->m_strID, EndEditCell_String_ID);

	for (long nCol = 3;  nCol  <  m_nCols;   nCol++)
	{
		ShowAttrCol(pDataGroup, nRow, nCol);
	}

	nRow++;

}

CDataType* CSttAdjModuleClassGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}

