#include "StdAfx.h"
#include "XUserTcpClient.h"
#include "..\Sentinel LDK\SentinelLDKInterface.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXUserTcpClient::CXUserTcpClient(void)
{

}

CXUserTcpClient::~CXUserTcpClient(void)
{

}


BOOL CXUserTcpClient::ConnectServer(const CString &strIP, UINT nPort)
{
	m_bIsTcpConnectSucc = TRUE;

	if (!Create())
	{
		m_bIsTcpConnectSucc = FALSE;
	}

	if (m_bIsTcpConnectSucc)
	{
		if (!Connect(strIP, nPort))
		{
			m_bIsTcpConnectSucc = FALSE;
		}
	}

	if (!m_bIsTcpConnectSucc)
	{
		Close();
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ConServerFail/*_T("连接服务器【%s】【%d】失败")*/
			, CSafenetConfig::GetServerIP(), CSafenetConfig::GetServerPort());
	}

	return m_bIsTcpConnectSucc;
}

void CXUserTcpClient::DisConnectServer()
{
	Close();
	m_bIsTcpConnectSucc = FALSE;
}

BOOL CXUserTcpClient::ProcessXUserCmd(CDvmData *pData)
{
	ASSERT (m_pMsgRcvWnd != NULL);
	m_pMsgRcvWnd->SendMessage(WM_XUSERTCPCLIENT_CMD, (LPARAM)pData, (WPARAM)pData);
// 	if (pData->m_strID == XUSER_CMD_LOGIN)
// 	{
// 		return ProcessXUserCmd_Login(pData);
// 	}
// 
// 	if (pData->m_strID == XUSER_CMD_LOGOUT)
// 	{
// 		return ProcessXUserCmd_Logout(pData);
// 	}
// 
// 	if (pData->m_strID == XUSER_CMD_GETINFOR)
// 	{
// 		return ProcessXUserCmd_GetInfor(pData);
// 	}
// 
// 	if (pData->m_strID == XUSER_CMD_HASFETURE)
// 	{
// 		return ProcessXUserCmd_HasFetureID(pData);
// 	}

	return FALSE;
}

BOOL CXUserTcpClient::ProcessXUserCmd_Login(CDvmData *pData)
{
	
	return TRUE;
}

BOOL CXUserTcpClient::ProcessXUserCmd_Logout(CDvmData *pData)
{
	return FALSE;
}

BOOL CXUserTcpClient::ProcessXUserCmd_GetInfor(CDvmData *pData)
{
	return TRUE;
}


BOOL CXUserTcpClient::ProcessXUserCmd_HasFetureID(CDvmData *pData)
{
	return TRUE;
}

void CXUserTcpClient::OnClose(int nErrorCode)
{
	m_bIsTcpConnectSucc = FALSE;

	CXUserTcpClientBase::OnClose(nErrorCode);
}
