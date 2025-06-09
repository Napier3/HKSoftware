//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MessageImp.cpp  CMessageImp


#include "stdafx.h"
#include "MessageImp.h"

CMessageImp::CMessageImp()
{
	//初始化属性
	m_nSysMsg = 0;

	//初始化成员变量
}

CMessageImp::~CMessageImp()
{
}

long CMessageImp::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strWndStateKey, oNode, m_strWndState);
	xml_GetAttibuteValue(pXmlKeys->m_strSysMsgKey, oNode, m_nSysMsg);
	xml_GetAttibuteValue(pXmlKeys->m_strScriptKey, oNode, m_strScript);
	return 0;
}

long CMessageImp::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strWndStateKey, oElement, m_strWndState);
	xml_SetAttributeValue(pXmlKeys->m_strSysMsgKey, oElement, m_nSysMsg);
	xml_SetAttributeValue(pXmlKeys->m_strScriptKey, oElement, m_strScript);
	return 0;
}

long CMessageImp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMessageImp::InitAfterRead()
{
}

BOOL CMessageImp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMessageImp *p = (CMessageImp*)pObj;

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

BOOL CMessageImp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMessageImp *p = (CMessageImp*)pDest;

	p->m_strWndState = m_strWndState;
	p->m_nSysMsg = m_nSysMsg;
	p->m_strScript = m_strScript;
	return TRUE;
}

CBaseObject* CMessageImp::Clone()
{
	CMessageImp *p = new CMessageImp();
	Copy(p);
	return p;
}




void CMessageImp::Run(BOOL bShowMessage)
{
	
}

CBaseObject* CMessageImp::GetParentPage()
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
