//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_CfgGsIn.cpp  CXScdDrawCtrl_CfgGsIn


#include "stdafx.h"
#include "XScdDrawCtrl_CfgGsIn.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGridTitleGsIn
CXScdDrawCtrl_CfgGridTitleGsIn::CXScdDrawCtrl_CfgGridTitleGsIn()
{

}

CXScdDrawCtrl_CfgGridTitleGsIn::~CXScdDrawCtrl_CfgGridTitleGsIn()
{

}

void CXScdDrawCtrl_CfgGridTitleGsIn::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
	// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecCfgGinData *pGinData=(CIecCfgGinData *)pData;
	//CIecCfg92Data *p92Data = (CIecCfg92Data*)pData;
	Show_Check(pData, 0, 0, &pGinData->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("GS订阅配置"));
	Show_Hex(pData, 0, 2, &pGinData->m_dwAppID, 2);

	Show_Fiber(pData, 0, 3, &pGinData->m_nFiberIndex);
//	Show_ChanStyle(pData, 0,4,    &pGinData->m_nChanStyleIndex);
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGridChsGsIn
CXScdDrawCtrl_CfgGridChsGsIn::CXScdDrawCtrl_CfgGridChsGsIn()
{

}

CXScdDrawCtrl_CfgGridChsGsIn::~CXScdDrawCtrl_CfgGridChsGsIn()
{

}


void  CXScdDrawCtrl_CfgGridChsGsIn::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pData;

	if (pGinCh->m_strDataType == g_strGooseChType_Single || pGinCh->m_strDataType == g_strGooseChType_Double)
	{
		PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrAppCh, pData, NULL, EndEditCell_AppCh_Gin);
		pVCellData->pExBaseList = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);
		Show_DataType_Val(pData, nRow, nCol, *pstrAppCh, pVCellData);

		//Show_DataType_Val(pData, nRow, nCol, iecfg_GinAppChDataType, pstrAppCh, EndEditCell_AppCh_Gin);
		//Show_DWORD_Check(pData, nRow, nCol, &pGinCh->m_dwAppChID,8, TRUE,  EndEditCell_AppCh_Gin);
	}
	else
	{
		*pstrAppCh = _T("---");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
}


void CXScdDrawCtrl_CfgGridChsGsIn::EndEditCell_AppCh_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGinCh *pInCh = (CIecCfgGinCh*)pVellData->pObj;
	ASSERT (pInCh != NULL);

	//
	CDataType *pDataType = (CDataType*)pVellData->pExBaseList;
	ASSERT (pDataType != NULL);

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(pCell->dwValue);

	if (pValue == NULL)
	{
		return;
	}

	//pInCh->AddBinString(pValue->m_strID);
	pInCh->SetBinString(pValue->m_strID);
	pInCh->InitAppIDText();
	pCell->szText = pInCh->m_strAppChIDText;
	pGrid->AutoSizeColumn(nCol);
	pGrid->InvalidateGrid(FALSE);

	CIecCfgGinDatas *pGinDatas = (CIecCfgGinDatas*)pInCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
	CIecCfgGinAppChMaps *pMaps = pGinDatas->GetIecCfgGinAppChMaps();
	CIecCfgGinAppChMap *pMap =pMaps->Bind(pValue->m_strID, pInCh);

	CWnd *pParentWnd = pGrid->GetParentWnd();
	pParentWnd->SendMessage(WM_GIN_CH_APPID_CHANGED, (WPARAM)pMap, (LPARAM)pMap);
}

void CXScdDrawCtrl_CfgGridChsGsIn::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecCfgGinCh *pCh = (CIecCfgGinCh*)pData;

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, &pCh->m_strName);
	//ShowCfgCh_AppCh(pData, nRow, 2, &pCh->m_strAppChID, iecfg_GinAppChDataType);
	ShowCfgCh_AppCh(pData, nRow, 2, &pCh->m_strAppChIDText, iecfg_GinAppChDataType);

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGsIn
CXScdDrawCtrl_CfgGsIn::CXScdDrawCtrl_CfgGsIn()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_CfgGsIn::~CXScdDrawCtrl_CfgGsIn()
{
}

void CXScdDrawCtrl_CfgGsIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_CfgGsIn::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_CfgGridTitleGsIn();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_CfgGsIn::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_CfgGridChsGsIn();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;

	//指向SCL控制块
	m_pGridCtrlChs->m_pSclCtrl = (CSclCtrlBase*)pIecCfgData->m_pSclRef;

	//指向CFG
	m_pGridCtrlChs->m_pCfgData = pIecCfgData;

	m_pGridCtrlChs->ShowDatas(pIecCfgData->m_pCfgChs);

	return XCREATE_SUCC;
}
