//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_SclSvIn.cpp  CXScdDrawCtrl_SclSvIn


#include "stdafx.h"
#include "XScdDrawCtrl_SclSvIn.h"
#include "XScdDrawLine_Ch.h"

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGridTitleSvIn
CXScdDrawCtrl_SclGridTitleSvIn::CXScdDrawCtrl_SclGridTitleSvIn()
{

}

CXScdDrawCtrl_SclGridTitleSvIn::~CXScdDrawCtrl_SclGridTitleSvIn()
{

}

void CXScdDrawCtrl_SclGridTitleSvIn::ShowTitle(CExBaseObject *pData)
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
//CXScdDrawCtrl_SclGridChsSvIn
CXScdDrawCtrl_SclGridChsSvIn::CXScdDrawCtrl_SclGridChsSvIn()
{

}

CXScdDrawCtrl_SclGridChsSvIn::~CXScdDrawCtrl_SclGridChsSvIn()
{

}


void CXScdDrawCtrl_SclGridChsSvIn::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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
//CXScdDrawCtrl_SclSvIn
CXScdDrawCtrl_SclSvIn::CXScdDrawCtrl_SclSvIn()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_SclSvIn::~CXScdDrawCtrl_SclSvIn()
{
}

void CXScdDrawCtrl_SclSvIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_SclSvIn::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_SclGridTitleSvIn();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_SclSvIn::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_SclGridChsSvIn();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CSclCtrlBase *pSclCtrl = (CSclCtrlBase*)pIecCfgData->m_pSclRef;

	//指向SCL控制块
	m_pGridCtrlChs->m_pSclCtrl = (CSclCtrlBase*)pIecCfgData->m_pSclRef;

	//指向CFG
	m_pGridCtrlChs->m_pCfgData = pIecCfgData;

	m_pGridCtrlChs->ShowDatas(m_pGridCtrlChs->m_pSclCtrl);

	//通道连线
	POS pos = pSclCtrl->GetHeadPosition();
	CSclChSmvIn *pSclCh = NULL;
	CIecCfgDataSmvChBase *pCfgCh = NULL;
	CIecCfgChsBase *pCfgChs = pIecCfgData->m_pCfgChs;

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvIn *)pSclCtrl->GetNext(pos);

		//SvOut通道进行关联
		pCfgCh = (CIecCfgDataSmvChBase*)pCfgChs->FindByID(pSclCh->fcda_name);

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

