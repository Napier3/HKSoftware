//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndEdit.cpp  CUIWndEdit


#include "stdafx.h"
#include "UIWndListControl.h"

CUIWndListControl::CUIWndListControl()
{
	//初始化属性

	//初始化成员变量
}

CUIWndListControl::~CUIWndListControl()
{
}

long CUIWndListControl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);
	return 0;
}

long CUIWndListControl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	return 0;
}

long CUIWndListControl::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CUIWndListControl::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndListControl::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndListControl *p = (CUIWndListControl*)pObj;

	if(m_strFormat != p->m_strFormat)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndListControl::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndListControl *p = (CUIWndListControl*)pDest;

	p->m_strFormat = m_strFormat;
	return TRUE;
}

CBaseObject* CUIWndListControl::Clone()
{
	CUIWndListControl *p = new CUIWndListControl();
	CUIWindowBase::Copy(p);
	return p;
}

BOOL CUIWndListControl::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndListControl::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndListControl::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}

BOOL CUIWndListControl::UICreate(CWnd *pParent)
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
		//this->SetPasswordChar('*');
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

BOOL CUIWndListControl::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CUIWndListControl, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CUIWndListControl::OnEnChange)
END_MESSAGE_MAP()

void CUIWndListControl::OnEnChange()
{
	if (m_pWindow)
	{
		GetWindowText(m_pText->m_strText);
	}
}
