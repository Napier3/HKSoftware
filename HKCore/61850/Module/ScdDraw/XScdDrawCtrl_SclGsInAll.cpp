//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_SclGsInAll.cpp  CXScdDrawCtrl_SclGsInAll


#include "stdafx.h"
#include "XScdDrawCtrl_SclGsInAll.h"

#include "XScdDrawLine_Ch.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_GridTitleSclGsInAll
CXScdDrawCtrl_GridTitleSclGsInAll::CXScdDrawCtrl_GridTitleSclGsInAll()
{

}

CXScdDrawCtrl_GridTitleSclGsInAll::~CXScdDrawCtrl_GridTitleSclGsInAll()
{

}


void CXScdDrawCtrl_GridTitleSclGsInAll::InitGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(0);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CXScdDrawCtrl_GridTitleSclGsInAll::InitGridTitle()
{
	SetColumnWidth(0, 200);
}

void CXScdDrawCtrl_GridTitleSclGsInAll::ShowTitle(CExBaseObject *pData)
{
	//UINT nClassID = pData->GetClassID();

	CIecCfgGinData *pGinData=(CIecCfgGinData *)pData;
	Show_StaticString(pData, 0, 0, _T("GSIN"));

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_GridChsSclGsInAll
CXScdDrawCtrl_GridChsSclGsInAll::CXScdDrawCtrl_GridChsSclGsInAll()
{

}

CXScdDrawCtrl_GridChsSclGsInAll::~CXScdDrawCtrl_GridChsSclGsInAll()
{

}

void CXScdDrawCtrl_GridChsSclGsInAll::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == SCLIECCLASSID_CH_GS_IN);

	CSclChGsIn *pGinCh = (CSclChGsIn*)pData;
	CSclChGsOut *pGoutCh = (CSclChGsOut*)pGinCh->m_pCfgDataRef;

	if (pGoutCh != NULL)
	{
		ASSERT (pGoutCh->GetClassID() == SCLIECCLASSID_CH_GS_OUT);
	}

	Show_Index(pData, nRow, 0, 1);
	Show_StaticString(pData, nRow, 1, pGinCh->GetName());

	if (pGoutCh == NULL)
	{
		Show_StaticString(pData, nRow, 2, m_strEmptyString);
	}
	else
	{
		Show_StaticString(pData, nRow, 2, pGoutCh->fcda_type);
	}

	nRow++;
}


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGsInAll
CXScdDrawCtrl_SclGsInAll::CXScdDrawCtrl_SclGsInAll()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_SclGsInAll::~CXScdDrawCtrl_SclGsInAll()
{
	m_listAllCh.RemoveAll();
}

void CXScdDrawCtrl_SclGsInAll::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_SclGsInAll::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_GridTitleSclGsInAll();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_SclGsInAll::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_GridChsSclGsInAll();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	if (pData==NULL)
	{
		return 0;
	}

	CSclCtrlsGsIn *pSclCtrlsGsIn = (CSclCtrlsGsIn*)pData;
	m_listAllCh.RemoveAll();
	pSclCtrlsGsIn->GetAllChs(m_listAllCh);
	m_pGridCtrlChs->ShowDatas(&m_listAllCh);

	CreateCtrlLines();

	return XCREATE_SUCC;
}

void CXScdDrawCtrl_SclGsInAll::CreateCtrlLines()
{
	POS pos = m_listAllCh.GetHeadPosition();
	CSclChGsIn *pSclCh = NULL;

	while (pos != NULL)
	{
		pSclCh = (CSclChGsIn *)m_listAllCh.GetNext(pos);

		if (pSclCh->m_pCfgDataRef != NULL)
		{
			CXScdDrawLine_Ch *pNew = new CXScdDrawLine_Ch();
			pNew->m_pBeginObj = pSclCh->m_pCfgDataRef;
			pNew->m_pEndObj = pSclCh;
			pNew->m_pEndElement = this;
			AddNewChild(pNew);
		}
	}
}

