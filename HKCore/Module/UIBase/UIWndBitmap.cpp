//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndBitmap.cpp  CUIWndBitmap


#include "stdafx.h"
#include "UIWndBitmap.h"
#include "..\System\TickCount32.h"

CUIWndBitmap::CUIWndBitmap()
{
	//初始化属性

	//初始化成员变量
}

CUIWndBitmap::~CUIWndBitmap()
{
	
}

long CUIWndBitmap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNormalBmpFileKey, oNode, m_strNormalBmpFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDisablelBmpFileKey, oNode, m_strDisablelBmpFile);
	xml_GetAttibuteValue(pXmlKeys->m_strClickBmpFileKey, oNode, m_strClickBmpFile);
	xml_GetAttibuteValue(pXmlKeys->m_strActiveBmpFileKey, oNode, m_strActiveBmpFile);
	return 0;
}

long CUIWndBitmap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNormalBmpFileKey, oElement, m_strNormalBmpFile);
	xml_SetAttributeValue(pXmlKeys->m_strDisablelBmpFileKey, oElement, m_strDisablelBmpFile);
	xml_SetAttributeValue(pXmlKeys->m_strClickBmpFileKey, oElement, m_strClickBmpFile);
	xml_SetAttributeValue(pXmlKeys->m_strActiveBmpFileKey, oElement, m_strActiveBmpFile);
	
	return 0;
}

long CUIWndBitmap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strNormalBmpFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDisablelBmpFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strClickBmpFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strActiveBmpFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strNormalBmpFile);
		BinarySerializeRead(oBinaryBuffer, m_strDisablelBmpFile);
		BinarySerializeRead(oBinaryBuffer, m_strClickBmpFile);
		BinarySerializeRead(oBinaryBuffer, m_strActiveBmpFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strNormalBmpFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDisablelBmpFile);
		BinarySerializeWrite(oBinaryBuffer, m_strClickBmpFile);
		BinarySerializeWrite(oBinaryBuffer, m_strActiveBmpFile);
	}
	return 0;
}

void CUIWndBitmap::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndBitmap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndBitmap *p = (CUIWndBitmap*)pObj;

	if(m_strNormalBmpFile != p->m_strNormalBmpFile)
	{
		return FALSE;
	}

	if(m_strDisablelBmpFile != p->m_strDisablelBmpFile)
	{
		return FALSE;
	}

	if(m_strClickBmpFile != p->m_strClickBmpFile)
	{
		return FALSE;
	}

	if(m_strActiveBmpFile != p->m_strActiveBmpFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndBitmap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndBitmap *p = (CUIWndBitmap*)pDest;

	p->m_strNormalBmpFile = m_strNormalBmpFile;
	p->m_strDisablelBmpFile = m_strDisablelBmpFile;
	p->m_strClickBmpFile = m_strClickBmpFile;
	p->m_strActiveBmpFile = m_strActiveBmpFile;
	return TRUE;
}

CBaseObject* CUIWndBitmap::Clone()
{
	CUIWndBitmap *p = new CUIWndBitmap();
	Copy(p);
	return p;
}

CExBaseObject* CUIWndBitmap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndBitmap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CUIWndBitmap, CStatic)
	//{{AFX_MSG_MAP(CUIWndBitmap)
	ON_WM_PAINT()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, OnDoubleclicked)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CUIWndBitmap::UICreate(CWnd *pParent)
{
	if (m_pWindow != NULL)
	{
		LOG_WriteLawString("recreate BitMap");
	}

	CRect rect = GetWndPosition();
	BOOL bState = FALSE;	

	bState = Create(NULL,WS_CHILD|WS_VISIBLE|SS_NOTIFY,
		rect,
		pParent,
		GenerateWindowID());

	if (!bState)
	{
		return FALSE;
	}

	CDC *pDC = GetDC();
	//m_oUIMemDC->Create(pDC, CRect(0, 0, m_nWidth, m_nHeight));
	ReleaseDC(pDC);
	LoadUIBitmap();
	ShowWindow(SW_SHOW);
	m_pWindow = this;

	return TRUE;
}

BOOL CUIWndBitmap::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}


void CUIWndBitmap::LoadUIBitmap()
{
	CString strBmpPath;
	CString strFile;
	strBmpPath = _P_GetSource_Bitmap_Path();

	strFile = strBmpPath + m_strNormalBmpFile;
	m_oDibNormal.Load(strFile);

	strFile = strBmpPath + m_strClickBmpFile;
	m_oDibClick.Load(strFile);

	strFile = strBmpPath + m_strActiveBmpFile;
	m_oDibActive.Load(strFile);

	strFile = strBmpPath + m_strDisablelBmpFile;
	m_oDibDisable.Load(strFile);

// 	m_oDibNormal.SetTransparent(m_nTransparent);
// 	m_oDibClick.SetTransparent(m_nTransparent);
// 	m_oDibActive.SetTransparent(m_nTransparent);
// 	m_oDibDisable.SetTransparent(m_nTransparent);

	m_oDibNormal.SetMaskColor(m_crTransMaskColor);
	m_oDibClick.SetMaskColor(m_crTransMaskColor);
	m_oDibActive.SetMaskColor(m_crTransMaskColor);
	m_oDibDisable.SetMaskColor(m_crTransMaskColor);
}

void CUIWndBitmap::OnPaint() 
{
// 	CTickCount32 oTick32;
	CPaintDC dc(this); // device context for painting
	BOOL bDraw = FALSE;

	CDC *pDC = &dc;//m_oUIMemDC->GetDC();
	//dc.FillSolidRect(0,0,m_nWidth, m_nHeight, RGB(0,255, 0));
	TRACE(_T("%s m_bSelected=%d m_bFocus=%d\n"), m_strID, m_bSelected, m_bFocus);

	if (!IsEnable())
	{
		bDraw = m_oDibDisable.Draw(pDC, 0, 0, m_nWidth, m_nHeight);
	}
	else 
	{
		if (m_bOver)
		{
			if (m_bSelected)
			{
				bDraw = m_oDibClick.Draw(pDC, 0, 0, m_nWidth, m_nHeight);
			}
			else
			{
				bDraw = m_oDibActive.Draw(pDC, 0, 0, m_nWidth, m_nHeight);
			}
		}
		else
		{
			if (m_bFocus)
			{
				bDraw = m_oDibActive.Draw(pDC, 0, 0, m_nWidth, m_nHeight);
			}
			else
			{
				bDraw = m_oDibNormal.Draw(pDC, 0, 0, m_nWidth, m_nHeight);
			}
		}
	}

	if (!bDraw)
	{
		m_oDibNormal.Draw(pDC, 0, 0, m_nWidth, m_nHeight);
	}
// 
// 	m_oUIMemDC->DrawTransparent(&dc, RGB(0, 0, 255));
	//m_oUIMemDC->Draw(&dc);
}


void CUIWndBitmap::OnClicked() 
{
	
}

void CUIWndBitmap::OnDoubleclicked() 
{
	UI_OnDoubleclicked();
}

void CUIWndBitmap::OnMouseMove(UINT nFlags, CPoint point) 
{
	UI_OnMouseMove(nFlags, point);

	CStatic::OnMouseMove(nFlags, point);
}

LRESULT CUIWndBitmap::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	RedrawParentRect();
	return UI_OnMouseLeave(wParam, lParam);
}

LRESULT CUIWndBitmap::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	RedrawParentRect();
	return UI_OnMouseHover(wParam, lParam);
}


void CUIWndBitmap::OnLButtonDown(UINT nFlags, CPoint point)
{
	UI_OnLButtonDown(nFlags, point);

	__super::OnLButtonDown(nFlags, point);
}

void CUIWndBitmap::OnLButtonUp(UINT nFlags, CPoint point)
{
	UI_OnLButtonUp(nFlags, point);

	if (m_bFocus && m_bOver)
	{
		UI_OnClicked();
	}

	__super::OnLButtonUp(nFlags, point);
}

HBRUSH CUIWndBitmap::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	pDC->SetBkMode(TRANSPARENT);

// 	if (m_pFont != NULL)
// 	{
// 		pDC->SetTextColor(m_pFont->m_crColor);
// 	}
// 	else
// 	{
// 		pDC->SetTextColor(RGB(255, 0, 0));
// 	}
// 
	return hbr;
}