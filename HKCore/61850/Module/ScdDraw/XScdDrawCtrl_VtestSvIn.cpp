//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_VtestSvIn.cpp  CXScdDrawCtrl_VtestSvIn


#include "stdafx.h"
#include "XScdDrawCtrl_VtestSvIn.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridTitleSvIn
CXScdDrawCtrl_VtestGridTitleSvIn::CXScdDrawCtrl_VtestGridTitleSvIn()
{

}

CXScdDrawCtrl_VtestGridTitleSvIn::~CXScdDrawCtrl_VtestGridTitleSvIn()
{

}

void CXScdDrawCtrl_VtestGridTitleSvIn::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecVtest92Data *p92Data = (CIecVtest92Data*)pData;
	Show_Check(pData, 0, 0, &p92Data->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("SVIN"));
	Show_Hex(pData, 0, 2, &p92Data->m_dwAppID, 2);
	Show_Fiber(pData, 0, 3,    &p92Data->m_nFiberIndex);

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGridChsSvIn
CXScdDrawCtrl_VtestGridChsSvIn::CXScdDrawCtrl_VtestGridChsSvIn()
{

}

CXScdDrawCtrl_VtestGridChsSvIn::~CXScdDrawCtrl_VtestGridChsSvIn()
{

}


void CXScdDrawCtrl_VtestGridChsSvIn::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == SCLIECCLASSID_CH_SMV_IN);

	CSclChSmvIn *pCh = (CSclChSmvIn*)pData;
	CIecVtest92Ch *p92Ch = (CIecVtest92Ch*)pCh->m_pVtestDataRef;

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pCh->GetName());

	if (p92Ch == NULL)
	{
		Show_StaticString(pData, nRow, 2, m_strEmptyString);
	}
	else
	{
		ShowVtestCh_AppCh(p92Ch, nRow, 2, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestSvIn
CXScdDrawCtrl_VtestSvIn::CXScdDrawCtrl_VtestSvIn()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_VtestSvIn::~CXScdDrawCtrl_VtestSvIn()
{
}

void CXScdDrawCtrl_VtestSvIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset);
}


DWORD CXScdDrawCtrl_VtestSvIn::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_VtestGridTitleSvIn();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_VtestSvIn::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_VtestGridChsSvIn();
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

