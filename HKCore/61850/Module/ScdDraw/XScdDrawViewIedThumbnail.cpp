//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedThumbnail.cpp  CXScdDrawViewIedThumbnail


#include "stdafx.h"
#include "XScdDrawViewIedThumbnail.h"
#include "ThumbLayoutTool.h"

CXScdDrawViewIedThumbnail::CXScdDrawViewIedThumbnail()
{
	m_pIedList_MergIntel = NULL;
	m_pIedList_ProtMeas = NULL;
}

CXScdDrawViewIedThumbnail::~CXScdDrawViewIedThumbnail()
{
}

void CXScdDrawViewIedThumbnail::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawViewBase::Draw(pDC,fZoomRatio,ptOffset, dwDrawFlag);
}

void CXScdDrawViewIedThumbnail::Pick(const CPoint &point, CExBaseList &oList)
{
	CXScdDrawViewBase::Pick(point, oList);

	m_oScdDrawLines.Pick(point, oList);
}

CXDrawElement* CXScdDrawViewIedThumbnail::XCreateChildElement(UINT nClassID)
{
	if (SCLIECCLASSID_IED == nClassID)
	{
		return new CXScdDrawIedThumbnail();
	}

	return NULL;
}

DWORD CXScdDrawViewIedThumbnail::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == XSCDDRAW_IED_THUMBNAIL);

	//CreateElements
	InitXScdDrawViewIedThumb((CXScdDrawIedThumbnail*)pData, pParentWnd);

	////CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	////调整位置
	//Layout(CPoint(0, 0));

	return XCREATE_SUCC;
}


CSize CXScdDrawViewIedThumbnail::CalLayout(CSize &szDraw)
{
	CSize szEntire(0,0);//计算所有的IED的Size
	CSize szIed(0,0);
	POS pos=GetHeadPosition(); 
	CXScdDrawIedThumbnail *pIedThumbnail=NULL;
	CSclIed *pTempIed=NULL;

	while (pos!=NULL)
	{
		pIedThumbnail=(CXScdDrawIedThumbnail*)GetNext(pos);
		szIed=pIedThumbnail->CalLayout(szIed);
	}

	szEntire.cy=max(szEntire.cy,szIed.cy);
	szEntire.cx+=szIed.cx;

	//计算总的Size
	szDraw = Layout(CPoint(0, 0));

	m_pMainIedThumb->FilterAllLines(m_oScdDrawLines);

	return szDraw;
}

void CXScdDrawViewIedThumbnail::LayoutLines()
{
	POS pos = m_oScdDrawLines.GetHeadPosition(); 
	CXScdDrawLineBase *pLine = NULL;

	while (pos!=NULL)
	{
		pLine = (CXScdDrawLineBase *)m_oScdDrawLines.GetNext(pos);
		pLine->InitLinePos();
	}
}


CSize CXScdDrawViewIedThumbnail::Layout(CPoint &ptTopLeft)
{
	CSize szMergIntel, szProcMeas;
	m_pIedList_ProtMeas->GetSize(szProcMeas,GETSIZE_MODE_XADD_YMAX);
	m_pIedList_MergIntel->GetSize(szMergIntel,GETSIZE_MODE_XADD_YMAX);

	ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN;
	ptTopLeft.y=XSCDDRAW_ELEMENT_MARGIN;

	//保护、测控
	szProcMeas=m_pIedList_ProtMeas->Layout(ptTopLeft);

	//合并单元、智能终端
	ptTopLeft.y += szProcMeas.cy + XSCDDRAW_THUMBNAIL_GAP_IED_Y;
	szMergIntel = m_pIedList_MergIntel->Layout(ptTopLeft);
	m_nHeight = ptTopLeft.y;

	long nOffset = szMergIntel.cx - szProcMeas.cx;

	if (nOffset > 0)
	{
		ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN + (nOffset) / 2;
		ptTopLeft.y=XSCDDRAW_ELEMENT_MARGIN;
		m_pIedList_ProtMeas->Layout(ptTopLeft);
	}
	else
	{
		ptTopLeft.y = XSCDDRAW_ELEMENT_MARGIN + szProcMeas.cy + XSCDDRAW_THUMBNAIL_GAP_IED_Y;
		ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN - nOffset / 2;
		m_pIedList_MergIntel->Layout(ptTopLeft);
	}

	m_nWidth  = max(szProcMeas.cx, szMergIntel.cx) + XSCDDRAW_THUMBNAIL_GAP_IED_X*2;
	m_nHeight +=szMergIntel.cy + XSCDDRAW_ELEMENT_MARGIN;

	LayoutLines();

	return CSize(m_nWidth, m_nHeight);
}



void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb(CXScdDrawIedThumbnail *pIedThumb, CWnd *pParentWnd)
{
	CXScdDrawCtrl_ThumbBase::g_bNeedCreateCtrlLines = FALSE;

	m_pMainIedThumb = new CXScdDrawIedThumbnail();
	pIedThumb->CopyOwn(m_pMainIedThumb);
	AddNewChild(m_pMainIedThumb);
	m_pMainIedThumb->XCreateCtrl(pParentWnd);
	m_pActiveElement = m_pMainIedThumb;

	POS pos=pIedThumb->GetHeadPosition();
	CSclIed *pIed=NULL;
	CXScdDrawCtrl_ThumbBase *pCtrlThumb=NULL;

	m_pIedList_ProtMeas=new CXScdIedGroupThumb();
	m_pIedList_MergIntel=new CXScdIedGroupThumb();
	m_listIedGroup.AddTail(m_pIedList_ProtMeas);
	m_listIedGroup.AddTail(m_pIedList_MergIntel);
	m_oScdDrawLines.DeleteAll();
	UINT nClassID = 0;

	//遍历当前IED的全部CXScdDrawCtrl_ThumbBase对象，创建于此对象相关的IedThumb
	while (pos!=NULL)
	{
		pCtrlThumb = (CXScdDrawCtrl_ThumbBase*)pIedThumb->GetNext(pos);
		nClassID = pCtrlThumb->GetClassID();

		switch(nClassID)
		{
		case XSCDDRAW_CTRL_THUMB_GSIN:
			InitXScdDrawViewIedThumb_GsIn((CXScdDrawCtrl_ThumbGsIn*)pCtrlThumb, pParentWnd);
			break;

		case XSCDDRAW_CTRL_THUMB_GSOUT:
			InitXScdDrawViewIedThumb_GsOut((CXScdDrawCtrl_ThumbGsOut*)pCtrlThumb, pParentWnd);
			break;

		case XSCDDRAW_CTRL_THUMB_SVIN:
			InitXScdDrawViewIedThumb_SvIn((CXScdDrawCtrl_ThumbSvIn*)pCtrlThumb, pParentWnd);
			break;

		case XSCDDRAW_CTRL_THUMB_SVOUT:
			InitXScdDrawViewIedThumb_SvOut((CXScdDrawCtrl_ThumbSvOut*)pCtrlThumb, pParentWnd);
			break;

		}
	}

	if (m_pMainIedThumb->IsIed_Prot_Meas())
	{
		long nCount = m_pIedList_ProtMeas->GetCount() / 2;
		POS pos = m_pIedList_ProtMeas->FindIndex(nCount);

		if (pos == NULL)
		{
			m_pIedList_ProtMeas->AddTail(m_pMainIedThumb);
		}
		else
		{
			m_pIedList_ProtMeas->InsertBefore(pos, m_pMainIedThumb);
		}
	}
	else
	{
		long nCount = m_pIedList_MergIntel->GetCount() / 2;
		POS pos = m_pIedList_MergIntel->FindIndex(nCount);

		if (pos == NULL)
		{
			m_pIedList_MergIntel->AddTail(m_pMainIedThumb);
		}
		else
		{
			m_pIedList_MergIntel->InsertBefore(pos, m_pMainIedThumb);
		}
	}


	CXScdDrawCtrl_ThumbBase::g_bNeedCreateCtrlLines = TRUE;

	m_pMainIedThumb->GetAllLines(m_oScdDrawLines);

	//调整连接线
	//InitLinesBeginElement();
}

CXScdDrawIedThumbnail* CXScdDrawViewIedThumbnail::FindBySclIed(CSclIed *pIed)
{
	CXScdDrawIedThumbnail *p = NULL;
	CXScdDrawIedThumbnail *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXScdDrawIedThumbnail *)GetNext(pos);

		if (p->GetRefIed() == pIed)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb_In(CExBaseList *pCtrlIn, CExBaseList *pDestCtrl, CWnd *pParentWnd)
{
	POS pos = pCtrlIn->GetHeadPosition();
	CXScdDrawLineBase *pLine = NULL;
	CXScdDrawIedThumbnail *pIedThumb = NULL;
	CXScdDrawIedThumbnail *pNewIedThumb = NULL;
	CXScdDrawLineBase *pNewLine = NULL;

	while (pos != NULL)
	{
		pLine = (CXScdDrawLineBase *)pCtrlIn->GetNext(pos);
		pIedThumb = (CXScdDrawIedThumbnail*)pLine->m_pBeginElement->GetParent();
		pNewIedThumb = FindBySclIed(pIedThumb->GetRefIed());

		if (pNewIedThumb == NULL)
		{
			pNewIedThumb = new CXScdDrawIedThumbnail();
			pIedThumb->CopyOwn(pNewIedThumb);
			AddNewChild(pNewIedThumb);

			if (pNewIedThumb->IsIed_Prot_Meas())
			{
				m_pIedList_ProtMeas->AddTail(pNewIedThumb);
			}
			else
			{
				m_pIedList_MergIntel->AddTail(pNewIedThumb);
			}

			pNewIedThumb->XCreateCtrl(pNewIedThumb->GetRefIed(),pParentWnd);
		}

		pNewLine = (CXScdDrawLineBase*)pLine->Clone();
		pNewLine->m_pEndElement = (CXDrawElement*)pDestCtrl;
		pNewLine->m_pBeginElement = (CXDrawElement*)pNewIedThumb->FindByClassID(pLine->m_pBeginElement->GetClassID());
		pDestCtrl->AddNewChild(pNewLine);
		pNewLine->m_crForeColor = pLine->m_crForeColor;
	}
}

void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb_Out(CExBaseList *pCtrlOut, CExBaseList *pDestCtrl, CWnd *pParentWnd)
{
	POS pos = pCtrlOut->GetHeadPosition();
	CXScdDrawLineBase *pLine = NULL;
	CXScdDrawIedThumbnail *pIedThumb = NULL;
	CXScdDrawIedThumbnail *pNewIedThumb = NULL;
	CXScdDrawLineBase *pNewLine = NULL;

	while (pos != NULL)
	{
		pLine = (CXScdDrawLineBase *)pCtrlOut->GetNext(pos);
		pIedThumb = (CXScdDrawIedThumbnail*)pLine->m_pEndElement->GetParent();
		pNewIedThumb = FindBySclIed(pIedThumb->GetRefIed());

		if (pNewIedThumb == NULL)
		{
			pNewIedThumb = new CXScdDrawIedThumbnail();
			pIedThumb->CopyOwn(pNewIedThumb);
			AddNewChild(pNewIedThumb);

			if (pNewIedThumb->IsIed_Prot_Meas())
			{
				m_pIedList_ProtMeas->AddTail(pNewIedThumb);
			}
			else
			{
				m_pIedList_MergIntel->AddTail(pNewIedThumb);
			}

			pNewIedThumb->XCreateCtrl(pNewIedThumb->GetRefIed(),pParentWnd);
		}

		pNewLine = (CXScdDrawLineBase*)pLine->Clone();
		pNewLine->m_pBeginElement = (CXDrawElement*)pDestCtrl;
		pNewLine->m_pEndElement = (CXDrawElement*)pNewIedThumb->FindByClassID(pLine->m_pEndElement->GetClassID());
		pDestCtrl->AddNewChild(pNewLine);
		pNewLine->m_crForeColor = pLine->m_crForeColor;
	}
}

void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb_GsIn(CXScdDrawCtrl_ThumbGsIn *pGsIn, CWnd *pParentWnd)
{
	CXScdDrawCtrl_ThumbGsIn *pNew = m_pMainIedThumb->GetCtrl_ThumbGsIn();

	InitXScdDrawViewIedThumb_In(pGsIn, pNew, pParentWnd);
}

void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb_GsOut(CXScdDrawCtrl_ThumbGsOut *pGsOut, CWnd *pParentWnd)
{
	CXScdDrawCtrl_ThumbGsOut *pNew = m_pMainIedThumb->GetCtrl_ThumbGsOut();

	InitXScdDrawViewIedThumb_Out(pGsOut, pNew, pParentWnd);
}

void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb_SvIn(CXScdDrawCtrl_ThumbSvIn *pSvIn, CWnd *pParentWnd)
{
	CXScdDrawCtrl_ThumbSvIn *pNew = m_pMainIedThumb->GetCtrl_ThumbSvIn();

	InitXScdDrawViewIedThumb_In(pSvIn, pNew, pParentWnd);
}

void CXScdDrawViewIedThumbnail::InitXScdDrawViewIedThumb_SvOut(CXScdDrawCtrl_ThumbSvOut *pSvOut, CWnd *pParentWnd)
{
	CXScdDrawCtrl_ThumbSvOut *pNew = m_pMainIedThumb->GetCtrl_ThumbSvOut();

	InitXScdDrawViewIedThumb_Out(pSvOut, pNew, pParentWnd);
}

