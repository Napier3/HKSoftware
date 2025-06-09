//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndEdit.cpp  CUIWndEdit


#include "stdafx.h"
#include "UIWndEdit.h"

CUIWndEdit::CUIWndEdit()
{
	//初始化属性

	//初始化成员变量
}

CUIWndEdit::~CUIWndEdit()
{
}

long CUIWndEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);
	return 0;
}

long CUIWndEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	return 0;
}

long CUIWndEdit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFormat);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFormat);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFormat);
	}
	return 0;
}

void CUIWndEdit::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndEdit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndEdit *p = (CUIWndEdit*)pObj;

	if(m_strFormat != p->m_strFormat)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndEdit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndEdit *p = (CUIWndEdit*)pDest;

	p->m_strFormat = m_strFormat;
	return TRUE;
}

CBaseObject* CUIWndEdit::Clone()
{
	CUIWndEdit *p = new CUIWndEdit();
	CUIWindowBase::Copy(p);
	return p;
}

BOOL CUIWndEdit::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndEdit::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}

BOOL CUIWndEdit::UICreate(CWnd *pParent)
{
	if ( m_pWindow != NULL )
	{
		LOG_WriteLawString("recreate button");
	}

	CRect rect = GetWndPosition();

	BOOL status = Create(
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
		rect,
		pParent,
		GenerateWindowID());

	if ( !status )
	{
		return FALSE;
	}

	if (m_strFormat == "Password")
	{
		this->SetPasswordChar('*');
	}

	CUIBaseFont *pUIFont = GetUIBaseFont();      //获取当前的Font

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

BOOL CUIWndEdit::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CUIWndEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CUIWndEdit::OnEnChange)
END_MESSAGE_MAP()

void CUIWndEdit::OnEnChange()
{
	if (m_pWindow)
	{
		GetWindowText(m_pText->m_strText);
	}
}
