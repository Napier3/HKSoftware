//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_SclSvInAll.cpp  CXScdDrawCtrl_SclSvInAll


#include "stdafx.h"
#include "XScdDrawCtrl_SclSvInAll.h"
#include "XScdDrawLine_Ch.h"

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_GridTitleSclSvInAll
CXScdDrawCtrl_GridTitleSclSvInAll::CXScdDrawCtrl_GridTitleSclSvInAll()
{

}

CXScdDrawCtrl_GridTitleSclSvInAll::~CXScdDrawCtrl_GridTitleSclSvInAll()
{

}


void CXScdDrawCtrl_GridTitleSclSvInAll::InitGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(0);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CXScdDrawCtrl_GridTitleSclSvInAll::InitGridTitle()
{
	SetColumnWidth(0, 200);
}

void CXScdDrawCtrl_GridTitleSclSvInAll::ShowTitle(CExBaseObject *pData)
{
	//UINT nClassID = pData->GetClassID();

	//CIecCfgGinData *pGinData=(CIecCfgGinData *)pData;
	Show_StaticString(pData, 0, 0, _T("SVIN"));

}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_GridChsSclSvInAll
CXScdDrawCtrl_GridChsSclSvInAll::CXScdDrawCtrl_GridChsSclSvInAll()
{

}

CXScdDrawCtrl_GridChsSclSvInAll::~CXScdDrawCtrl_GridChsSclSvInAll()
{

}


void CXScdDrawCtrl_GridChsSclSvInAll::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	CSclChSmvIn *pCh = (CSclChSmvIn*)pData;
	CSclChSmvOut *pOutCh = (CSclChSmvOut*)pCh->m_pCfgDataRef;

	if (pOutCh != NULL)
	{
		ASSERT (pOutCh->GetClassID() == SCLIECCLASSID_CH_SMV_OUT);
	}

	Show_Index(pData, nRow, 0, 1);
	Show_StaticString(pData, nRow, 1, pCh->GetName());

	Show_StaticString(pData, nRow, 2, m_strEmptyString);
// 	if (pOutCh == NULL)
// 	{
// 		Show_StaticString(pData, nRow, 2, m_strEmptyString);
// 	}
// 	else
// 	{
// 		Show_StaticString(pData, nRow, 2, pOutCh->GetName());
// 	}
	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclSvInAll
CXScdDrawCtrl_SclSvInAll::CXScdDrawCtrl_SclSvInAll()
{
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_SclSvInAll::~CXScdDrawCtrl_SclSvInAll()
{
	m_listAllCh.RemoveAll();
}

void CXScdDrawCtrl_SclSvInAll::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrlBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


DWORD CXScdDrawCtrl_SclSvInAll::XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlTitle == NULL);
	m_pGridCtrlTitle = new CXScdDrawCtrl_GridTitleSclSvInAll();
	m_pGridCtrlTitle->Create(pParentWnd);
	m_pGridCtrlTitle->InitGrid();
	m_pGridCtrlTitle->ShowDatas((CExBaseList*)pData);

	return XCREATE_SUCC;
}

DWORD CXScdDrawCtrl_SclSvInAll::XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd)
{
	ASSERT (m_pGridCtrlChs == NULL);
	m_pGridCtrlChs = new CXScdDrawCtrl_GridChsSclSvInAll();
	m_pGridCtrlChs->Create(pParentWnd);
	m_pGridCtrlChs->InitGrid();

	if (pData==NULL)
	{
		return 0;
	}

	CSclCtrlsSmvIn *pSclCtrlsIn = (CSclCtrlsSmvIn*)pData;
	m_listAllCh.RemoveAll();
	pSclCtrlsIn->GetAllChs(m_listAllCh);
	m_pGridCtrlChs->ShowDatas(&m_listAllCh);

	CreateCtrlLines();

	return XCREATE_SUCC;
}

void CXScdDrawCtrl_SclSvInAll::CreateCtrlLines()
{
	POS pos = m_listAllCh.GetHeadPosition();
	CSclChSmvIn *pSclCh = NULL;

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvIn *)m_listAllCh.GetNext(pos);

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

