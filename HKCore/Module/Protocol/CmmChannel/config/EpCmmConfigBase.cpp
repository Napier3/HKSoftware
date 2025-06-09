#include "StdAfx.h"
#include "EpCmmConfigBase.h"
//#include "EpCmmOnConnect.h"

CEpCmmConfigBase::CEpCmmConfigBase(void)
{
	m_nReceiveTimeout = 1000;
	m_nSendTimeout = 1000;
}

CEpCmmConfigBase::~CEpCmmConfigBase(void)
{
}

//´®ÐÐ»¯
long CEpCmmConfigBase::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CEpCmmConfigBase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
// 	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strSendTimeout,oNode,m_nSendTimeout);
// 	xml_GetAttibuteValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strReceiveTimeout,oNode,m_nReceiveTimeout);

	return 0;
}

long CEpCmmConfigBase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
// 	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strSendTimeout,oElement,m_nSendTimeout);
// 	xml_SetAttributeValue(CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strReceiveTimeout,oElement,m_nReceiveTimeout);

	return 0;
}


//±à¼­
BOOL CEpCmmConfigBase::IsEqualOwn(CBaseObject* pObj)
{ 
	return TRUE;
}

BOOL CEpCmmConfigBase::CopyOwn(CBaseObject* pDest)
{
	((CEpCmmConfigBase*)pDest)->m_nSendTimeout = m_nSendTimeout;
	((CEpCmmConfigBase*)pDest)->m_nReceiveTimeout = m_nReceiveTimeout;

	return TRUE;
}

CBaseObject* CEpCmmConfigBase::Clone()
{
	return NULL;
}

CExBaseObject* CEpCmmConfigBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
// 	if(nClassID == EPCLASSID_CMM_ONCONNECT)
// 	{
// 		return new CEpCmmConfigBase;
// 	}

	return NULL;
}

CExBaseObject* CEpCmmConfigBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
// 	if(strClassID==CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strOnConnectKey)
// 	{
// 		return new CEpCmmOnConnect;
// 	}

	return NULL;
}

