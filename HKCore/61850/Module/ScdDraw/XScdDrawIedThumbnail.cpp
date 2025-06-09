//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawIedThumbnail.h"

CXScdDrawIedThumbnail::CXScdDrawIedThumbnail()
{
	//初始化属性
	m_pRefIed=NULL;
	m_b_ProtMeas_MuCtrl=0;

	//初始化成员变量
}

CXScdDrawIedThumbnail::~CXScdDrawIedThumbnail()
{
}


BOOL CXScdDrawIedThumbnail::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXScdDrawIedThumbnail *p = (CXScdDrawIedThumbnail*)pDest;

	CXScdDrawIedBase::CopyOwn(pDest);

	p->m_pRefIed = m_pRefIed;
	p->m_b_ProtMeas_MuCtrl = m_b_ProtMeas_MuCtrl;

	return TRUE;
}

CBaseObject* CXScdDrawIedThumbnail::Clone()
{
	CXScdDrawIedThumbnail *p = new CXScdDrawIedThumbnail();
	Copy(p);
	return p;
}

void CXScdDrawIedThumbnail::Pick(const CPoint &point, CExBaseList &oList)
{
	if (IsPointInRect(point))
	{
		oList.AddTail(this);
	}
}


void CXScdDrawIedThumbnail::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CFont *pFont;
	CBrush brush1;
	pFont=pDC->SelectObject(g_pGlobalFont12);
	UINT nOldTextColor = pDC->SetTextColor(RGB(0,0,0));
	UINT nOldBkColor = pDC->SetBkColor(RGB(150,200,156));

	if (IsPicked())
	{
		brush1.CreateSolidBrush(RGB(0,255,0));
	}
	else
	{
		brush1.CreateSolidBrush(RGB(192,192,192));
	}

	CBrush *pOldBrush1 = pDC->SelectObject(&brush1);

	CPoint ptTopLeft = m_ptTopLeft;
	CRect rc_Ied(ptTopLeft.x, ptTopLeft.y, (ptTopLeft.x+m_nWidth), ptTopLeft.y+m_nHeight);
	rc_Ied.DeflateRect(1,1,1,1);
	CPen pen1(PS_SOLID, 1, RGB(0, 0, 255));//重新定义IED正文的画笔和画刷
	CPen *pOldPen1 = pDC->SelectObject(&pen1);
	pDC->Rectangle(rc_Ied);

	CPoint ptTopLeft_ID;
	ptTopLeft_ID.x=ptTopLeft.x;
	ptTopLeft_ID.y = ptTopLeft.y + XSCDDRAW_THUMBNAIL_IED_HEIGHT_TYPE - 1;

	if (m_b_ProtMeas_MuCtrl==IEDTHUMBNAILTYPE_MUCTRL)
	{
		ptTopLeft.y += m_nHeight - XSCDDRAW_THUMBNAIL_IED_HEIGHT_TYPE;	
		ptTopLeft_ID.y= ptTopLeft.y - XSCDDRAW_THUMBNAIL_IED_HEIGHT_ID + 1;
	}

	CRect rc_IedName(ptTopLeft.x, ptTopLeft.y, ptTopLeft.x+m_nWidth, ptTopLeft.y + XSCDDRAW_THUMBNAIL_IED_HEIGHT_TYPE);//定义IED的名字和ID的背景区域
	CRect rc_IedID(ptTopLeft_ID.x,ptTopLeft_ID.y, (ptTopLeft_ID.x+XSCDDRAW_THUMBNAIL_IED_ID_WIDTH), (ptTopLeft_ID.y+XSCDDRAW_THUMBNAIL_IED_HEIGHT_ID));
	CRect rc_IP = rc_IedID;

	rc_IP.left  = rc_IedID.right;
	rc_IP.right = ptTopLeft_ID.x + m_nWidth;

	rc_IedName.DeflateRect(1,1,1,1);
	rc_IedID.DeflateRect(1,1,1,1);
	rc_IP.DeflateRect(1,1,1,1);

	pDC->Rectangle(rc_IedName);
	pDC->Rectangle(rc_IedID);
	pDC->Rectangle(rc_IP);

	rc_IedName.DeflateRect(1, 0, 1, 0);
	rc_IedID.DeflateRect(1, 0, 1, 0);
	rc_IP.DeflateRect(1, 0, 1, 0);

#ifdef _use_font_g_lfGlobalFont11
	CmDrawTextRect(pDC, m_strName, RGB(0, 0, 0), rc_IedName, RGB(192,192,192), g_lfGlobalFont11, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
	CmDrawTextRect(pDC, m_strID,   RGB(0, 0, 0), rc_IedID, RGB(192,192,192),   g_lfGlobalFont11, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
	CmDrawTextRect(pDC, m_pRefIed->m_strIP,   RGB(0, 0, 0), rc_IP, RGB(192,192,192),   g_lfGlobalFont11, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
#else
	CmDrawTextRect(pDC, m_strName, RGB(0, 0, 0), rc_IedName, RGB(192,192,192), g_lfGlobalFont12, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
	CmDrawTextRect(pDC, m_strID,   RGB(0, 0, 0), rc_IedID, RGB(192,192,192),   g_lfGlobalFont12, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
	CmDrawTextRect(pDC, m_pRefIed->m_strIP,   RGB(0, 0, 0), rc_IP, RGB(192,192,192),   g_lfGlobalFont12, TRANSPARENT, DT_VCENTER|DT_WORDBREAK|DT_CENTER, 0);
#endif

	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);

	pDC->SelectObject(pOldPen1);
	pDC->SelectObject(pOldBrush1);
	pDC->SetTextColor(nOldTextColor);
	pDC->SetBkColor(nOldBkColor);
}

void CXScdDrawIedThumbnail::XCreateCtrl(CSclIed *pIedData, CWnd *pParentWnd)
{
	CSclIed *pTempIed=pIedData;
	POS pos=pTempIed->GetHeadPosition();
	CExBaseObject *pIedCtrl=NULL;
	UINT nClassID = 0;

	while (pos!=NULL)
	{
		pIedCtrl=pTempIed->GetNext(pos);
		nClassID = pIedCtrl->GetClassID();
	
		if (nClassID==SCLIECCLASSID_CTRLS_GS_IN)
		{
			CSclCtrlsGsIn *pSclCtrlsGsIn=(CSclCtrlsGsIn*)pIedCtrl;
			CXScdDrawCtrl_ThumbGsIn *pNew=new CXScdDrawCtrl_ThumbGsIn();
			AddNewChild(pNew);
			pNew->XCreateElement(pSclCtrlsGsIn,pParentWnd);
		}
		else if(nClassID==SCLIECCLASSID_CTRLS_GS_OUT)
		{
			CSclCtrlsGsOut *pSclCtrlsGsOut=(CSclCtrlsGsOut*)pIedCtrl;
			CXScdDrawCtrl_ThumbGsOut *pNew=new CXScdDrawCtrl_ThumbGsOut();
			AddNewChild(pNew);
			pNew->XCreateElement(pSclCtrlsGsOut,pParentWnd);
		}
		else if(nClassID==SCLIECCLASSID_CTRLS_SMV_IN)
		{
			CSclCtrlsSmvIn *pSclCtrlsSmvIn=(CSclCtrlsSmvIn*)pIedCtrl;
			CXScdDrawCtrl_ThumbSvIn *pNew=new CXScdDrawCtrl_ThumbSvIn();
			AddNewChild(pNew);
			pNew->XCreateElement(pSclCtrlsSmvIn,pParentWnd);
		}
		else if(nClassID==SCLIECCLASSID_CTRLS_SMV_OUT)
		{
			CSclCtrlsSmvOut *pSclCtrlsSmvOut=(CSclCtrlsSmvOut*)pIedCtrl;
			CXScdDrawCtrl_ThumbSvOut *pNew=new CXScdDrawCtrl_ThumbSvOut();
			AddNewChild(pNew);
			pNew->XCreateElement(pSclCtrlsSmvOut,pParentWnd);
		}
	}
}

void CXScdDrawIedThumbnail::CreateCtrlLines()
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrl_ThumbBase *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CXScdDrawCtrl_ThumbBase *)GetNext(pos);
		pCtrl->CreateCtrlLines();
	}
}

void CXScdDrawIedThumbnail::XCreateCtrl(CWnd *pParentWnd)
{
	XCreateCtrl(m_pRefIed, pParentWnd);
}

void CXScdDrawIedThumbnail::GetAllLines(CXDrawElements &oScdLines)
{
	CXScdDrawCtrl_ThumbBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXScdDrawCtrl_ThumbBase *)GetNext(pos);
		p->GetAllLines(oScdLines);
	}
}



CSize CXScdDrawIedThumbnail::CalLayout(CSize &szDraw)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;
	CSize szElement, szIed(0,200);
	long nCount = GetCount();

	while (pos != NULL)
	{
		p = (CXDrawElement *)GetNext(pos);
		szElement = p->CalLayout(szElement);
		szIed.cx += szElement.cx;	
	}

	if (nCount > 0)
	{
		szIed.cx += (nCount + 1) * XSCDDRAW_ELEMENT_MARGIN;
	}

	//标题：
	szIed.cx = max(XSCDDRAW_THUMBNAIL_IED_WIDTH , szIed.cx);
	szIed.cy = XSCDDRAW_THUMBNAIL_IED_HEIGHT;
	szIed.cy += XSCDDRAW_ELEMENT_MARGIN;

	m_nHeight = szIed.cy;
	m_nWidth  = szIed.cx;

	szDraw = szIed;
	return szDraw;
}


CSize CXScdDrawIedThumbnail::Layout(CPoint &ptTopLeft)
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrlBase = NULL;
	CPoint pt;
	CSize szCtrl;
	m_ptTopLeft = ptTopLeft;

	pt.x = ptTopLeft.x+XSCDDRAW_ELEMENT_MARGIN;

	//保护、测控
	if(m_b_ProtMeas_MuCtrl == IEDTHUMBNAILTYPE_MUCTRL)
	{
		pt.y = ptTopLeft.y + XSCDDRAW_ELEMENT_MARGIN;
	}
	else
	{//合并单元、智能终端
		pt.y = ptTopLeft.y + XSCDDRAW_THUMBNAIL_IED_HEIGHT_TYPE+XSCDDRAW_THUMBNAIL_IED_HEIGHT_ID;
	}

	//CTRLS
	while (pos != NULL)
	{
		pCtrlBase = (CXScdDrawCtrlBase *)GetNext(pos);
		szCtrl = pCtrlBase->Layout(pt);
		pt.x += szCtrl.cx + XSCDDRAW_ELEMENT_MARGIN;
	}

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}

CXScdDrawCtrl_ThumbSvOut* CXScdDrawIedThumbnail::GetCtrl_ThumbSvOut()
{
	CXScdDrawCtrl_ThumbSvOut *pFind = (CXScdDrawCtrl_ThumbSvOut*)FindByClassID(XSCDDRAW_CTRL_THUMB_SVOUT);
	return pFind;
}

CXScdDrawCtrl_ThumbSvIn* CXScdDrawIedThumbnail::GetCtrl_ThumbSvIn()
{
	CXScdDrawCtrl_ThumbSvIn *pFind = (CXScdDrawCtrl_ThumbSvIn*)FindByClassID(XSCDDRAW_CTRL_THUMB_SVIN);
	return pFind;
}

CXScdDrawCtrl_ThumbGsOut* CXScdDrawIedThumbnail::GetCtrl_ThumbGsOut()
{
	CXScdDrawCtrl_ThumbGsOut *pFind = (CXScdDrawCtrl_ThumbGsOut*)FindByClassID(XSCDDRAW_CTRL_THUMB_GSOUT);
	return pFind;
}

CXScdDrawCtrl_ThumbGsIn* CXScdDrawIedThumbnail::GetCtrl_ThumbGsIn()
{
	CXScdDrawCtrl_ThumbGsIn *pFind = (CXScdDrawCtrl_ThumbGsIn*)FindByClassID(XSCDDRAW_CTRL_THUMB_GSIN);
	return pFind;
}

void CXScdDrawIedThumbnail::CreateCtrlBusLines()
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrl_ThumbBase *pCtrlBase = NULL;

	while (pos != NULL)
	{
		pCtrlBase = (CXScdDrawCtrl_ThumbBase *)GetNext(pos);
		pCtrlBase->CreateCtrlBusLines();
	}
}



void CXScdDrawIedThumbnail::FilterAllLines(CXDrawElements &oScdLines)
{

	POS posLine=oScdLines.GetHeadPosition();
	CXScdDrawLine_Vert *pXScdDrawLine_Vert=NULL;
	CXScdDrawIedThumbnail *pXScdDrawCtrl=NULL;
	CXDrawElement *m_pBeginElement;
	CXDrawElement *m_pEndElement;

	int nHeight1_Left=30;
	int nHeight1_Right=30;
	int nHeight2_Left=50;
	int nHeight2_Right=50;


	while (posLine!=NULL)
	{
		pXScdDrawLine_Vert=(CXScdDrawLine_Vert*)oScdLines.GetNext(posLine);
		if (pXScdDrawLine_Vert->m_ptBegin.y!=pXScdDrawLine_Vert->m_ptEnd.y)
		{
			continue;
		}

		m_pBeginElement=pXScdDrawLine_Vert->m_pBeginElement;
		m_pEndElement=pXScdDrawLine_Vert->m_pEndElement;

		pXScdDrawCtrl=(CXScdDrawIedThumbnail*)m_pBeginElement->GetParent();
		if (pXScdDrawCtrl==(CXScdDrawIedThumbnail*)this)
		{
			if (pXScdDrawLine_Vert->m_ptBegin.x>pXScdDrawLine_Vert->m_ptEnd.x)
		 {
           
			 pXScdDrawLine_Vert->m_ptMainIedTurn.x=pXScdDrawLine_Vert->m_ptBegin.x-nHeight1_Left;
			  pXScdDrawLine_Vert->m_ptMainIedTurn.y=pXScdDrawLine_Vert->m_ptBegin.y+nHeight1_Left;
			 nHeight1_Left-=4;
		 }
			else
		 {
			 pXScdDrawLine_Vert->m_ptMainIedTurn.x=pXScdDrawLine_Vert->m_ptBegin.x+nHeight1_Right;
			   pXScdDrawLine_Vert->m_ptMainIedTurn.y=pXScdDrawLine_Vert->m_ptBegin.y+nHeight1_Right;
			 nHeight1_Right-=4;
		 }
			


		}
		else
		{
			if (pXScdDrawLine_Vert->m_ptBegin.x<pXScdDrawLine_Vert->m_ptEnd.x)
		 {
			 pXScdDrawLine_Vert->m_ptMainIedTurn.x=pXScdDrawLine_Vert->m_ptEnd.x-nHeight2_Left;
			 pXScdDrawLine_Vert->m_ptMainIedTurn.y=pXScdDrawLine_Vert->m_ptEnd.y+nHeight2_Left;

			 nHeight2_Left-=4;
		 }
			else
		 {
			  pXScdDrawLine_Vert->m_ptMainIedTurn.x=pXScdDrawLine_Vert->m_ptEnd.x+nHeight2_Right;
			 pXScdDrawLine_Vert->m_ptMainIedTurn.y=pXScdDrawLine_Vert->m_ptEnd.y+nHeight2_Right;
			 nHeight2_Right-=4;
		 }	

		}
	}
}
