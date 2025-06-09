//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_CfgSvIn.cpp  CXScdDrawCtrl_CfgSvIn


#include "stdafx.h"
#include "XScdDrawCtrl_CfgSvIn.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGridTitleSvIn
CXScdDrawCtrl_CfgGridTitleSvIn::CXScdDrawCtrl_CfgGridTitleSvIn()
{

}

CXScdDrawCtrl_CfgGridTitleSvIn::~CXScdDrawCtrl_CfgGridTitleSvIn()
{

}

void CXScdDrawCtrl_CfgGridTitleSvIn::ShowTitle(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	CIecCfg92Data *p92Data = (CIecCfg92Data*)pData;
	Show_Check(pData, 0, 0, &p92Data->m_nUseFlag);
	Show_StaticString(pData, 0, 1, _T("SVIN"));
	Show_Hex(pData, 0, 2, &p92Data->m_dwAppID, 2);
	Show_Fiber(pData, 0, 3,    &p92Data->m_nFiberIndex);

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgGridChsSvIn
CXScdDrawCtrl_CfgGridChsSvIn::CXScdDrawCtrl_CfgGridChsSvIn()
{

}

CXScdDrawCtrl_CfgGridChsSvIn::~CXScdDrawCtrl_CfgGridChsSvIn()
{

}


void CXScdDrawCtrl_CfgGridChsSvIn::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == SCLIECCLASSID_CH_SMV_IN);

	CSclChSmvIn *pCh = (CSclChSmvIn*)pData;
	CIecCfg92Ch *p92Ch = (CIecCfg92Ch*)pCh->m_pCfgDataRef;

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pCh->GetName());

	if (p92Ch == NULL)
	{
		Show_StaticString(pData, nRow, 2, m_strEmptyString);
	}
	else
	{
		ShowCfgCh_AppCh(p92Ch, nRow, 2, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);
	}

	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_CfgSvIn
CXScdDrawCtrl_CfgSvIn::CXScdDrawCtrl_CfgSvIn()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_CfgSvIn::~CXScdDrawCtrl_CfgSvIn()
{
}

void CXScdDrawCtrl_CfgSvIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_CfgSvIn::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_CfgGridTitleSvIn();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_CfgSvIn::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_CfgGridChsSvIn();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;

	//指向SCL控制块
	m_pGridCtrlChs->m_pSclCtrl = (CSclCtrlBase*)pIecCfgData->m_pSclRef;

	//指向CFG
	m_pGridCtrlChs->m_pCfgData = pIecCfgData;

	m_pGridCtrlChs->ShowDatas(m_pGridCtrlChs->m_pSclCtrl);

	return XCREATE_SUCC;
}
