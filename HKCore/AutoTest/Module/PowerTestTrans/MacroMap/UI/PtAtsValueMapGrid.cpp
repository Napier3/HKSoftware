// PtAtsValueMapGrid.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PtAtsValueMapGrid.h"
#include "..\ValueMap.h"
#include "..\MacroMaps.h"

// #include "..\PtAtsMacroMap.h"

#define VALUEMAP_TABLE_COLS   5    

//extern CString _GetAuditFolderPath(const CString &strFolderPath, bool bBackSlash);
// CPtAtsMacroMapGrid
CPtAtsValueMapGrid::CPtAtsValueMapGrid()
{
	m_nAdjustBeginCol = 1;
}

CPtAtsValueMapGrid::~CPtAtsValueMapGrid()
{
	
}

// CPtAtsMacroMapGrid ��Ա����
void CPtAtsValueMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(VALUEMAP_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPtAtsValueMapGrid::InitGridTitle()
{
	CString astrGridTitle[VALUEMAP_TABLE_COLS] = {_T("���"), _T("PowerTest����ֵ����"), _T("PowerTest����ֵsrc"), _T("Ats����ֵdst"), _T("Ats����ֵ����")};
	int  iColType[VALUEMAP_TABLE_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[VALUEMAP_TABLE_COLS]={40, 100, 100, 100, 100};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, VALUEMAP_TABLE_COLS);
}

void CPtAtsValueMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	CValueMap* pValueMap = (CValueMap*)pData;

	if (pValueMap == NULL)
	{
		return;
	}

	Show_Index(pValueMap, nRow, 0);//���
	Show_String(pValueMap, nRow, 1, &pValueMap->m_strName);
	Show_String(pValueMap, nRow, 2, &pValueMap->m_strID);
	Show_String(pValueMap, nRow, 3, &pValueMap->m_strMapID);
	Show_String(pValueMap, nRow, 4, &pValueMap->m_strMapName);

	nRow++;
}

BOOL CPtAtsValueMapGrid::UpdateData(CExBaseObject *pData)
{
	//��ȡ��֤���½ڵ��ڵ�ǰgrid�ڵ�����
	int nRow = GetDataRow(pData);

	if (nRow != -1)
	{
		ShowData(pData, nRow, FALSE);
		Invalidate(FALSE);
	}
	else
	{
	}

	return TRUE;
}

void CPtAtsValueMapGrid::SetMidifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	CMacroMaps *pMaps = (CMacroMaps*)pData->GetAncestor(MPCLASSID_CMACROMAPS);
	pMaps->SetModifiedFlag(bModified);
}

