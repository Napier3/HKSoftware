#pragma once

#include "../MemBuffer/BufferBase.h"
#include "SafenetConfig.h"
#include "SafenetAuthoritysMngr.h"
#include "hasp_api.h"

/*//文本格式
POWSKY
0001
g_str_develop
g_str_ownership
g_str_user_cop
g_str_user_name
g_str_sys_name
g_str_user_cop_sn
g_str_test_apps
BYTE  m_byteAuthority[64]      64字节的权限信息
g_str_test_macros
g_str_template_authority_sn
*/

#define  SAFENET_AUTHORITY_BUF_LEN  64

#define SAFENET_VERSION_KEY    "POWSKY"
#define SAFENET_VERSION_0000   0X0000
#define SAFENET_VERSION_0001   0X0001

//20180525:授权时间    __int64  m_tmAuthority;  
#define SAFENET_VERSION_0002   0X0002

//2020-01-26：增加测试功能种类授权
#define SAFENET_VERSION_0003   0X0003

#define SAFENET_VERSION_CUR   SAFENET_VERSION_0003

//////////////////////////////////////////////////////////////////////////
//CSafenet_Base
class CSafenet_Base 
{
public:
	CSafenet_Base();
	virtual ~CSafenet_Base();

	CString g_strSafenet_Infor;
	CString m_strSafenet_SN;
	CString g_str_develop;
	CString g_str_ownership;
	CString g_str_user_cop;
	CString g_str_user_name;
	CString g_str_user_psw;
	CString g_str_sys_name;
	UINT g_nFetureID;

	 //用户编号，用于用户模板授权
	CString g_str_user_cop_sn; 

	//能够使用的测试仪接口程序id，PonovoVm.TestEngine$OnlyCtrl.DeviceCtrlApp$PqtVm.TestEngine$PqcVm.TestEngine
	CString g_str_test_apps;  

	//其他的权限
	BYTE  m_byteAuthority[SAFENET_AUTHORITY_BUF_LEN];

	SYSTEMTIME m_tmLimit;
	hasp_time_t  m_tmAuthority;  //20180525:授权时间，如果是无期限授权，则为0xFFFFFFFFFFFFFFFF

	DWORD m_dwVersion;

	//2020-01-26  
	//能够使用的测试测试功能id，PonovoVm.TestEngine$OnlyCtrl.DeviceCtrlApp$PqtVm.TestEngine$PqcVm.TestEngine
	CString g_str_test_macros;
	CString g_str_template_authority_sn;   //模板授权码
	
public:
	CString get_develop(BOOL bHasTitle=FALSE);
	CString get_ownership(BOOL bHasTitle=FALSE);
	CString get_user_cop(BOOL bHasTitle=FALSE);
	CString get_user_name(BOOL bHasTitle=FALSE);
	CString get_user_psw();
	CString get_sys_name();
	CString get_user_cop_sn();
	CString get_test_apps();
	CString get_test_macros();
	CString get_template_authority_sn();
	CString get_safenet_sn();
	SYSTEMTIME get_time_limit();

	void set_develop(const CString &strData);
	void set_ownership(const CString &strData);
	void set_user_cop(const CString &strData);
	void set_user_name(const CString &strData);
	void set_user_psw(const CString &strData);
	void set_sys_name(const CString &strData);
	void set_user_cop_sn(const CString &strData);
	void set_test_apps(const CString &strData);
	void set_test_macros(const CString &strData);
	void set_template_authority_sn(const CString &strData);
	void set_time_limit(SYSTEMTIME tmLimit);
	void set_test(const CString &strData);
	void set_safenet_sn(const CString &strData);

	void get_develop(CString &strData);
	void get_ownership(CString &strData);
	void get_user_cop(CString &strData);
	void get_user_name(CString &strData);
	void get_user_psw(CString &strData);
	void get_sys_name(CString &strData);
	void get_user_cop_sn(CString &strData);
	void get_test_apps(CString &strData);
	void get_test_macros(CString &strData);
	void get_template_authority_sn(CString &strData);
	BOOL get_time_limit(SYSTEMTIME &tmLimit);

	BOOL can_use_test_app(const CString &strTestApp);
	BOOL can_use_test_macro(const CString &strTestMacro);
	BOOL can_use_test(UINT nTestID);

	void read_infor(char *pBuffer);
	void init_infor();
	long get_infor_buf(char* &pInforBuf);

protected:
// 	void read_infor_old(CBufferBase &oBuffer);
// 	void read_infor_new(CBufferBase &oBuffer);
	char* read_infor_old(char *pBuffer);
	char* read_infor_new(char *pBuffer);
	void read_authority_test();
	void read_authority_testapp();
	void read_authority_testmacros();
	void init_authority_test();
	void init_authority_testapp();
	void init_authority_testmacro();
	BOOL is_tm_authority_FF();
	void set_tm_authority_FF();

public:
	BOOL has_authority(UINT nAuthority);
	BOOL has_authority(const CString &strAuthority);
	BOOL has_authority_test_macro(const CString &strAuthority);
	BOOL is_power_sky();
	BOOL is_power_sky(const CString &strCopSN);
	BOOL is_power_sky_register();
	BOOL is_power_sky_register(const CString &strAuthoritySN);
};
