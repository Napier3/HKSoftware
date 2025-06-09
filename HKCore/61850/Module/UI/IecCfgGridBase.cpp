#include "StdAfx.h"
#include "IecCfgGridBase.h"


//////////////////////////////////////////////////////////////////////////
//CIecCfgGridBase

CIecCfgGridBase::CIecCfgGridBase()
{
	m_nAdjustBeginCol = 0;
}


CIecCfgGridBase::~CIecCfgGridBase(void)
{
	
}

void CIecCfgGridBase::SetMidifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	iecfg_SetModified(pData);
}

CDataType* CIecCfgGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}


void CIecCfgGridBase::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	Show_DataType_Val(pData, nRow, nCol, strDataType, pstrAppCh, EndEditCell_AppCh);
}


void CIecCfgGridBase::EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
}

void CIecCfgGridBase::SetGridCellFgClr(int nRow,int nCol,COLORREF crFgColor)
{
	CGridCell* pCell = GetCell(nRow, nCol);

	if (pCell)
	{
		pCell->crFgClr = crFgColor;
	}
}

void CIecCfgGridBase::SetRowFgClr(int nRow,int nBeginCol ,int nEndCol,COLORREF crFgColor)
{
	for (int nIndex = nBeginCol;nIndex<=nEndCol;nIndex++)
	{
		SetGridCellFgClr(nRow,nIndex,crFgColor);
	}
}



