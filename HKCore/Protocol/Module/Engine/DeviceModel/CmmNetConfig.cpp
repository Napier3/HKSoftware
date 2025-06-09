#include "StdAfx.h"
#include "CmmNetConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmNetConfig::CCmmNetConfig(void)
{
}

CCmmNetConfig::~CCmmNetConfig(void)
{
	int i = 0;
}

//基本方法
void CCmmNetConfig::Init()
{

}

void CCmmNetConfig::InitAfterRead()
{
	return ;
}

//串行化
long CCmmNetConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmNetConfig::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


long CCmmNetConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


//编辑
BOOL CCmmNetConfig::IsEqualOwn(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CCmmNetConfig::CopyOwn(CBaseObject* pDest)
{
	return FALSE;
}

CBaseObject* CCmmNetConfig::Clone()
{
	CCmmNetConfig *pNew = new CCmmNetConfig();

	Copy(pNew);

	return pNew;
}


//创建子对象
CExBaseObject* CCmmNetConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject* CCmmNetConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey)
	{
		pNew = new CCmmTcpServerConfig();
	}
	else if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey)
	{
		pNew = new CCmmTcpClientConfig();
	}
	else if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey)
	{
		pNew = new CCmmUdpServerConfig();
	}
	else if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey)
	{
		pNew = new CCmmUdpClientConfig();
	}
	else
	{

	}


	if (pNew != NULL)
	{
		pNew->m_strName = strClassID;
		pNew->m_strID = strClassID;
	}


	return pNew;
}


CExBaseObject* CCmmNetConfig::GetChildByClassID(UINT nClassID)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
	UINT nID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		nID = p->GetClassID();

		if (nClassID == nID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCmmTcpServerConfig* CCmmNetConfig::GetConfigTcpServer()
{
	return (CCmmTcpServerConfig*)FindByClassID(DMCLASSID_CMM_TCP_SERVER_CONFIG);
}

CCmmTcpClientConfig* CCmmNetConfig::GetConfigTcpClient()
{
	return (CCmmTcpClientConfig*)FindByClassID(DMCLASSID_CMM_TCP_CLIENT_CONFIG);
}

CCmmUdpServerConfig* CCmmNetConfig::GetConfigUdpServer()
{
	return (CCmmUdpServerConfig*)FindByClassID(DMCLASSID_CMM_UDP_SERVER_CONFIG);
}

CCmmUdpClientConfig* CCmmNetConfig::GetConfigUdpClient()
{
	return (CCmmUdpClientConfig*)FindByClassID(DMCLASSID_CMM_UDP_CLIENT_CONFIG);
}

CCmmTcpServerConfig* CCmmNetConfig::AddConfigTcpServer()
{
	CCmmTcpServerConfig *pCfg = GetConfigTcpServer();

	if (pCfg == NULL)
	{
		pCfg = new CCmmTcpServerConfig();
		AddNewChild(pCfg);
	}

	return pCfg;
}

CCmmTcpClientConfig* CCmmNetConfig::AddConfigTcpClient()
{
	CCmmTcpClientConfig *pCfg = GetConfigTcpClient();

	if (pCfg == NULL)
	{
		pCfg = new CCmmTcpClientConfig();
		AddNewChild(pCfg);
	}

	return pCfg;
}

CCmmUdpServerConfig* CCmmNetConfig::AddConfigUdpServer()
{
	CCmmUdpServerConfig *pCfg = GetConfigUdpServer();

	if (pCfg == NULL)
	{
		pCfg = new CCmmUdpServerConfig();
		AddNewChild(pCfg);
	}

	return pCfg;
}

CCmmUdpClientConfig* CCmmNetConfig::AddConfigUdpClient()
{
	CCmmUdpClientConfig *pCfg = GetConfigUdpClient();

	if (pCfg == NULL)
	{
		pCfg = new CCmmUdpClientConfig();
		AddNewChild(pCfg);
	}

	return pCfg;
}

void CCmmNetConfig::DeleteConfigTcpServer()
{
	CCmmTcpServerConfig *pCfg = GetConfigTcpServer();

	if (pCfg != NULL)
	{
		Delete(pCfg);
	}
}

void CCmmNetConfig::DeleteConfigTcpClient()
{
	CCmmTcpClientConfig *pCfg = GetConfigTcpClient();

	if (pCfg != NULL)
	{
		Delete(pCfg);
	}
}

void CCmmNetConfig::DeleteConfigUdpServer()
{
	CCmmUdpServerConfig *pCfg = GetConfigUdpServer();

	if (pCfg != NULL)
	{
		Delete(pCfg);
	}
}

void CCmmNetConfig::DeleteConfigUdpClient()
{
	CCmmUdpClientConfig *pCfg = GetConfigUdpClient();

	if (pCfg != NULL)
	{
		Delete(pCfg);
	}
}

void CCmmNetConfig::SetRemoteIP(const CString &strIP, long nPort)
{
	CCmmTcpClientConfig* pTcpClient = GetConfigTcpClient();

	if (pTcpClient != NULL)
	{
		pTcpClient->m_strRemoteIP = strIP;
		pTcpClient->m_nRemotePort = nPort;
		return;
	}

	CCmmUdpClientConfig *pUdpClient = GetConfigUdpClient();

	if (pUdpClient != NULL)
	{
		pUdpClient->m_strRemoteIP = strIP;
		pUdpClient->m_nRemotePort = nPort;
		return;
	}

}

