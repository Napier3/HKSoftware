#include "stdafx.h"

#include "SttClientSocket.h"
#include "../../../Engine/SttTestEngineBase.h"

#ifndef NOT_USE_XLANGUAGE

#include "../../../../../Module/XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttClientSocket::CSttClientSocket()
{

}

CSttClientSocket::~CSttClientSocket()
{

}

BOOL CSttClientSocket::ConnectServer()
{
#ifndef _PSX_QT_LINUX_
	InitSocket();
#endif
	SetReceiveBuffLen( STT_FILECMD_MAX_LEN );
	Create(SOCK_STREAM);
	InitSocketClient(20);
	BOOL bRet = Connect(m_strIPRemote.GetString(), m_nPortRemote);
	#ifdef NOT_USE_XLANGUAGE
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接服务器[%s][%d]成功"), m_strIPRemote.GetString(), m_nPortRemote);
	}
	#else
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ConServerSucc.GetString(), m_strIPRemote.GetString(), m_nPortRemote);
	}
	#endif
	return bRet;
}

BOOL CSttClientSocket::ConnectServer(const CString &strIPServer,long nPort)
{//本地或远程测试端，连接成功后设置SttLocalTestEngine的RefSocket

	char pszIPServer[64] = {0};
	CString_to_char(strIPServer,pszIPServer);

	m_strIPRemote = strIPServer;
	m_nPortRemote = nPort;

	return ConnectServer();
}

void CSttClientSocket::OnClose(int nErrorCode)
{
	CSttTestEngineBase *pEngine = GetTestEngine();

	if(pEngine != NULL)
	{
		pEngine->OnSocketClose(this);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("nErrorCode=%d[CSttClientSocket::OnClose]."),nErrorCode);
	}
//	OnSocketClose(nErrorCode);
}

void CSttClientSocket::CloseSocket()
{
	Close();

	CSttClientSocketBase::CloseSocket();
}

long CSttClientSocket::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}