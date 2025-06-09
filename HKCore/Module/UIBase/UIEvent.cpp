//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIEvent.cpp  CUIEvent


#include "stdafx.h"
#include "UIEvent.h"
#include "UILuaScript.h"
#include "..\System\TickCount32.h"

CUIEvent::CUIEvent()
{
	//初始化属性
	m_nSysMsg = 0;

	//初始化成员变量
}

CUIEvent::~CUIEvent()
{
}

long CUIEvent::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strWndStateKey, oNode, m_strWndState);
	xml_GetAttibuteValue(pXmlKeys->m_strSysMsgKey, oNode, m_nSysMsg);

	xml_GetCDATA(oNode, m_strScript);

	return 0;
}

long CUIEvent::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strWndStateKey, oElement, m_strWndState);
	xml_SetAttributeValue(pXmlKeys->m_strSysMsgKey, oElement, m_nSysMsg);

	xml_SetCDATA(oXMLDoc, oElement, m_strScript);

	return 0;
}

long CUIEvent::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strWndState);
		BinarySerializeCalLen(oBinaryBuffer, m_nSysMsg);
		BinarySerializeCalLen(oBinaryBuffer, m_strScript);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strWndState);
		BinarySerializeRead(oBinaryBuffer, m_nSysMsg);
		BinarySerializeRead(oBinaryBuffer, m_strScript);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strWndState);
		BinarySerializeWrite(oBinaryBuffer, m_nSysMsg);
		BinarySerializeWrite(oBinaryBuffer, m_strScript);
	}
	return 0;
}

void CUIEvent::InitAfterRead()
{
}

BOOL CUIEvent::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIEvent *p = (CUIEvent*)pObj;

	if(m_strWndState != p->m_strWndState)
	{
		return FALSE;
	}

	if(m_nSysMsg != p->m_nSysMsg)
	{
		return FALSE;
	}

	if(m_strScript != p->m_strScript)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIEvent::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUIEvent *p = (CUIEvent*)pDest;

	p->m_strWndState = m_strWndState;
	p->m_nSysMsg = m_nSysMsg;
	p->m_strScript = m_strScript;
	return TRUE;
}

CBaseObject* CUIEvent::Clone()
{
	CUIEvent *p = new CUIEvent();
	Copy(p);
	return p;
}




void CUIEvent::Run()
{
// 	CTickCount32 oTick32;
	CString strSyntaxError;
	UILuaScript::UI_RunScript(this, strSyntaxError);
// 	CString strText;
// 	strText.Format(_T("\r\nTime=%d\r\n"), oTick32.GetTickCountLong(TRUE));
// 	TRACE(strText);
}

CBaseObject* CUIEvent::GetParentPage()
{
	CBaseObject *pParent = GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == UICLASSID_CUIWNDPAGE)
		{
			break;
		}

		pParent = pParent->GetParent();
	}

	ASSERT (pParent != NULL);

	return pParent;
}


CExBaseObject* CUIEvent::GetParentWnd()
{
	CExBaseObject *pParentWnd = (CExBaseObject*)GetParent();

	ASSERT (pParentWnd != NULL);

	pParentWnd = (CExBaseObject *)pParentWnd->GetParent();
	ASSERT(pParentWnd != NULL);

	return pParentWnd;
}

