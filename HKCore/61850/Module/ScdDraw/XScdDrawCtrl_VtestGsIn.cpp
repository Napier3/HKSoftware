//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_VtestGsIn.cpp  CXScdDrawCtrl_VtestGsIn


#include "stdafx.h"
#include "XScdDrawCtrl_VtestGsIn.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridTitleGsIn
CXScdDrawCtrl_VtestGridTitleGsIn::CXScdDrawCtrl_VtestGridTitleGsIn()
{

}

CXScdDrawCtrl_VtestGridTitleGsIn::~CXScdDrawCtrl_VtestGridTitleGsIn()
{

}

void CXScdDrawCtrl_VtestGridTitleGsIn::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
	// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecVtestGinData *pGinData=(CIecVtestGinData *)pData;
	//CIecVtest92Data *p92Data = (CIecVtest92Data*)pData;
	Show_Check(pData, 0, 0, &pGinData->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("GSIN"));
	Show_Hex(pData, 0, 2, &pGinData->m_dwAppID, 2);

	Show_Fiber(pData, 0, 3, &pGinData->m_nFiberIndex);


}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridChsGsIn
CXScdDrawCtrl_VtestGridChsGsIn::CXScdDrawCtrl_VtestGridChsGsIn()
{

}

CXScdDrawCtrl_VtestGridChsGsIn::~CXScdDrawCtrl_VtestGridChsGsIn()
{

}


void CXScdDrawCtrl_VtestGridChsGsIn::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CSclChGsIn *pGinCh = (CSclChGsIn)pData;
	CIecVtestGoutCh *pCh = (CIecVtestGoutCh*)pData;

	Show_Index(pData, nRow, 0);
	Show_String(pData, nRow, 1, &p92Ch->m_strDescExternal, EndEditCell_String_NameAndID );
	ShowVtestCh_AppCh(pData, nRow, 2, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGsIn
CXScdDrawCtrl_VtestGsIn::CXScdDrawCtrl_VtestGsIn()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_VtestGsIn::~CXScdDrawCtrl_VtestGsIn()
{
}

void CXScdDrawCtrl_VtestGsIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset);
}


DWORD CXScdDrawCtrl_VtestGsIn::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_VtestGridTitleGsIn();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_VtestGsIn::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_VtestGridChsGsIn();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	CIecVtestDataBase *pIecVtestData = (CIecVtestDataBase*)pData;

	//指向SCL控制块
	m_pGridCtrlChs->m_pSclCtrl = (CSclCtrlBase*)pIecVtestData->m_pSclRef;

	//指向CFG
	m_pGridCtrlChs->m_pVtestData = pIecVtestData;

	m_pGridCtrlChs->ShowDatas(m_pGridCtrlChs->m_pSclCtrl);

	return XCREATE_SUCC;
}

