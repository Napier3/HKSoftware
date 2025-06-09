#include "StdAfx.h"
#include "EpCmmChannelCreateMngr.h"


long CEpCmmChannelCreateMngr::g_nEpCmmChannelCreateMngrRef = 0;
CEpCmmChannelCreateMngr* CEpCmmChannelCreateMngr::g_pEpCmmChannelCreateMngr = NULL;

CEpCmmChannelCreateMngr* CEpCmmChannelCreateMngr::Create()
{
	g_nEpCmmChannelCreateMngrRef++;

	if (g_nEpCmmChannelCreateMngrRef == 1)
	{
		g_pEpCmmChannelCreateMngr = new CEpCmmChannelCreateMngr();
	}	

	return g_pEpCmmChannelCreateMngr;
}
void CEpCmmChannelCreateMngr::Release()
{
	g_nEpCmmChannelCreateMngrRef--;

	if (g_nEpCmmChannelCreateMngrRef == 0)
	{
		delete g_pEpCmmChannelCreateMngr;
		g_pEpCmmChannelCreateMngr = NULL;
	}
}

CEpCmmChannelCreateMngr::CEpCmmChannelCreateMngr(void)
{

}

CEpCmmChannelCreateMngr::~CEpCmmChannelCreateMngr(void)
{

}


CEpCmmTcpServer* CEpCmmChannelCreateMngr::RegisterTcpServer(CEpCmmTcpServerChannel *pTcpServerChannel)
{
	ASSERT (pTcpServerChannel != NULL);

	CEpCmmTcpServerConfig *pConfig = pTcpServerChannel->m_pConfig;
	CEpCmmNetServer *pServer = g_pEpCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);
	UINT nClassID = 0;
	CEpCmmTcpServer *pTcpServer = NULL;

	if (pServer != NULL)
	{//找到相同的服务器
		nClassID = pServer->GetClassID();

		if (nClassID == EPCMMCLASSID_TCPSERVER)
		{//为TCP服务器
			pTcpServerChannel->m_pNetServer = pServer;
			pServer->AddTail(pTcpServerChannel);
			pTcpServer = (CEpCmmTcpServer*)pServer;
		}
		else
		{//为UDP服务器
			CLogPrint::LogFormatString(g_pLogTracePrint, LOGLEVEL_ERROR, _T("存在同名的UDP服务器(IP=%s  Port=%d)"), pConfig->m_strLocalIP, pConfig->m_nLocalPort);
		}
	}
	else
	{
		pTcpServer = new CEpCmmTcpServer();
		g_pEpCmmChannelCreateMngr->AddTail(pTcpServer);
		pTcpServerChannel->m_pNetServer = pTcpServer;
		pTcpServer->AddTail(pTcpServerChannel);
		pTcpServer->CreateServer( pConfig->m_strLocalIP, pConfig->m_nLocalPort, _T(""), 0);
	}

	return pTcpServer;
}

CEpCmmUdpServer* CEpCmmChannelCreateMngr::RegisterUdpServer(CEpCmmUdpServerChannel *pUdpServerChannel)
{
	ASSERT (pUdpServerChannel != NULL);

	CEpCmmUdpConfig *pConfig = pUdpServerChannel->m_pConfig;
	CEpCmmNetServer *pServer = g_pEpCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);
	UINT nClassID = 0;
	CEpCmmUdpServer *pUdpServer = NULL;

	if (pServer != NULL)
	{//找到相同的服务器
		nClassID = pServer->GetClassID();

		if (nClassID == EPCMMCLASSID_UDPSERVER)
		{//为TCP服务器
			pServer->AddTail(pUdpServerChannel);
			pUdpServer = (CEpCmmUdpServer*)pServer;
			pUdpServerChannel->m_pNetServer = pServer;
		}
		else
		{//为UDP服务器
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("存在同名的TCP服务器(IP=%s  Port=%d)"), pConfig->m_strLocalIP, pConfig->m_nLocalPort);
		}
	}
	else
	{
		pUdpServer = new CEpCmmUdpServer();
		g_pEpCmmChannelCreateMngr->AddTail(pUdpServer);
		pUdpServerChannel->m_pNetServer = pUdpServer;
		pUdpServer->AddTail(pUdpServerChannel);
		pUdpServer->CreateServer( pConfig->m_strLocalIP, pConfig->m_nLocalPort, pConfig->m_strMulticastIP, pConfig->m_nMulticastPort);
	}

	return pUdpServer;
}

void CEpCmmChannelCreateMngr::UnRegisterTcpServer(CEpCmmTcpServerChannel *pTcpServerChannel)
{
	CEpCmmTcpServerConfig *pConfig = pTcpServerChannel->m_pConfig;
	CEpCmmNetServer *pServer = g_pEpCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);

	if (pServer != NULL)
	{
		pServer->CloseServer(pTcpServerChannel);
	}

	return ;
}

void CEpCmmChannelCreateMngr::UnRegisterUdpServer(CEpCmmUdpServerChannel *pUdpServerChannel)
{
	CEpCmmUdpConfig *pConfig = pUdpServerChannel->m_pConfig;
	CEpCmmNetServer *pServer = g_pEpCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);

	if (pServer != NULL)
	{
		pServer->CloseServer(pUdpServerChannel);
	}

	return ;
}

void CEpCmmChannelCreateMngr::UnRegisterServer(CEpCmmNetServer *pServer)
{
	POS pos = g_pEpCmmChannelCreateMngr->Find(pServer);

	if (pos == NULL)
	{
		delete pServer;
		return;
	}

	if (pServer->GetCount() == 0)
	{
		g_pEpCmmChannelCreateMngr->RemoveAt(pos);
		delete pServer;
	}
}

// 
// CEpCmmTcpServer* CEpCmmChannelCreateMngr::RegisterTcpServer(const CString &strIP, UINT nPort)
// {
// 	return NULL;
// }
// 
// CEpCmmUdpServer* CEpCmmChannelCreateMngr::RegisterUdpServer(const CString &strIP, UINT nPort)
// {
// 	return NULL;
// }
// 
// void CEpCmmChannelCreateMngr::UnRegisterTcpServer(const CString &strIP, UINT nPort)
// {
// 	return ;
// }
// 
// void CEpCmmChannelCreateMngr::UnRegisterUdpServer(const CString &strIP, UINT nPort)
// {
// 	return ;
// }
// 
// void CEpCmmChannelCreateMngr::UnRegisterTcpServer(CEpCmmTcpServer *pServer)
// {
// 	return ;
// }
// 
// void CEpCmmChannelCreateMngr::UnRegisterUdpServer(CEpCmmUdpServer *pServer)
// {
// 	return ;
// }
// 


CEpCmmNetServer* CEpCmmChannelCreateMngr::FindNetServer(const CString &strIP, UINT nPort)
{
	CEpCmmNetServer *pFind = NULL;
	CEpCmmNetServer *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpCmmNetServer*)GetNext(pos);

		if (p->IsEqual(strIP, nPort))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

