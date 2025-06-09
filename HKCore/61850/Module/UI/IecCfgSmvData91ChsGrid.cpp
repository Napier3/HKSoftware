#include "StdAfx.h"
#include "IecCfgSmvData91ChsGrid.h"
#include "..\XLanguageResourceIec.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgSmvData91ChsGrid::CIecCfgSmvData91ChsGrid()
{

}


CIecCfgSmvData91ChsGrid::~CIecCfgSmvData91ChsGrid(void)
{
	
}

void CIecCfgSmvData91ChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_91CH);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData91ChsGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_91CH]={
		g_sLtxt_SMVChannel,g_sLtxt_Description,g_sLtxt_ChannelType,
		g_sLtxt_TestDeviceChannel//_T("SMV通道"),_T("描述"),_T("通道类型"),_T("测试仪通道")
	};
	int iWidth[IECCFG_COLS_91CH]={60,160, 80,90};

	CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_91CH);
}


void CIecCfgSmvData91ChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG91CH);

	if (nClassID != CFGCLASSID_CIECCFG91CH)
	{
		return;
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg91Ch *p91Ch = (CIecCfg91Ch*)pData;

	Show_String(pData, nRow, IECCFG_COL_ID_91CH_DESC, &p91Ch->m_strID, EndEditCell_String_NameAndID );
	ShowCfgCh_Type(pData, nRow, IECCFG_COL_ID_91CH_CHTYPE, &p91Ch->m_strChType, iecfg_Smv91ChDataType);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_91CH_APPCH, &p91Ch->m_strAppChID, iecfg_SmvAppChDataType);

	nRow++;
}

void CIecCfgSmvData91ChsGrid::UpdateType(CExBaseObject *pData, const int& nRow)
{
	CIecCfg91Ch *p91Ch = (CIecCfg91Ch*)pData;
		
	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_91CH_CHTYPE, iecfg_Smv91ChDataType, &p91Ch->m_strChType);
	RedrawCell(nRow, IECCFG_COL_ID_91CH_CHTYPE);
}

void CIecCfgSmvData91ChsGrid::UpdateType()
{
	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 1;

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		UpdateType(pObj, nRowIndex);
		nRowIndex++;
	}
}

