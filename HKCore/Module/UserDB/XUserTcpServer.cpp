#include "StdAfx.h"
#include "XUserTcpServer.h"
#include "..\Sentinel LDK\SentinelLDKInterface.h"

#include "../Encrypt/EncryptTool.h"

// CServerCientSocket

CXUserTcpServerClient::CXUserTcpServerClient()
{
	m_pServerRef = NULL;

	m_pObjectRef = NULL;
}

CXUserTcpServerClient::~CXUserTcpServerClient()
{
}


void CXUserTcpServerClient::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pServerRef != NULL)
	{
		m_pServerRef->CloseTcpClient(this);
	}

	CSocket::OnClose(nErrorCode);
}

BOOL CXUserTcpServerClient::ProcessXUserCmd(CDvmData *pData)
{
	if (pData->m_strID == XUSER_CMD_LOGIN)
	{
		return ProcessXUserCmd_Login(pData);
	}

	if (pData->m_strID == XUSER_CMD_LOGOUT)
	{
		return ProcessXUserCmd_Logout(pData);
	}

	if (pData->m_strID == XUSER_CMD_GETINFOR)
	{
		return ProcessXUserCmd_GetInfor(pData);
	}

	if (pData->m_strID == XUSER_CMD_HASFETURE)
	{
		return ProcessXUserCmd_HasFetureID(pData);
	}

	return FALSE;
}

BOOL CXUserTcpServerClient::ProcessXUserCmd_Login(CDvmData *pData)
{
	CString strUserName, strPsw;
	strUserName = pData->GetAttrValue(XUSER_CMD_PARA_USERID);
	strPsw = pData->GetAttrValue(XUSER_CMD_PARA_USERPSW);
	CXUser *pCurrUser = CUserDBConstGlobal::Login(strUserName, strPsw);;
	ASSERT (m_pObjectRef != NULL);

	if (m_pObjectRef != NULL)
	{
		m_pObjectRef->m_pCurrUser = pCurrUser;
		m_pServerRef->UpdateTcpClient(this);
	}


	//如果用户不存在，则返回没有参数的通讯命令
	if (pCurrUser == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("login:id=%s   psw=%s error"), strUserName, strPsw);
		pData->m_strValue = _T("0");
	}
	else
	{
		pData->m_strValue = _T("1");
		pData->AddValue(XUSER_CMD_PARA_user_name, pCurrUser->m_strName);
	}

	SendXUserCmd(pData);

	return TRUE;
}

BOOL CXUserTcpServerClient::ProcessXUserCmd_Logout(CDvmData *pData)
{
	return FALSE;
}

BOOL CXUserTcpServerClient::ProcessXUserCmd_GetInfor(CDvmData *pData)
{
	if (Encrypt_IsUseRegisterFile())
	{
		pData->AddValue(XUSER_CMD_PARA_develop, g_pEncryptTool->GetDev());
		pData->AddValue(XUSER_CMD_PARA_ownership, g_pEncryptTool->GetOwnership());
		pData->AddValue(XUSER_CMD_PARA_user_cop, g_pEncryptTool->GetUserCop());
		pData->AddValue(XUSER_CMD_PARA_user_name, g_pEncryptTool->GetUser());
		pData->AddValue(XUSER_CMD_PARA_sys_name, g_pEncryptTool->GetSysName());

		//pData->AddValue(XUSER_CMD_PARA_safenet_sn, CSafenet_hasp::hasp_get_safenet_sn());
		//pData->AddValue(XUSER_CMD_PARA_user_cop_sn, CSafenet_hasp::hasp_get_user_cop_sn());
		//pData->AddValue(XUSER_CMD_PARA_test_apps, CSafenet_hasp::hasp_get_test_apps());
		//pData->AddValue(XUSER_CMD_PARA_test, CSafenet_hasp::hasp_get_test());
		//pData->AddValue(XUSER_CMD_PARA_authority_sn, CSafenet_hasp::hasp_get_template_authority_sn());
	}
	else
	{
		pData->AddValue(XUSER_CMD_PARA_develop, CSafenet_hasp::hasp_get_develop());
		pData->AddValue(XUSER_CMD_PARA_ownership, CSafenet_hasp::hasp_get_ownership());
		pData->AddValue(XUSER_CMD_PARA_user_cop, CSafenet_hasp::hasp_get_user_cop());
		pData->AddValue(XUSER_CMD_PARA_user_name, CSafenet_hasp::hasp_get_user_name());
		pData->AddValue(XUSER_CMD_PARA_sys_name, CSafenet_hasp::hasp_get_sys_name());

		pData->AddValue(XUSER_CMD_PARA_safenet_sn, CSafenet_hasp::hasp_get_safenet_sn());
		pData->AddValue(XUSER_CMD_PARA_user_cop_sn, CSafenet_hasp::hasp_get_user_cop_sn());
		pData->AddValue(XUSER_CMD_PARA_test_apps, CSafenet_hasp::hasp_get_test_apps());
		pData->AddValue(XUSER_CMD_PARA_test, CSafenet_hasp::hasp_get_test());
		pData->AddValue(XUSER_CMD_PARA_authority_sn, CSafenet_hasp::hasp_get_template_authority_sn());
	}


/*
	m_pSafenet_XUser->hasp_set_safenet_sn(pData->GetValueByID(XUSER_CMD_PARA_safenet_sn));
	m_pSafenet_XUser->hasp_set_user_cop_sn(pData->GetValueByID(XUSER_CMD_PARA_user_cop_sn));
	m_pSafenet_XUser->hasp_set_test_apps(pData->GetValueByID(XUSER_CMD_PARA_test_apps));
	m_pSafenet_XUser->hasp_set_test(pData->GetValueByID(XUSER_CMD_PARA_test));
*/

	SendXUserCmd(pData);

	return TRUE;
}

BOOL CXUserTcpServerClient::ProcessXUserCmd_HasFetureID(CDvmData *pData)
{
	ASSERT (m_pObjectRef != NULL);

	if (m_pObjectRef != NULL)
	{
		GetPeerName(m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("HasFetureID: from 【%s】【%d】"), m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nReotePort);
		GetSockName(m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nLocalPort);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("HasFetureID: from 【%s】【%d】"), m_pObjectRef->m_strRemoteIp, m_pObjectRef->m_nLocalPort);
		m_pServerRef->UpdateTcpClient(this);
	}

	CString strValue;
	strValue = pData->GetAttrValue(XUSER_CMD_PARA_FETUREID);
	UINT nFetureID = CString_To_long(strValue);

	if (m_pObjectRef != NULL)
	{
		m_pObjectRef->SetModuleID(nFetureID);
		m_pServerRef->UpdateTcpClient(this);
	}

	BOOL bHas = FALSE;
	
	if (Encrypt_IsUseRegisterFile())
	{
		bHas = Encrypt_IsEncrypt();

		if (m_pObjectRef->m_strRemoteIp != _T("172.21.23.191"))
		{
			bHas = FALSE;
		}
	}
	else
	{
		bHas = CSafenet_hasp::hasp_has_catalog(nFetureID, TRUE);
	}

	pData->m_strValue.Format(_T("%d"), bHas);
	SendXUserCmd(pData);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//

CXUserTcpServer::CXUserTcpServer(void)
{
	m_pListCtrlRef = NULL;
}

CXUserTcpServer::~CXUserTcpServer(void)
{
	POS pos = m_listTcpClient.GetHeadPosition();
	CXUserTcpServerClient *p = NULL;

	while (pos != NULL)
	{
		p = (CXUserTcpServerClient *)m_listTcpClient.GetNext(pos);
		p->Close();
	}

	m_listTcpClient.DeleteAll();
}

BOOL CXUserTcpServer::CreateServer(const CString &strIP, UINT nPort)
{
	if (!Create(nPort, SOCK_STREAM, strIP))
	{
		return FALSE;
	}


	if (!Listen())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXUserTcpServer::CloseServer()
{
	return TRUE;
}

BOOL CXUserTcpServer::IsServerClosed()
{
	return TRUE;
}


void CXUserTcpServer::OnAccept(int nErrorCode)
{
	CXUserTcpServerClientObject *pClientObj = new CXUserTcpServerClientObject();
	m_listClientObject.AddTail(pClientObj);
	
	CXUserTcpServerClient *pClientSocket = new CXUserTcpServerClient();
	pClientSocket->m_pObjectRef = pClientObj;
	pClientSocket->m_pServerRef = this;
	m_listTcpClient.AddTail(pClientSocket);

	Accept(*pClientSocket); 

	CSocket::OnAccept(nErrorCode);
}

void CXUserTcpServer::CloseTcpClient(CXUserTcpServerClient *pSockt)
{
	m_pListCtrlRef->DeleteObject(pSockt->m_pObjectRef);
	m_listClientObject.Delete(pSockt->m_pObjectRef);
	pSockt->Close();
	m_listTcpClient.Delete(pSockt);
}

void CXUserTcpServer::UpdateTcpClient(CXUserTcpServerClient *pSockt)
{
	m_pListCtrlRef->UpdateListCtrl(pSockt->m_pObjectRef);
}
