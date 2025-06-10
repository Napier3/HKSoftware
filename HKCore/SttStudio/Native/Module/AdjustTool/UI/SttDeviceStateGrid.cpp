//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttDeviceStateGrid.h"
#include "..\SttAdjBase.h"

CSttDeviceStateGrid::CSttDeviceStateGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_Channel;
}

CSttDeviceStateGrid::~CSttDeviceStateGrid()
{

}


void CSttDeviceStateGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttDeviceStateGrid::InitGridTitle()
{
	CString astrTitle[5] = {_T("���"),_T("ͨ��"),_T("����ѹ"),_T("��С��ѹ"),_T("�Ƿ����")};
	CString astrAttrs[5] = {_T(""),_T("Name"), _T("VoltMax"),_T("VoltMin"), _T("IsOverLoad")};
	int nWidth[5]={40,120,120,120,120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 5);
	InitGridColAttrs(astrAttrs, 5);
}

void CSttDeviceStateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDataGroup *pChannel = (CDataGroup*)pData;
	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pChannel->m_strName);

	for (long nCol = 2; nCol <= 4; nCol++)
	{
		ShowAttrCol(pChannel, nRow, nCol);
	}

	nRow++;
}
