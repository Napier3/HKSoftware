#include "StdAfx.h"
#include "IecCfgSmvData6044ChsGrid.h"
#include "..\XLanguageResourceIec.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgSmvData6044ChsGrid::CIecCfgSmvData6044ChsGrid()
{

}


CIecCfgSmvData6044ChsGrid::~CIecCfgSmvData6044ChsGrid(void)
{
	
}

void CIecCfgSmvData6044ChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_6044CH);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData6044ChsGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_6044CH]={
		g_sLtxt_SMVChannel,g_sLtxt_Description,g_sLtxt_ChannelType,
		g_sLtxt_TestDeviceChannel//_T("SMV通道"),_T("描述"),_T("通道类型"),_T("测试仪通道")
	};
	int iWidth[IECCFG_COLS_6044CH]={60,160, 80,90};

	CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_6044CH);
}


void CIecCfgSmvData6044ChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG6044CH);

	if (nClassID != CFGCLASSID_CIECCFG6044CH)
	{
		return;
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg6044Ch *p6044Ch = (CIecCfg6044Ch*)pData;

	Show_String(pData, nRow, IECCFG_COL_ID_6044CH_DESC, &p6044Ch->m_strID, EndEditCell_String_NameAndID );
	ShowCfgCh_Type(pData, nRow, IECCFG_COL_ID_6044CH_CHTYPE, &p6044Ch->m_strChType, iecfg_Smv6044ChDataType);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_6044CH_APPCH, &p6044Ch->m_strAppChID, iecfg_SmvAppChDataType);

	nRow++;
}
