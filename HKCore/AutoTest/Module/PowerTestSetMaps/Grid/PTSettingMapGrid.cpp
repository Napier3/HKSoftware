#include "StdAfx.h"
#include "PTSettingMapGrid.h"
#include "..\..\GuideBook\DataObj.h"

CPTSettingMapGrid::CPTSettingMapGrid(void)
{
}

CPTSettingMapGrid::~CPTSettingMapGrid(void)
{
}

void CPTSettingMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(PTSETTING_MAP_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPTSettingMapGrid::InitGridTitle()
{
	CString cTempStr[PTSETTING_MAP_GRID_COLS]={_T("���"),_T("����"),_T("ATS��ʶ"),_T("ӳ��·��"),_T("��ֵ"),_T("��λ"),_T("��Сֵ"),_T("���ֵ")};

	int iWidth[PTSETTING_MAP_GRID_COLS]={60,80,80,80,80,80,80,80};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, PTSETTING_MAP_GRID_COLS);
}


void CPTSettingMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	CDataObj *pDataObj = NULL;

	if (nClassID != GBCLASSID_DATAOBJ)
	{
		return;
	}

	Show_Index(pData, nRow, 0);
	CString strTmp;

	pDataObj = (CDataObj*)pData;
	Show_StaticString(pData, nRow, 1, &pDataObj->m_strName);
	Show_StaticString(pData, nRow, 2, &pDataObj->m_strID);
	Show_StaticString(pData, nRow, 3, &pDataObj->m_strDefaultValue);
	Show_StaticString(pData, nRow, 4, &pDataObj->m_strValue);
	Show_StaticString(pData, nRow, 5, &pDataObj->m_strUnit);
	Show_Double(pData, nRow, 6, &pDataObj->m_dMinVal);
	Show_Double(pData, nRow, 7, &pDataObj->m_dMaxVal);
	nRow++;
}

BOOL CPTSettingMapGrid::UpdateData(CExBaseObject *pData)
{
	//��ȡ��֤���½ڵ��ڵ�ǰgrid�ڵ�����
	int nRow = GetDataRow(pData);

	if (nRow != -1)
	{
		ShowData(pData, nRow, FALSE);
		AdjustAllCols(TRUE);
		Invalidate(FALSE);
	}
	else
	{
	}

	return TRUE;
}

