// SttRemoteServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "SttRemoteServerSocket.h"
#include "..\..\..\Module\Socket\XPing.h"
#include "..\..\..\Cloud\SttCloudServerConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CSttRemoteServerSocket

CSttRemoteServerSocket::CSttRemoteServerSocket()
{

}

CSttRemoteServerSocket::~CSttRemoteServerSocket()
{

}

// CSttRemoteServerSocket 成员函数
BOOL CSttRemoteServerSocket::CreateServer(const CString &strIP, UINT nPort)
{
	if (!Create(nPort, SOCK_STREAM, strIP))
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("服务端Create失败【%s】【%d】"), strIP, nPort);
		return FALSE;
	}

	long nMaxClientCnt = CSttCloudServerConfig::GetMaxClientCount();
	if (!Listen(nMaxClientCnt))
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("服务端Listen失败【%s】【%d】"), strIP, nPort);
		return FALSE;
	}

	m_nMaxClientCount = nMaxClientCnt;
	m_strIPLocal = strIP;
	m_nPortLocal = nPort;

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("服务端成功【%s】【%d】"), strIP, nPort);
	return TRUE;
}

void CSttRemoteServerSocket::OnAccept(int nErrorCode)
{
	CSttRemoteServerClientSocket *pClientSocket = new CSttRemoteServerClientSocket();
	Accept(*pClientSocket); 

	long nPort = 0;
	GetIPPortFromSocket(pClientSocket->m_hSocket,pClientSocket->m_strIPRemote, nPort);
// 	pClientSocket->GetPeerName(pClientSocket->m_strIPRemote, nPort);
 	pClientSocket->m_nPortRemote = nPort;
	OnSttSktAccept((CSttSocketDataBase *)pClientSocket);

	CSocket::OnAccept(nErrorCode);
}

//如果是本地端断链，拼UnRegister命令应答远程端
//如果是远程端，拼Logout命令给本地
void CSttRemoteServerSocket::OnSttScktClose(CSttSocketDataBase *pSttSckt)
{

}
