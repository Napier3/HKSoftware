//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndStaticText.cpp  CUIWndStaticText


#include "stdafx.h"
#include "UIWndStaticText.h"

CUIWndStaticText::CUIWndStaticText()
{
	//初始化属性

	//初始化成员变量
}

CUIWndStaticText::~CUIWndStaticText()
{
}

long CUIWndStaticText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndStaticText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndStaticText::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CUIWndStaticText::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndStaticText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndStaticText *p = (CUIWndStaticText*)pObj;

	return TRUE;
}

BOOL CUIWndStaticText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndStaticText *p = (CUIWndStaticText*)pDest;

	return TRUE;
}

CBaseObject* CUIWndStaticText::Clone()
{
	CUIWndStaticText *p = new CUIWndStaticText();
	Copy(p);
	return p;
}

BOOL CUIWndStaticText::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndStaticText::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);


	return pNew;
}

CExBaseObject* CUIWndStaticText::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}



BEGIN_MESSAGE_MAP(CUIWndStaticText, CStatic)
	//{{AFX_MSG_MAP(CUIWndStaticText)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CUIWndStaticText::UICreate(CWnd *pParent)
{
	if ( m_pWindow != NULL )
	{
		LOG_WriteLawString("recreate button");
	}

	CRect rect = GetWndPosition();

	BOOL status = Create(
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT ,
		rect,
		pParent,
		GenerateWindowID());

	if ( !status )
	{
		return FALSE;
	}

	CUIBaseFont *pFont = GetUIBaseFont();

	if (pFont != NULL)
	{
		SetFont(pFont->GetFont());
	}

	if (m_pText != NULL)
	{
		SetWindowText(m_pText->m_strText);
	}
	else
	{
		SetWindowText(m_strID);
	}

	ShowWindow(SW_SHOW);	
	m_pWindow = this;

	return TRUE;
}


BOOL CUIWndStaticText::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}

HBRUSH CUIWndStaticText::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	pDC->SetBkMode(TRANSPARENT);

	if (m_pFont != NULL)
	{
		pDC->SetTextColor(m_pFont->m_crColor);
	}
	else
	{
		pDC->SetTextColor(RGB(0, 0, 0));
	}

	return hbr;
}

void CUIWndStaticText::OnClicked() 
{
	Event_OnClick();	
}

void CUIWndStaticText::SetWndText(CString strWndText)
{
	CUIWindowBase::SetWndText(strWndText);

	if (m_pWindow == NULL)
	{
		return;
	}

	CWnd *pParentWnd = (CWnd*)m_pWindow->GetParent();

	if (pParentWnd != NULL)
	{
		if (::IsWindow(pParentWnd->m_hWnd))
		{
			pParentWnd->InvalidateRect(GetWndPosition(), TRUE);
		}
	}
}