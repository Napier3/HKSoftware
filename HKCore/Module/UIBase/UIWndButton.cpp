//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndButton.cpp  CUIWndButton


#include "stdafx.h"
#include "UIWndButton.h"

CUIWndButton::CUIWndButton()
{
	//初始化属性

	//初始化成员变量
}

CUIWndButton::~CUIWndButton()
{
}

long CUIWndButton::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndButton::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndButton::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CUIWndButton::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndButton::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndButton *p = (CUIWndButton*)pObj;

	return TRUE;
}

BOOL CUIWndButton::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndButton *p = (CUIWndButton*)pDest;

	return TRUE;
}

CBaseObject* CUIWndButton::Clone()
{
	CUIWndButton *p = new CUIWndButton();
	Copy(p);
	return p;
}

BOOL CUIWndButton::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndButton::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

    pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndButton::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}


BEGIN_MESSAGE_MAP(CUIWndButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CUIWndButton::OnBnClicked)
//	ON_WM_PAINT()
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, &CUIWndButton::OnBnDoubleclicked)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()


BOOL CUIWndButton::UICreate(CWnd *pParent)
{
	if (m_pWindow != NULL)
	{
		LOG_WriteLawString("recreate Button");
	}

	CRect rect = GetWndPosition();
	BOOL bState = FALSE;	

	bState = Create(NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_OWNERDRAW,
		rect,
		pParent,
		GenerateWindowID());

	if (!bState)
	{
		return FALSE;
	}

	ShowWindow(SW_SHOW);
	m_pWindow = this;

	m_crFrmPen.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, m_crFrmTopLeftColor);
	m_crFontPen.CreatePen(PS_INSIDEFRAME | PS_SOLID,1,m_crForeColor);
	m_crFillBkBrush.CreateSolidBrush(m_crBkColor);

	return TRUE;
}

BOOL CUIWndButton::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	m_crFrmPen.DeleteObject();
	m_crFontPen.DeleteObject();
	m_crFillBkBrush.DeleteObject();

	return TRUE;
}


void CUIWndButton::OnBnClicked()
{
	UI_OnClicked();
}


void CUIWndButton::OnBnDoubleclicked()
{
	UI_OnDoubleclicked();
}

void CUIWndButton::OnMouseMove(UINT nFlags, CPoint point)
{
	UI_OnMouseMove(nFlags, point);
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CUIWndButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return UI_OnMouseLeave(wParam, lParam);
}

LRESULT CUIWndButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	return UI_OnMouseHover(wParam, lParam);
}

void CUIWndButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//从lpDrawItemStruct获取控件的相关信息
	CRect rect =  lpDrawItemStruct->rcItem;
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC=pDC->SaveDC();
	UINT state = lpDrawItemStruct->itemState;
	POINT pt ;
	TCHAR strText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, strText, MAX_PATH);
	
	//画按钮的外边框，它是一个半径为5的圆角矩形
	pt.x = 5;
	pt.y = 5;
	pDC->SelectObject(&m_crFrmPen);
	pDC->RoundRect(&rect, pt);

	//获取按钮的状态
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}

	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}

	rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));

	//根据按钮的状态填充按钮的底色

	if (m_bOver)
	{
		pDC->SelectObject(&m_crFillBkBrush);
		DoGradientFill(pDC, &rect);
	}
	else
	{
		pDC->SelectObject(&m_crFillBkBrush);
		DoGradientFill(pDC, &rect);
	}

	//文本
	if ( m_pText->m_strText.GetLength() != 0)
	{
		CFont* hFont = GetFont();
		CFont* hOldFont = pDC->SelectObject(hFont);
		CSize szExtent = pDC->GetTextExtent(strText, lstrlen(strText));
		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
		if (state & ODS_SELECTED) 
			pt.Offset(1, 1);
		int nMode = pDC->SetBkMode(TRANSPARENT);

		CRect rcClient;
		GetClientRect(&rcClient);
		rcClient.DeflateRect(2,2);
		COLORREF cr ;

		if (state & ODS_DISABLED)
		{
			cr = pDC->SetTextColor(RGB(51,51,51));
			pDC->DrawText(m_pText->m_strText, rcClient, DT_CENTER | DT_WORDBREAK | DT_VCENTER);
			pDC->SetTextColor(cr);
		}
		else
		{
			cr = pDC->SetTextColor(m_crForeColor);
			pDC->DrawText(m_pText->m_strText, rcClient, DT_CENTER | DT_WORDBREAK | DT_VCENTER);	
			pDC->SetTextColor(cr);
		}

		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);
	}

	pDC->RestoreDC(nSaveDC);
}

