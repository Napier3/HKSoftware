#include "StdAfx.h"
#include "CmmChannelCreateMngr.h"
#include "../../XLanguageResourcePp.h"


long CCmmChannelCreateMngr::g_nCmmChannelCreateMngrRef = 0;
CCmmChannelCreateMngr* CCmmChannelCreateMngr::g_pCmmChannelCreateMngr = NULL;

CCmmChannelCreateMngr* CCmmChannelCreateMngr::Create()
{
	g_nCmmChannelCreateMngrRef++;

	if (g_nCmmChannelCreateMngrRef == 1)
	{
		g_pCmmChannelCreateMngr = new CCmmChannelCreateMngr();
	}	

	return g_pCmmChannelCreateMngr;
}
void CCmmChannelCreateMngr::Release()
{
	g_nCmmChannelCreateMngrRef--;

	if (g_nCmmChannelCreateMngrRef == 0)
	{
		delete g_pCmmChannelCreateMngr;
		g_pCmmChannelCreateMngr = NULL;
	}
}

CCmmChannelCreateMngr::CCmmChannelCreateMngr(void)
{

}

CCmmChannelCreateMngr::~CCmmChannelCreateMngr(void)
{

}


CCmmTcpServer* CCmmChannelCreateMngr::RegisterTcpServer(CCmmTcpServerChannel *pTcpServerChannel)
{
	ASSERT (pTcpServerChannel != NULL);

	CCmmTcpServerConfig *pConfig = pTcpServerChannel->m_pConfig;
	CCmmNetServer *pServer = g_pCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);
	UINT nClassID = 0;
	CCmmTcpServer *pTcpServer = NULL;

	if (pServer != NULL)
	{//找到相同的服务器
		nClassID = pServer->GetClassID();

		if (nClassID == CMMCLASSID_TCPSERVER)
		{//为TCP服务器
			pTcpServerChannel->m_pNetServer = pServer;
			pServer->AddTail(pTcpServerChannel);
			pTcpServer = (CCmmTcpServer*)pServer;
		}
		else
		{//为UDP服务器
#ifdef NOT_USE_XLANGUAGE
            CLogPrint::LogFormatString(g_pLogTracePrint, XLOGLEVEL_ERROR, "存在同名的UDP服务器(IP=%s  Port=%d)"
#else
            CLogPrint::LogFormatString(g_pLogTracePrint, XLOGLEVEL_ERROR, g_sLangTxt_ExistSameName/*L"存在同名的UDP服务器(IP=%s  Port=%d)"*/
#endif
                                       , pConfig->m_strLocalIP.GetString(), pConfig->m_nLocalPort);
		}
	}
	else
	{
		pTcpServer = new CCmmTcpServer();
		g_pCmmChannelCreateMngr->AddTail(pTcpServer);
		pTcpServerChannel->m_pNetServer = pTcpServer;
		pTcpServer->AddTail(pTcpServerChannel);
		pTcpServer->CreateServer( pConfig->m_strLocalIP, pConfig->m_nLocalPort, _T(""), 0);
	}

	return pTcpServer;
}

#ifndef _PSX_IDE_QT_
CCmmUdpServer* CCmmChannelCreateMngr::RegisterUdpServer(CCmmUdpServerChannel *pUdpServerChannel)
{
	ASSERT (pUdpServerChannel != NULL);

	CCmmUdpServerConfig *pConfig = pUdpServerChannel->m_pConfig;
	CCmmNetServer *pServer = g_pCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);
	UINT nClassID = 0;
	CCmmUdpServer *pUdpServer = NULL;

	if (pServer != NULL)
	{//找到相同的服务器
		nClassID = pServer->GetClassID();

		if (nClassID == CMMCLASSID_UDPSERVER)
		{//为TCP服务器
			pServer->AddTail(pUdpServerChannel);
			pUdpServer = (CCmmUdpServer*)pServer;
			pUdpServerChannel->m_pNetServer = pServer;
		}
		else
		{//为UDP服务器
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ExistSameName2/*L"存在同名的TCP服务器(IP=%s  Port=%d)"*/, pConfig->m_strLocalIP, pConfig->m_nLocalPort);
		}
	}
	else
	{
		pUdpServer = new CCmmUdpServer();
		g_pCmmChannelCreateMngr->AddTail(pUdpServer);
		pUdpServerChannel->m_pNetServer = pUdpServer;
		pUdpServer->AddTail(pUdpServerChannel);
		pUdpServer->CreateServer( pConfig->m_strLocalIP, pConfig->m_nLocalPort, pConfig->m_strMulticastIP, pConfig->m_nMulticastPort);
	}

	return pUdpServer;
}
#endif

void CCmmChannelCreateMngr::UnRegisterTcpServer(CCmmTcpServerChannel *pTcpServerChannel)
{
	CCmmTcpServerConfig *pConfig = pTcpServerChannel->m_pConfig;
	CCmmNetServer *pServer = g_pCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);

	if (pServer != NULL)
	{
		pServer->CloseServer(pTcpServerChannel);
	}

	return ;
}

#ifndef _PSX_IDE_QT_
void CCmmChannelCreateMngr::UnRegisterUdpServer(CCmmUdpServerChannel *pUdpServerChannel)
{
	CCmmUdpServerConfig *pConfig = pUdpServerChannel->m_pConfig;
	CCmmNetServer *pServer = g_pCmmChannelCreateMngr->FindNetServer(pConfig->m_strLocalIP, pConfig->m_nLocalPort);

	if (pServer != NULL)
	{
		pServer->CloseServer(pUdpServerChannel);
	}

	return ;
}
#endif

void CCmmChannelCreateMngr::UnRegisterServer(CCmmNetServer *pServer)
{
	POS pos = g_pCmmChannelCreateMngr->Find(pServer);

	if (pos == NULL)
	{
		delete pServer;
		return;
	}

	if (pServer->GetCount() == 0)
	{
		g_pCmmChannelCreateMngr->RemoveAt(pos);
		delete pServer;
	}
}


CCmmNetServer* CCmmChannelCreateMngr::FindNetServer(const CString &strIP, UINT nPort)
{
	CCmmNetServer *pFind = NULL;
	CCmmNetServer *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCmmNetServer*)GetNext(pos);

		if (p->IsEqual(strIP, nPort))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}
