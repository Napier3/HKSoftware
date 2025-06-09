#pragma once

extern unsigned char g_psz_def_develop[MAX_PATH];
extern unsigned char g_psz_def_ownership[MAX_PATH];
extern unsigned char g_psz_def_infor[MAX_PATH];
extern unsigned char g_psz_title_ownership[MAX_PATH];
extern unsigned char g_psz_title_develop[MAX_PATH];
extern unsigned char g_psz_title_user_cop[MAX_PATH];

//////////////////////////////////////////////////////////////////////////
class CSafenet_Login
{
private:
	CSafenet_Login(UINT nFetureID);
	virtual ~CSafenet_Login();

	static long g_nSafenetLoginRef;
	static CSafenet_Login *g_pSafenetLogin;

public:
	static CSafenet_Login* Create(UINT nFetureID);
	static void Release();

	static BOOL IsSafenetServer();

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

	static void hasp_get_develop(CString &strData);
	static void hasp_get_ownership(CString &strData);
	static void hasp_get_user_cop(CString &strData);
	static void hasp_get_user_name(CString &strData);
	static void hasp_get_user_psw(CString &strData);
	static void hasp_get_sys_name(CString &strData);

	static BOOL hasp_can_use_test_app(const CString &strTestApp);
	static BOOL hasp_can_use_test_macro(const CString &strTestMacro);
	static BOOL hasp_can_use_test(UINT nTestID);

	static BOOL hasp_is_power_sky();
	static BOOL hasp_is_power_sky(const CString &strCopSN);
	static BOOL hasp_is_overdue();
};

