#include "stdafx.h"
#include "Msg.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMsg::CMsg()
{
	m_strName = g_sLangTxt_MsgPrompt/*_T("消息提示")*/;
	m_nUseCData = 1;
}

CMsg::~CMsg()
{

}

long CMsg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
	}

	return 0;
}

long CMsg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	m_nUseCData = -1;
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey, oNode, m_nUseCData);

	if (m_nUseCData == -1)
	{
		m_strMsg = oNode.Gettext();
	}
	else
	{
		xml_GetCDATA(oNode, m_strMsg);
	}

	m_nUseCData = 1;
	return 0;
}

long CMsg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//oElement->put_text((_bstr_t)m_strMsg);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey, oElement, m_nUseCData);
	xml_SetCDATA(oXMLDoc, oElement, m_strMsg);

	return 0;
}

BSTR CMsg::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strMsgKey;
}

BOOL CMsg::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CMsg* pMsg = (CMsg*)pObj;
		if(CExBaseObject::IsEqual(pObj) && pMsg->m_strMsg == m_strMsg)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMsg::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;
	CExBaseObject::CopyOwn(pDesObj);
	CMsg* pMsgObj = (CMsg*)pDesObj;
	pMsgObj->m_strMsg = m_strMsg;
	return TRUE;
}

CBaseObject* CMsg::Clone()
{
	CMsg* pMsg = new CMsg();
	Copy(pMsg);

	return pMsg;
}