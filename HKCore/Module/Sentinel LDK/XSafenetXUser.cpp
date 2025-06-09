// XSafenetXUser.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XSafenetXUser.h"
#include "..\System\TickCount32.h"
#include "XSafenetXUserDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void hasp_ViewEntitlementInfor(UINT nFetureID);

//////////////////////////////////////////////////////////////////////////
//CSafenet_XUser
long CSafenet_XUser::g_nSafenetXUserRef = 0;
CSafenet_XUser *CSafenet_XUser::g_pSafenetXUser = NULL;


CSafenet_XUser::CSafenet_XUser()
{
	m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
	m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
	m_bHasFetureID = FALSE;
	//m_pXUserTcpThread = AfxBeginThread(XUserTcpThread,this);
	//m_pXUserTcpThread->m_bAutoDelete = TRUE;
}

void CSafenet_XUser::hasp_read_infor()
{

}

void CSafenet_XUser::SetMsgRcvWnd(CWnd *pMsgRcvWnd)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->m_oXUserTcpClient.SetMsgRcvWnd(pMsgRcvWnd);
}

CSafenet_XUser::~CSafenet_XUser()
{

}

CSafenet_XUser* CSafenet_XUser::Create(UINT nFetureID)
{
	g_nSafenetXUserRef++;

	if (g_nSafenetXUserRef == 1)
	{
		g_pSafenetXUser = new CSafenet_XUser();
		g_pSafenetXUser->g_nFetureID = nFetureID;
	}

	return g_pSafenetXUser;
}

void CSafenet_XUser::Release()
{
	if (g_nSafenetXUserRef == 0)
	{
		return;
	}

	g_nSafenetXUserRef--;

	if (g_nSafenetXUserRef == 0)
	{
		g_pSafenetXUser->XUserTcpClient_Wait(SAFENET_XUSER_CMD_EXIT);
		delete g_pSafenetXUser;
		g_pSafenetXUser = NULL;
	}
}

BOOL CSafenet_XUser::login_catalog()
{
	return FALSE;
}

BOOL CSafenet_XUser::hasp_has_catalog()
{
	ASSERT (g_pSafenetXUser != NULL);

	if (g_pSafenetXUser == NULL)
	{
		return FALSE;
	}

	return CSafenet_XUser::hasp_has_catalog(g_pSafenetXUser->g_nFetureID);
}

BOOL CSafenet_XUser::hasp_has_catalog(UINT nFetureID, BOOL bShowXUserMsg)
{
	ASSERT (g_pSafenetXUser != NULL);

	g_pSafenetXUser->SetHasFetureID(FALSE);
	CXSafenetXUserDlg dlg(AfxGetMainWnd());
	g_pSafenetXUser->g_nFetureID = nFetureID;
	dlg.m_pSafenet_XUser = g_pSafenetXUser;

	if (dlg.DoModal() == IDOK)
	{
		hasp_ViewEntitlementInfor(nFetureID);

		return TRUE;
	}
	else
	{
		return FALSE;
	}

	g_pSafenetXUser->XUserTcpClient_Wait(SAFENET_XUSER_CMD_CATALOG);

	if (g_pSafenetXUser->m_dwXUserTcpRetState == SAFENET_XUSER_RETSTATE_FAILED)
	{
		return FALSE;
	}

	//g_pSafenetXUser->XUserTcpClient_Wait(SAFENET_XUSER_CMD_GETINFOR);

	if (g_pSafenetXUser->m_dwXUserTcpRetState == SAFENET_XUSER_RETSTATE_FAILED)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

CString CSafenet_XUser::hasp_get_develop(BOOL bHasTitle)
{
	ASSERT (g_pSafenetXUser != NULL);
	CString strText;

	return g_pSafenetXUser->get_develop(bHasTitle);
}

CString CSafenet_XUser::hasp_get_ownership(BOOL bHasTitle)
{
	ASSERT (g_pSafenetXUser != NULL);
	CString strText;

	return g_pSafenetXUser->get_ownership(bHasTitle);
}

CString CSafenet_XUser::hasp_get_user_cop(BOOL bHasTitle)
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->get_user_cop(bHasTitle);
}

CString CSafenet_XUser::hasp_get_user_name(BOOL bHasTitle)
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->get_user_name(bHasTitle);
}

CString CSafenet_XUser::hasp_get_user_psw()
{
	ASSERT (g_pSafenetXUser != NULL);

	return g_pSafenetXUser->get_user_psw();
}


CString CSafenet_XUser::hasp_get_sys_name()
{
	ASSERT (g_pSafenetXUser != NULL);

	return g_pSafenetXUser->get_sys_name();
}

CString CSafenet_XUser::hasp_get_test_macros()
{
	ASSERT (g_pSafenetXUser != NULL);

	return g_pSafenetXUser->get_test_macros();
}

CString CSafenet_XUser::hasp_get_template_authority_sn()
{
	ASSERT (g_pSafenetXUser != NULL);

	return g_pSafenetXUser->get_template_authority_sn();
}

CString CSafenet_XUser::hasp_get_user_cop_sn()
{
	ASSERT (g_pSafenetXUser != NULL);

	return g_pSafenetXUser->get_user_cop_sn();
}

CString CSafenet_XUser::hasp_get_safenet_sn()
{
	ASSERT (g_pSafenetXUser != NULL);

	return g_pSafenetXUser->get_safenet_sn();
}

void CSafenet_XUser::hasp_set_develop(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_develop(strData);
}

void CSafenet_XUser::hasp_set_ownership(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_ownership(strData);
}

void CSafenet_XUser::hasp_set_user_cop(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_user_cop(strData);
}

void CSafenet_XUser::hasp_set_user_name(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_user_name(strData);
}

void CSafenet_XUser::hasp_set_user_psw(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_user_psw(strData);
}


void CSafenet_XUser::hasp_set_sys_name(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_sys_name(strData);
}

void CSafenet_XUser::hasp_set_safenet_sn(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_safenet_sn(strData);
}

void CSafenet_XUser::hasp_set_user_cop_sn(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_user_cop_sn(strData);
}

void CSafenet_XUser::hasp_set_test(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_test(strData);
}

void CSafenet_XUser::hasp_set_test_apps(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_test_apps(strData);
}

void CSafenet_XUser::hasp_set_template_authority_sn(const CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->set_template_authority_sn(strData);
}

void CSafenet_XUser::hasp_get_develop(CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->get_develop(strData);
}

void CSafenet_XUser::hasp_get_ownership(CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->get_ownership(strData);
}

void CSafenet_XUser::hasp_get_user_cop(CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->get_user_cop(strData);
}

void CSafenet_XUser::hasp_get_user_name(CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->get_user_name(strData);
}

void CSafenet_XUser::hasp_get_user_psw(CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->get_user_psw(strData);
}

void CSafenet_XUser::hasp_get_sys_name(CString &strData)
{
	ASSERT (g_pSafenetXUser != NULL);
	g_pSafenetXUser->get_sys_name(strData);
}

BOOL CSafenet_XUser::hasp_can_use_test_app(const CString &strTestApp)
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->can_use_test_app(strTestApp);
}


BOOL CSafenet_XUser::hasp_can_use_test_macro(const CString &strTestMacro)
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->can_use_test_macro(strTestMacro);
}

BOOL CSafenet_XUser::hasp_can_use_test(UINT nTestID)
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->can_use_test(nTestID);
}

BOOL CSafenet_XUser::hasp_is_power_sky()
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->is_power_sky();
}

BOOL CSafenet_XUser::hasp_is_power_sky(const CString &strCopSN)
{
	ASSERT (g_pSafenetXUser != NULL);
	return g_pSafenetXUser->is_power_sky(strCopSN);
}

/*
UINT CSafenet_XUser::XUserTcpThread(LPVOID pData)
{
	CSafenet_XUser *pXUser = (CSafenet_XUser*)pData;
	CXUserTcpClient oXUserTcpClient;
	CTickCount32 oTickCount32;

	if (!AfxSocketInit())
	{
		return FALSE;
	}

	if (!AfxOleInit())
	{
		return FALSE;
	}

	while (TRUE)
	{
		if (pXUser->m_dwXUserTcpCmd == SAFENET_XUSER_CMD_EXIT)
		{
			break;
		}

		switch (pXUser->m_dwXUserTcpCmd)
		{
		case SAFENET_XUSER_CMD_NONE:
			Sleep(50);
			break;

		case SAFENET_XUSER_CMD_CONNECT:
			oXUserTcpClient.ConnectServer(CSafenetConfig::GetServerIP(), CSafenetConfig::GetServerPort());
			break;

		case SAFENET_XUSER_CMD_CATALOG:
			pXUser->XUserTcpClient_Catalog(&oXUserTcpClient);
			pXUser->m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
			break;

		case SAFENET_XUSER_CMD_GETINFOR:
			pXUser->XUserTcpClient_GetInfor(&oXUserTcpClient);
			pXUser->m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
			break;

		case SAFENET_XUSER_CMD_LOGIN:
			pXUser->XUserTcpClient_Login(&oXUserTcpClient);
			pXUser->m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
			break;

		}

	}

	pXUser->m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_SUCCES;

	return 0;
}
*/

void CSafenet_XUser::XUserTcpClient_Catalog(CXUserTcpClient *pXUserTcpClient)
{
	if (!pXUserTcpClient->IsTcpConnectSucc())
	{
		pXUserTcpClient->ConnectServer(CSafenetConfig::GetServerIP(), CSafenetConfig::GetServerPort());
	}

	if (!pXUserTcpClient->IsTcpConnectSucc())
	{
		m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
		return;
	}

	if (!pXUserTcpClient->hasp_has_catalog(g_nFetureID))
	{
		m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
		return;
	}

// 	CTickCount32 oTickCount32;
// 
// 	while (TRUE)
// 	{
// 		if (pXUserTcpClient->IsSendCmdFinished())
// 		{
// 			long nRet = pXUserTcpClient->GetSendCmdResult();
// 
// 			if (nRet != 0)
// 			{
// 				m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_SUCCES;
// 			}
// 			else
// 			{
// 				m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
// 			}
// 
// 			break;
// 		}
// 		
// 		if (oTickCount32.GetTickCountLong(FALSE) > 15000)
// 		{
// 			m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
// 			break;
// 		}
// 	}
}

void CSafenet_XUser::XUserTcpClient_Login(CXUserTcpClient *pXUserTcpClient)
{

}

void CSafenet_XUser::XUserTcpClient_GetInfor(CXUserTcpClient *pXUserTcpClient)
{
	if (!pXUserTcpClient->IsTcpConnectSucc())
	{
		pXUserTcpClient->ConnectServer(CSafenetConfig::GetServerIP(), CSafenetConfig::GetServerPort());
	}

	if (!pXUserTcpClient->IsTcpConnectSucc())
	{
		m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
		return;
	}

	if (!pXUserTcpClient->hasp_get_infor())
	{
		m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_FAILED;
		return;
	}
}

void CSafenet_XUser::XUserTcpClient_Wait(DWORD dwXUserTcpState)
{
	m_dwXUserTcpRetState = SAFENET_XUSER_RETSTATE_WAITE;
	m_dwXUserTcpCmd    = dwXUserTcpState;

	switch (m_dwXUserTcpCmd)
	{
	case SAFENET_XUSER_CMD_NONE:
		Sleep(50);
		break;

	case SAFENET_XUSER_CMD_CONNECT:
		m_oXUserTcpClient.ConnectServer(CSafenetConfig::GetServerIP(), CSafenetConfig::GetServerPort());
		break;

	case SAFENET_XUSER_CMD_CATALOG:
		XUserTcpClient_Catalog(&m_oXUserTcpClient);
		m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
		break;

	case SAFENET_XUSER_CMD_GETINFOR:
		XUserTcpClient_GetInfor(&m_oXUserTcpClient);
		m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
		break;

	case SAFENET_XUSER_CMD_LOGIN:
		XUserTcpClient_Login(&m_oXUserTcpClient);
		m_dwXUserTcpCmd = SAFENET_XUSER_CMD_NONE;
		break;

	}
}

BOOL CSafenet_XUser::IsConnectSucc()
{
	if (g_pSafenetXUser == NULL)
	{
		return FALSE;
	}

	return g_pSafenetXUser->m_oXUserTcpClient.IsTcpConnectSucc();
}

void CSafenet_XUser::DisconnectServer()
{
	m_oXUserTcpClient.DisConnectServer();
}

