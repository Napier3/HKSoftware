#include "StdAfx.h"
#include "CmmTcpServerConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmTcpServerConfig::CCmmTcpServerConfig(void)
{
	m_strName = _T("tcp-server");
	m_strID = m_strName;
}

CCmmTcpServerConfig::~CCmmTcpServerConfig(void)
{
}


//´®ÐÐ»¯
long CCmmTcpServerConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmTcpServerConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetServerConfig::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CCmmTcpServerConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCmmNetServerConfig::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CCmmTcpServerConfig::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CCmmTcpServerConfig*)pDest)->m_bPostConnectFinishMsgAfterAccept = m_bPostConnectFinishMsgAfterAccept;

	CCmmNetServerConfig::CopyOwn(pDest);

	return TRUE;
}



CBaseObject* CCmmTcpServerConfig::Clone()
{
	CCmmTcpServerConfig *pNew = new CCmmTcpServerConfig();

	Copy(pNew);

	return pNew;
}

