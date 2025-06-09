//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_ThumbBase.cpp  XScdDrawCtrl_ThumbBase


#include "stdafx.h"
#include "XScdDrawCtrl_ThumbBase.h"
#include "XScdDrawViewStationThumbnail.h"

BOOL CXScdDrawCtrl_ThumbBase::g_bNeedCreateCtrlLines = TRUE;

CXScdDrawCtrl_ThumbBase::CXScdDrawCtrl_ThumbBase()
{
	m_pLineCtrlBus = NULL;
}

CXScdDrawCtrl_ThumbBase::~CXScdDrawCtrl_ThumbBase()
{
	RemoveAll();
}


BOOL CXScdDrawCtrl_ThumbBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXScdDrawCtrl_ThumbBase *p = (CXScdDrawCtrl_ThumbBase*)pDest;

	CXDrawElements::CopyOwn(pDest);

	p->m_strCtrlText = m_strCtrlText;

	return TRUE;
}

CBaseObject* CXScdDrawCtrl_ThumbBase::Clone()
{
	CXScdDrawCtrl_ThumbBase *p = new CXScdDrawCtrl_ThumbBase();
	Copy(p);
	return p;
}

void CXScdDrawCtrl_ThumbBase::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CFont *pFont;
	pFont=pDC->SelectObject(g_pGlobalFont12);
	pDC->SetTextColor(RGB(0,0,0));


	CRect rc(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x + m_nWidth, m_ptTopLeft.y + m_nHeight);
	pDC->Rectangle(rc);

#ifdef _use_font_g_lfGlobalFont11
	CmDrawTextRect(pDC, m_strName, RGB(0, 0, 0), rc, RGB(192,192,192),   g_lfGlobalFont11, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
#else
	CmDrawTextRect(pDC, m_strName, RGB(0, 0, 0), rc, RGB(192,192,192),   g_lfGlobalFont12, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
#endif
	pDC->SelectObject(pFont);

	if (m_pLineCtrlBus != NULL)
	{
		m_pLineCtrlBus->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
}


DWORD CXScdDrawCtrl_ThumbBase::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	m_pXDrawDataRef = pData;

	if (g_bNeedCreateCtrlLines)
	{
		CreateCtrlLines();
	}

	CSize sz;
	CalLayout(sz);

	return XCREATE_SUCC;
}

CSize CXScdDrawCtrl_ThumbBase::CalLayout(CSize &szDraw)
{
	m_nWidth = XSCDDRAW_THUMBNAIL_CTRL_WIDTH;
	m_nHeight = XSCDDRAW_THUMBNAIL_IED_HEIGHT_CTRLS;

	CSize sz(m_nWidth, m_nHeight);

	return sz;
}

CSize CXScdDrawCtrl_ThumbBase::Layout(CPoint &ptTopLeft)
{
	m_ptTopLeft = ptTopLeft;

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}

void CXScdDrawCtrl_ThumbBase::CreateCtrlBusLines()
{
	POS pos = GetHeadPosition();
	CXScdDrawLineBase *pLine = NULL;

	while (pos != NULL)
	{
		pLine = (CXScdDrawLineBase *)GetNext(pos);
		m_pLineCtrlBus->AddTail(pLine);
		pLine->m_crForeColor = m_pLineCtrlBus->m_crForeColor;
	}
}

CXScdDrawLineBase* CXScdDrawCtrl_ThumbBase::FindLineByBeginRef(CExBaseObject *pBeginRef)
{
	POS pos = GetHeadPosition();
	CXScdDrawLineBase *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXScdDrawLineBase *)GetNext(pos);

		if (p->m_pBeginObj == pBeginRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CXScdDrawCtrl_ThumbBase::GetAllLines(CXDrawElements &oScdLines)
{
	oScdLines.Append(this);
}

CXScdDrawLine_Bus* CXScdDrawCtrl_ThumbBase::GetSvBus()
{
	CXScdDrawViewStationThumbnail *pView = (CXScdDrawViewStationThumbnail*)GetAncestor(XSCDDRAW_VIEW_THUMB);

	if (pView == NULL)
	{
		return NULL;
	}

	return pView->m_pLineSvBus;
}

CXScdDrawLine_Bus* CXScdDrawCtrl_ThumbBase::GetGooseBus()
{
	CXScdDrawViewStationThumbnail *pView = (CXScdDrawViewStationThumbnail*)GetAncestor(XSCDDRAW_VIEW_THUMB);

	if (pView == NULL)
	{
		return NULL;
	}

	return pView->m_pLineGooseBus;
}

