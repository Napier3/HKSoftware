//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_SclGsIn.cpp  CXScdDrawCtrl_SclGsIn


#include "stdafx.h"
#include "XScdDrawCtrl_SclGsIn.h"

#include "XScdDrawLine_Ch.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGridTitleGsIn
CXScdDrawCtrl_SclGridTitleGsIn::CXScdDrawCtrl_SclGridTitleGsIn()
{

}

CXScdDrawCtrl_SclGridTitleGsIn::~CXScdDrawCtrl_SclGridTitleGsIn()
{

}

void CXScdDrawCtrl_SclGridTitleGsIn::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
	// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecCfgGinData *pGinData=(CIecCfgGinData *)pData;
	//CIecCfg92Data *p92Data = (CIecCfg92Data*)pData;
	Show_Check(pData, 0, 0, &pGinData->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("GSIN"));
	Show_Hex(pData, 0, 2, &pGinData->m_dwAppID, 2);

	Show_Fiber(pData, 0, 3, &pGinData->m_nFiberIndex);


}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGridChsGsIn
CXScdDrawCtrl_SclGridChsGsIn::CXScdDrawCtrl_SclGridChsGsIn()
{

}

CXScdDrawCtrl_SclGridChsGsIn::~CXScdDrawCtrl_SclGridChsGsIn()
{

}


void CXScdDrawCtrl_SclGridChsGsIn::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CSclChGsIn *pGinCh = (CSclChGsIn*)pData;
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pGinCh->m_pCfgDataRef;

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pGinCh->GetName());

	if (pGoutCh == NULL)
	{
		Show_StaticString(pData, nRow, 2, m_strEmptyString);
	}
	else
	{
		ShowCfgCh_AppCh(pGoutCh, nRow, 2, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);
	}

	nRow++;
}


void  CXScdDrawCtrl_SclGridChsGsIn::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;

	if (pGoutCh->m_strDataType == g_strGooseChType_Single)
	{
		Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_single, pstrAppCh, EndEditCell_AppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Double)
	{
		Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_double, pstrAppCh, EndEditCell_AppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Time)		//_T("UTCTime")
	{
		// 		Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_double, pstrAppCh, EndEditCell_AppCh);
		*pstrAppCh = _T("UTCTime");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Float)		//_T("float")
	{
		*pstrAppCh = _T("0.0");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Struct)		//_T("struct")
	{
		*pstrAppCh = _T("1000000000000");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else
	{
		*pstrAppCh = _T("---");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
}

void CXScdDrawCtrl_SclGridChsGsIn::EndEditCell_ChDataType_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
	ASSERT (pGoutCh != NULL);

	CString strOldType = pGoutCh->m_strDataType;

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	if (strOldType == pGoutCh->m_strDataType)
	{
		return;
	}

	CXScdDrawCtrl_SclGridChsGsIn *pExBaseGrid = (CXScdDrawCtrl_SclGridChsGsIn*)pGrid;
	pExBaseGrid->FreeExBaseCellData(nRow, 2);
	pExBaseGrid->ShowCfgCh_AppCh(pGoutCh, nRow, 2, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);
}


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGsIn
CXScdDrawCtrl_SclGsIn::CXScdDrawCtrl_SclGsIn()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_SclGsIn::~CXScdDrawCtrl_SclGsIn()
{
}

void CXScdDrawCtrl_SclGsIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_SclGsIn::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_SclGridTitleGsIn();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_SclGsIn::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_SclGridChsGsIn();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;

	CSclCtrlBase *pSclCtrl = (CSclCtrlBase*)pIecCfgData->m_pSclRef;//cgl

	if (pSclCtrl==NULL)
	{
		return 0;
	}

	//指向SCL控制块
	m_pGridCtrlChs->m_pSclCtrl = (CSclCtrlBase*)pIecCfgData->m_pSclRef;

	//指向CFG
	m_pGridCtrlChs->m_pCfgData = pIecCfgData;

	m_pGridCtrlChs->ShowDatas(m_pGridCtrlChs->m_pSclCtrl);


	//通道连线
	POS pos = pSclCtrl->GetHeadPosition();
	CSclChGsIn *pSclCh = NULL;

	CIecCfgDataGooseChBase *pCfgCh = NULL;
	//CIecCfgGoutCh *pCfgCh = NULL;
    
	CIecCfgChsBase *pCfgChs = pIecCfgData->m_pCfgChs;

	while (pos != NULL)
	{
		pSclCh = (CSclChGsIn *)pSclCtrl->GetNext(pos);

		//SvOut通道进行关联
	    pCfgCh = (CIecCfgDataGooseChBase*)pCfgChs->FindByID(pSclCh->fcda_name);

		if (pCfgCh != NULL)
		{
			CXScdDrawLine_Ch *pNew = new CXScdDrawLine_Ch();
			pNew->m_pBeginObj = pCfgCh;
			pNew->m_pEndObj = pSclCh;
			pNew->m_pEndElement = this;
			AddNewChild(pNew);
		}
	}

	return XCREATE_SUCC;
}