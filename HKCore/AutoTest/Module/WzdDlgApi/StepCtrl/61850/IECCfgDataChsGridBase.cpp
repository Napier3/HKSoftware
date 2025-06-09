#include "StdAfx.h"
#include "IECCfgDataChsGridBase.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIECCfgDataChsGridBase::CIECCfgDataChsGridBase()
{
	m_nViewChsPath = 1;
	m_pRefDataGrid = NULL;
}


CIECCfgDataChsGridBase::~CIECCfgDataChsGridBase(void)
{
	
}

void CIECCfgDataChsGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	Show_Index(pData, nRow, IECCFG_COL_ID_INDEX);
}

BOOL CIECCfgDataChsGridBase::OnCellRButtonUp(const CCellID &idCell)
{
	return FALSE;
}

