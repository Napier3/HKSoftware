//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawIedSclDetail.h"

CXScdDrawIedSclDetail::CXScdDrawIedSclDetail()
{
	//初始化属性

	//初始化成员变量
	m_strIP="";
	m_strManufacturer="";
}

CXScdDrawIedSclDetail::~CXScdDrawIedSclDetail()
{
}


DWORD CXScdDrawIedSclDetail::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	UINT nClassID = pData->GetClassID();

	if(nClassID == SCLIECCLASSID_IED)
	{
		CSclIed *pIed = (CSclIed*)pData;
		m_pXDrawDataRef = pIed;

		CSclCtrlsGsIn *pCtrslGsIn          = pIed->GetGsIns();
		CSclCtrlsGsOut *pCtrslGsOut      = pIed->GetGsOuts();
		CSclCtrlsSmvIn *pCtrslSmvIn     = pIed->GetSmvIns();
		CSclCtrlsSmvOut *pCtrslSmvOut = pIed->GetSmvOuts();

		XCreateCtrl_GsIn_Scl(pCtrslGsIn, pParentWnd);
		XCreateCtrl_SvIn_Scl(pCtrslSmvIn, pParentWnd);
		XCreateCtrl_GsOut_Scl(pCtrslGsOut, pParentWnd);
		XCreateCtrl_SvOut_Scl(pCtrslSmvOut, pParentWnd);
	}
	else if (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
	{
		CSclIed *pIed = (CSclIed*)pData->GetAncestor(SCLIECCLASSID_IED);
		m_pXDrawDataRef = pIed;
		XCreateCtrl_GsIn_Scl((CSclCtrlsGsIn*)pData, pParentWnd);
	}
	else if (nClassID == SCLIECCLASSID_CTRLS_GS_OUT)
	{
		CSclIed *pIed = (CSclIed*)pData->GetAncestor(SCLIECCLASSID_IED);
		m_pXDrawDataRef = pIed;
		XCreateCtrl_GsOut_Scl((CSclCtrlsGsOut*)pData, pParentWnd);
	}
	else if (nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
	{
		CSclIed *pIed = (CSclIed*)pData->GetAncestor(SCLIECCLASSID_IED);
		m_pXDrawDataRef = pIed;
		XCreateCtrl_SvIn_Scl((CSclCtrlsSmvIn*)pData, pParentWnd);
	}
	else if (nClassID == SCLIECCLASSID_CTRLS_SMV_OUT)
	{
		CSclIed *pIed = (CSclIed*)pData->GetAncestor(SCLIECCLASSID_IED);
		m_pXDrawDataRef = pIed;
		XCreateCtrl_SvOut_Scl((CSclCtrlsSmvOut*)pData, pParentWnd);
	}	
	else
	{
		return XCREATE_FAIL;
	}

	InitAfterCreateElement(pParentWnd);

	return XCREATE_SUCC;
}


CXScdDrawCtrlBase* CXScdDrawIedSclDetail::XCreateCtrl_SvIn_Scl(CSclCtrlsSmvIn *pSclCtrls, CWnd *pParentWnd)
{
	if (pSclCtrls->GetCount() == 0)
	{
		return NULL;
	}

	CXScdDrawCtrl_SclSvInAll *pNew = new CXScdDrawCtrl_SclSvInAll();
	AddNewChild(pNew);
	pNew->XCreateElement(pSclCtrls, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedSclDetail::XCreateCtrl_GsIn_Scl(CSclCtrlsGsIn *pSclCtrls, CWnd *pParentWnd)
{
	if (pSclCtrls->GetCount() == 0)
	{
		return NULL;
	}

	CXScdDrawCtrl_SclGsInAll *pNew = new CXScdDrawCtrl_SclGsInAll();
	AddNewChild(pNew);

	pNew->XCreateElement(pSclCtrls, pParentWnd);

	return pNew;
}

void CXScdDrawIedSclDetail::XCreateCtrl_SvOut_Scl(CSclCtrlsSmvOut *pSclCtrls, CWnd *pParentWnd)
{
	POS pos = pSclCtrls->GetHeadPosition();
	CSclCtrlSmvOut *pSclCtrl = NULL;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlSmvOut *)pSclCtrls->GetNext(pos);
		XCreateCtrl_SvOut_Scl(pSclCtrl, pParentWnd);
	}
}

void CXScdDrawIedSclDetail::XCreateCtrl_GsOut_Scl(CSclCtrlsGsOut *pSclCtrls, CWnd *pParentWnd)
{
	POS pos = pSclCtrls->GetHeadPosition();
	CSclCtrlGsOut *pSclCtrl = NULL;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlGsOut *)pSclCtrls->GetNext(pos);
		XCreateCtrl_GsOut_Scl(pSclCtrl, pParentWnd);
	}
}

CXScdDrawCtrlBase* CXScdDrawIedSclDetail::XCreateCtrl_SvOut_Scl(CSclCtrlSmvOut *pSclCtrl, CWnd *pParentWnd)
{
	CXScdDrawCtrl_SclSvOut *pNew = new CXScdDrawCtrl_SclSvOut();
	AddNewChild(pNew);
	pNew->XCreateElement(pSclCtrl, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedSclDetail::XCreateCtrl_GsOut_Scl(CSclCtrlGsOut *pSclCtrl, CWnd *pParentWnd)
{
	CXScdDrawCtrl_SclGsOut *pNew = new CXScdDrawCtrl_SclGsOut();
	AddNewChild(pNew);
	pNew->XCreateElement(pSclCtrl, pParentWnd);

	return pNew;
}
// 
// void CXScdDrawIedSclDetail::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {
// 	//绘制边框
// 
// 	CFont font;//定义IED名字和ID的字体样式
// 	CFont *pFont;
// 	font.CreateFont(12,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"宋体");
// 	pFont=pDC->SelectObject(&font);
// 	pDC->SetTextColor(RGB(0,0,0));
// 	pDC->SetBkColor(RGB(150,200,156));
// 
// 	CRect rc_IedName(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);//定义IED的名字和ID的背景区域
// 	CRect rc_IedID(m_ptTopLeft.x+m_nWidth/3-2,m_ptTopLeft.y, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+30);
// 	rc_IedName.DeflateRect(1,1,1,1);
// 	rc_IedID.DeflateRect(1,1,1,1);
// 
// 
// 	CPen pen(PS_SOLID, 1, RGB(0, 0, 255));//绘制IED的 名字和ID 的背景色
// 	CPen *pOldPen = pDC->SelectObject(&pen);
// 	CBrush brush;
// 	brush.CreateSolidBrush(RGB(150,200,156));
// 	CBrush *pOldBrush = pDC->SelectObject(&brush);
// 	pDC->Rectangle(rc_IedName);
// 	pDC->Rectangle(rc_IedID);
// 
// 
// 	if (strlen(m_strName)<m_nWidth/3)//重新定义 输入IED的名字和字体 的区域，比背景色稍微偏下，区别换行
// 	{
// 		CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
// 		pDC->DrawText(m_strName,strlen(m_strName),rc_IedName_Text,DT_CENTER);//输入IED的名字和字体
// 	}
// 	else
// 	{
// 		CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
// 		pDC->DrawText(m_strName,strlen(m_strName),rc_IedName_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
// 	}
// 
// 
// 	if(strlen(m_strID)<m_nWidth*2/3)
// 	{
// 		CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
// 		pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_CENTER);
// 	}
// 	else
// 	{
// 		CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
// 		pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
// 	}
// 
// 	pDC->SelectObject(pOldPen);
// 	pDC->SelectObject(pOldBrush);
// 	font.DeleteObject();
// 
// 	CRect rc_Ied(m_ptTopLeft.x, m_ptTopLeft.y+28, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+m_nHeight);
// 	rc_Ied.DeflateRect(1,1,1,1);
// 	CPen pen1(PS_SOLID, 1, RGB(0, 0, 255));//重新定义IED正文的画笔和画刷
// 	CPen *pOldPen1 = pDC->SelectObject(&pen1);
// 	CBrush brush1;
// 	brush1.CreateSolidBrush(RGB(192,192,192));
// 	CBrush *pOldBrush1 = pDC->SelectObject(&brush1);
// 	pDC->Rectangle(rc_Ied);
// 	pDC->SelectObject(pOldPen1);
// 	pDC->SelectObject(pOldBrush1);
// 
// 	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// }

void CXScdDrawIedSclDetail::DrawLines(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
}


CSize CXScdDrawIedSclDetail::CalLayout(CSize &szDraw)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;
	CSize szElement, szIed(0, 0);

	while (pos != NULL)
	{
		p = (CXDrawElement *)GetNext(pos);
		szElement = p->CalLayout(szElement);
		szIed.cx = max(szIed.cx, szElement.cx);
		szIed.cy += szElement.cy;
	}

	if (szIed.cx == 0)
	{
		szIed.cx = XSCDDRAW_IED_WIDTH_MIN;
	}

	if (szIed.cy == 0)
	{
		szIed.cy = XSCDDRAW_IED_TITLE_HEIGHT;
	}

	//标题：
	szIed.cx += XSCDDRAW_IED_BORDER_GAP*2;
	szIed.cy += XSCDDRAW_IED_TITLE_HEIGHT;

	m_nWidth = szIed.cx;
	m_nHeight = szIed.cy;

	szDraw = szIed;
	return szDraw;
}

CSize CXScdDrawIedSclDetail::Layout(CPoint &ptTopLeft)
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrlBase = NULL;
	CPoint pt,ptMainIed;
	CSize szCtrl;
	m_ptTopLeft = ptTopLeft;
	pt.x = ptTopLeft.x + XSCDDRAW_IED_BORDER_GAP;
	pt.y = ptTopLeft.y + XSCDDRAW_IED_BORDER_GAP + XSCDDRAW_IED_TITLE_HEIGHT;
	m_nHeight = XSCDDRAW_IED_TITLE_HEIGHT + XSCDDRAW_IED_BORDER_GAP;
	m_nWidth = 0;
	ptMainIed=pt;

	while (pos != NULL)
	{
		pCtrlBase = (CXScdDrawCtrlBase *)GetNext(pos);
		szCtrl = pCtrlBase->Layout(pt);
		pt.y += szCtrl.cy + XSCDDRAW_CTRL_GAP_UNMAINIED;
		m_nHeight += szCtrl.cy + XSCDDRAW_CTRL_GAP_UNMAINIED;
		m_nWidth = max(m_nWidth, szCtrl.cx);
	}

	if (m_nWidth == 0)
	{
		m_nWidth = XSCDDRAW_IED_WIDTH_MIN;
	}

	if (m_nHeight == 0)
	{
		m_nHeight = XSCDDRAW_IED_TITLE_HEIGHT;
	}

	m_nWidth  += XSCDDRAW_IED_BORDER_GAP * 2;
// 	m_nHeight =  pt.y + XSCDDRAW_IED_BORDER_GAP;

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}

