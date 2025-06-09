#include "StdAfx.h"
#include "CmmTcpClientConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmTcpClientConfig::CCmmTcpClientConfig(void)
{
	m_strName = _T("tcp-client");
	m_strID = m_strName;
}

CCmmTcpClientConfig::~CCmmTcpClientConfig(void)
{
}


//´®ÐÐ»¯
long CCmmTcpClientConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmTcpClientConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetClientConfig::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CCmmTcpClientConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetClientConfig::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}


BOOL CCmmTcpClientConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CCmmNetClientConfig::CopyOwn(pDest);
}



CBaseObject* CCmmTcpClientConfig::Clone()
{
	CCmmTcpClientConfig *pNew = new CCmmTcpClientConfig();

	Copy(pNew);

	return pNew;
}

