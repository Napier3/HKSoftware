#include "StdAfx.h"
#include "IecCfgDataChsGridBase.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgDataChsGridBase::CIecCfgDataChsGridBase()
{
	m_nViewChsPath = 1;
}


CIecCfgDataChsGridBase::~CIecCfgDataChsGridBase(void)
{
	
}

void CIecCfgDataChsGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	Show_Index(pData, nRow, IECCFG_COL_ID_INDEX);
}


BOOL CIecCfgDataChsGridBase::OnCellRButtonUp(const CCellID &idCell)
{
	return FALSE;
}

