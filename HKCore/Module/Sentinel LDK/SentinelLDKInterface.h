#pragma once

#include "hasp_api.h"
#include "XSafenetBase.h"

void hasp_get_develop(CString &strDevelop);
void hasp_get_ownership(CString &strOwnership);
void hasp_get_user_cop(CString &strUserCop);
void hasp_get_user_name(CString &strUserName);
void hasp_get_user_psw(CString &strUserPsw);
void hasp_get_sys_name(CString &strsys_name);

CString hasp_get_develop(BOOL bHasTitle=FALSE);
CString hasp_get_ownership(BOOL bHasTitle=FALSE);
CString hasp_get_user_cop(BOOL bHasTitle=FALSE);
CString hasp_get_user_name(BOOL bHasTitle=FALSE);
CString hasp_get_user_psw();
CString hasp_get_sys_name();

BOOL hasp_can_use_test_app(const CString &strTestApp);
BOOL hasp_can_use_test(UINT nTestID);

void hasp_ViewEntitlementInfor(UINT nFetureID);
CString hasp_get_login_error();

//////////////////////////////////////////////////////////////////////////
//CSafenet_hasp
class CSafenet_hasp : public CSafenet_Base
{
private:
	CSafenet_hasp(UINT nFetureID);
	virtual ~CSafenet_hasp();

	static long g_nSafenetHaspRef;
	static CSafenet_hasp *g_pSafenetHasp;
	static hasp_handle_t g_hasp_handle;
	static BOOL g_hasp_oa_server_mode;

public:
	static CSafenet_hasp* GetSafenet_hasp()		{	return g_pSafenetHasp;	}
	static CSafenet_hasp* Create(UINT nFetureID);
	static void Release();

	static BOOL hasp_has_catalog();
	static BOOL hasp_has_catalog(UINT nFetureID, BOOL bShowHaspMsg=TRUE);
	static CString hasp_get_develop(BOOL bHasTitle=FALSE);
	static CString hasp_get_ownership(BOOL bHasTitle=FALSE);
	static CString hasp_get_user_cop(BOOL bHasTitle=FALSE);
	static CString hasp_get_user_name(BOOL bHasTitle=FALSE);
	static CString hasp_get_user_psw();
	static CString hasp_get_sys_name();
	static CString hasp_get_user_cop_sn();
	static CString hasp_get_safenet_sn();
	static CString hasp_get_test();
	static CString hasp_get_test_apps();
	static CString hasp_get_test_macros();
	static CString hasp_get_template_authority_sn();

	static void hasp_set_develop(const CString &strData);
	static void hasp_set_ownership(const CString &strData);
	static void hasp_set_user_cop(const CString &strData);
	static void hasp_set_user_name(const CString &strData);
	static void hasp_set_user_psw(const CString &strData);
	static void hasp_set_sys_name(const CString &strData);
	static void hasp_set_user_cop_sn(const CString &strData);
	static void hasp_set_template_authority_sn(const CString &strData);
	static void hasp_set_time_limit(SYSTEMTIME tmLimit);

	static void hasp_get_develop(CString &strData);
	static void hasp_get_ownership(CString &strData);
	static void hasp_get_user_cop(CString &strData);
	static void hasp_get_user_name(CString &strData);
	static void hasp_get_user_psw(CString &strData);
	static void hasp_get_sys_name(CString &strData);
	static void hasp_get_user_cop_sn(CString &strData);
	static void hasp_get_template_authority_sn(CString &strData);
	static BOOL hasp_get_time_limit(SYSTEMTIME &tmLimit);

	static BOOL hasp_can_use_test_app(const CString &strTestApp);
	static BOOL hasp_can_use_test_macro(const CString &strTestMacro);
	static BOOL hasp_can_use_test(UINT nTestID);
	static BOOL hasp_is_power_sky();
	static BOOL hasp_is_power_sky(const CString &strCopSN);
	static BOOL hasp_is_power_sky_register();
	static BOOL hasp_is_power_sky_register(const CString &strAuthoritySN);
	static BOOL hasp_is_overdue();
	static BOOL hasp_has_time_authority();
	static BOOL hasp_get_curr_time(SYSTEMTIME &tmSys);
	static DWORD hasp_get_days_left();

	static CSafenetAuthoritys* hasp_get_authoritys_test();
	static CSafenetAuthoritys* hasp_get_authoritys_testapp();
	static CSafenetAuthoritys* hasp_get_authoritys_hasp_info();
	static CSafenetAuthoritys* hasp_get_authoritys_testmacros();

	static void hasp_write_infor();
	static void hasp_read_infor();

	static void hasp_set_oa_server_mode();
private:
	BOOL login_catalog();
	void init_hasp_login();
	void read_safenet_infor();
	BOOL hasp_get_curr_time(hasp_time_t *time);
	void time_hasp_to_system(hasp_time_t &time, SYSTEMTIME &tmSys); 
	void time_system_to_hasp(SYSTEMTIME &tmSys, hasp_time_t &time); 
	void time_hasp_to_system(); 
	void time_system_to_hasp(); 

	long hasp_infor_get_id(char **ppszBegin, char *pszKey);
	char* hasp_infor_get_id_str(char *pszBegin, char *pszKey,char *pszID);
};

