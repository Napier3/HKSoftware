#include "StdAfx.h"
#include "IecCfgSmvDataChsGridBase.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgSmvDataChsGridBase::CIecCfgSmvDataChsGridBase()
{
	
}


CIecCfgSmvDataChsGridBase::~CIecCfgSmvDataChsGridBase(void)
{
	
}


void  CIecCfgSmvDataChsGridBase::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pData;
	
	if (iecfg_IsCurrSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_I, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsVolSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_U, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsDCVolSmvChType(pSmvCh->m_strChType))//zhouhj 20211012 直流电压
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_DCU, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsDCCurSmvChType(pSmvCh->m_strChType))//zhouhj 20211012 直流电流
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_DCI, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsNeutralUSmvChType(pSmvCh->m_strChType))//zhouhj 20211012  中性母线电压
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_NeutralU, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsUTCTimeSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_T, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsStateValueChType(pSmvCh->m_strChType))//zhouhj 20211012 增加用于CommonFT3 Smv通道状态值
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_StateValue, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsOtherChType(pSmvCh->m_strChType))//zhouhj 20211012 增加用于CommonFT3 Smv通道其它
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_Other, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_Is6CurrSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_6I, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_Is6VolSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_6U, pstrAppCh, EndEditCell_AppCh);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_U, pstrAppCh, EndEditCell_AppCh);
	}
}



void CIecCfgSmvDataChsGridBase::ShowCfgCh_Type(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrChType,const CString &strDataType, BOOL bSetColor)
{
	Show_DataType_Val(pData, nRow, nCol, strDataType, pstrChType, EndEditCell_ChType);
}


void CIecCfgSmvDataChsGridBase::EndEditCell_ChType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pVellData->pObj;
	ASSERT (pSmvCh != NULL);

	CString strOldType = pSmvCh->m_strChType;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	if (strOldType == pSmvCh->m_strChType)
	{
		return;
	}

	pSmvCh->InitAfterRead();
	CIecCfgSmvDataChsGridBase *pChsGrid = (CIecCfgSmvDataChsGridBase*)pGrid;
	long nChAppCol = pChsGrid->GetAppChColIndex();
	pChsGrid->FreeExBaseCellData(nRow, nChAppCol);
	pChsGrid->ShowCfgCh_AppCh(pSmvCh, nRow, nChAppCol, &pSmvCh->m_strAppChID, _T(""), FALSE);
}


void CIecCfgSmvDataChsGridBase::SetAbc(BOOL bSetU, BOOL bSetI)
{

}

void CIecCfgSmvDataChsGridBase::SetPabc(BOOL bSetU, BOOL bSetI)
{

}

void CIecCfgSmvDataChsGridBase::SetSabc(BOOL bSetU, BOOL bSetI)
{

}

void CIecCfgSmvDataChsGridBase::SetTabc(BOOL bSetU, BOOL bSetI)
{

}

void CIecCfgSmvDataChsGridBase::Setabc5(BOOL bSetU, BOOL bSetI)
{

}

void CIecCfgSmvDataChsGridBase::Setabc6(BOOL bSetU, BOOL bSetI)
{

}

