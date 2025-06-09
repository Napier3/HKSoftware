#pragma once

#include "XSafenetBase.h"
#include "../UserDB/XUserTcpClient.h"

#define SAFENET_XUSER_CMD_EXIT      0
#define SAFENET_XUSER_CMD_NONE      1
#define SAFENET_XUSER_CMD_CONNECT   2
#define SAFENET_XUSER_CMD_LOGIN     3
#define SAFENET_XUSER_CMD_CATALOG   4
#define SAFENET_XUSER_CMD_GETINFOR  5

#define SAFENET_XUSER_RETSTATE_WAITE       -1
#define SAFENET_XUSER_RETSTATE_FAILED      0
#define SAFENET_XUSER_RETSTATE_SUCCES      1

//////////////////////////////////////////////////////////////////////////
//CSafenet_hasp
class CSafenet_XUser : public CSafenet_Base
{
private:
	CSafenet_XUser();
	virtual ~CSafenet_XUser();

	static long g_nSafenetXUserRef;
	static CSafenet_XUser *g_pSafenetXUser;

public:
	static CSafenet_XUser* Create(UINT nFetureID);
	static void Release();

	static BOOL hasp_has_catalog();
	static BOOL hasp_has_catalog(UINT nFetureID, BOOL bShowHaspMsg=TRUE);
	static CString hasp_get_develop(BOOL bHasTitle=FALSE);
	static CString hasp_get_ownership(BOOL bHasTitle=FALSE);
	static CString hasp_get_user_cop(BOOL bHasTitle=FALSE);
	static CString hasp_get_user_name(BOOL bHasTitle=FALSE);
	static CString hasp_get_user_psw();
	static CString hasp_get_sys_name();
	static CString hasp_get_test_macros();
	static CString hasp_get_template_authority_sn();
	static CString hasp_get_user_cop_sn();
	static CString hasp_get_safenet_sn();

	static void hasp_set_develop(const CString &strData);
	static void hasp_set_ownership(const CString &strData);
	static void hasp_set_user_cop(const CString &strData);
	static void hasp_set_user_name(const CString &strData);
	static void hasp_set_user_psw(const CString &strData);
	static void hasp_set_sys_name(const CString &strData);
	static void hasp_set_safenet_sn(const CString &strData);
	static void hasp_set_user_cop_sn(const CString &strData);
	static void hasp_set_test(const CString &strData);
	static void hasp_set_test_apps(const CString &strData);
	static void hasp_set_template_authority_sn(const CString &strData);

	static void hasp_get_develop(CString &strData);
	static void hasp_get_ownership(CString &strData);
	static void hasp_get_user_cop(CString &strData);
	static void hasp_get_user_name(CString &strData);
	static void hasp_get_user_psw(CString &strData);
	static void hasp_get_sys_name(CString &strData);


	static void hasp_write_infor();
	static void hasp_read_infor();

	static void SetMsgRcvWnd(CWnd *pMsgRcvWnd);
	static BOOL IsConnectSucc();

	static BOOL hasp_can_use_test_app(const CString &strTestApp);
	static BOOL hasp_can_use_test_macro(const CString &strTestMacro);
	static BOOL hasp_can_use_test(UINT nTestID);
	static BOOL hasp_is_power_sky();
	static BOOL hasp_is_power_sky(const CString &strCopSN);

private:
	BOOL login_catalog();

	CXUserTcpClient m_oXUserTcpClient;

	DWORD m_dwXUserTcpCmd;
	DWORD m_dwXUserTcpRetState;
	BOOL  m_bHasFetureID;

	//CWinThread *m_pXUserTcpThread;
	//static UINT XUserTcpThread(LPVOID pData);

	void XUserTcpClient_Catalog(CXUserTcpClient *pXUserTcpClient);
	void XUserTcpClient_Login(CXUserTcpClient *pXUserTcpClient);
	void XUserTcpClient_GetInfor(CXUserTcpClient *pXUserTcpClient);

public:
	void XUserTcpClient_Wait(DWORD dwXUserTcpState);
	void SetHasFetureID(BOOL bHas)	{	m_bHasFetureID = bHas;	}
	BOOL HasFetureID()				{	return m_bHasFetureID ;	}
	void DisconnectServer();
};
