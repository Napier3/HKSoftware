//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndCheckBox.cpp  CUIWndCheckBox


#include "stdafx.h"
#include "UIWndCheckBox.h"

CUIWndCheckBox::CUIWndCheckBox()
{
	//初始化属性

	//初始化成员变量
}

CUIWndCheckBox::~CUIWndCheckBox()
{
}

long CUIWndCheckBox::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndCheckBox::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndCheckBox::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CUIWndCheckBox::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndCheckBox::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndCheckBox *p = (CUIWndCheckBox*)pObj;

	return TRUE;
}

BOOL CUIWndCheckBox::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndCheckBox *p = (CUIWndCheckBox*)pDest;

	return TRUE;
}

CBaseObject* CUIWndCheckBox::Clone()
{
	CUIWndCheckBox *p = new CUIWndCheckBox();
	Copy(p);
	return p;
}

BOOL CUIWndCheckBox::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndCheckBox::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndCheckBox::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}

BOOL CUIWndCheckBox::UICreate(CWnd *pParent)
{
	if ( m_pWindow != NULL )
	{
		LOG_WriteLawString("recreate button");
	}

	CRect rect = GetWndPosition();

	BOOL status = Create(
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX ,
		rect,
		pParent,
		GenerateWindowID());

	if ( !status )
	{
		return FALSE;
	}

	CUIBaseFont *pUIFont = GetUIBaseFont();

	if (pUIFont != NULL)
	{
		CFont *pFont = pUIFont->GetFont();
		SetFont(pFont);
	}

	if (m_pText != NULL)
	{
		SetWindowText(m_pText->m_strText);
	}
	else
	{
		SetWindowText(NULL);
	}

	ShowWindow(SW_SHOW);

	m_pWindow = this;

	return TRUE;
}

BOOL CUIWndCheckBox::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}



BEGIN_MESSAGE_MAP(CUIWndCheckBox, CButton)
ON_CONTROL_REFLECT(BN_CLICKED, &CUIWndCheckBox::OnBnClicked)
ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CUIWndCheckBox::OnBnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
}

HBRUSH CUIWndCheckBox::CtlColor(CDC* pDC, UINT nCtlColor)
{
	HBRUSH hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	pDC->SetBkMode(TRANSPARENT);

	return hbr;
}
