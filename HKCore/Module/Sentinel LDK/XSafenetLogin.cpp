// 程序说明：权限配置文件格式：
/*
<authoritys-mngr use-server="0">
	<authoritys name="测试功能授权" id="Test">
		<authority name="数字化变电站整站测试" id="1"/>
		<authority name="单装置多规约测试" id="2"/>
		<authority name="多装置单规约测试" id="3"/>
		<authority name="多装置多组测试" id="4"/>
		<authority name="模型映射工具DvmMap" id="5"/>
		<authority name="模型测试工具DvmTest" id="6"/>
		<authority name="多语言配置工具XLangDev" id="7"/>
		<authority name="测试模板管理" id="8"/>
		<authority name="测试模板授权" id="9"/>
		<authority name="测试任务测试" id="10"/>
	</authoritys>
	<authoritys name="测试仪使用权限" id="TestApp">
		<authority name="博电测试仪" id="PonovoVm.TestEngine"/>
		<authority name="昂立测试仪" id="OnlyCtrl.DeviceCtrlApp"/>
		<authority name="博电电能质量测试仪" id="PqtVm.TestEngine"/>
		<authority name="FLUKE标准源" id="Fluke.TestEngine"/>
	</authoritys>
	<authoritys name="软件授权" id="hasp_info">
		<authority name="自动测试AutoTest" id="100"/>
		<authority name="测试模板编辑ReportTemplateDev" id="102"/>
		<authority name="报告模板编辑GuideBookDev" id="101"/>
		<authority name="子模板开发GuidBookDev.Stxml" id="103"/>
		<authority name="规约模板开发PpDev" id="104"/>
		<authority name="传统规约引擎PpEngine" id="105"/>
		<authority name="61850MMS规约引擎PpMmsEngine" id="106"/>
		<authority name="软件狗授权AtsRegister" id="107"/>
		<authority name="服务器软件狗SafenetServer" id="108"/>
	</authoritys>
	<authoritys name="测试种类" id="TestMacros">
		<authority name="数字保护测试功能" id="RelayTest"/>
		<authority name="传统保护测试功能" id="JZRelayTest"/>
		<authority name="104规约测试" id="Protocl104Test"/>
		<authority name="PQT电能质量测试功能" id="PqtTest"/>
		<authority name="DT电压监测仪测试功能" id="DTTest"/>
		<authority name="PQC电能质量测试功能" id="PqcTest"/>
		<authority name="测试仪检测测试功能" id="TesterTest"/>
		<authority name="交流采样测试仪测试功能" id="TunkiaVmTest"/>
		<authority name="GZ故障指示器测试功能" id="GZTest"/>
		<authority name="Md配电终端测试功能" id="MdTest"/>
	</authoritys>

</authoritys-mngr>
*/
//流程说明：
//	1，CSafenet_hasp读取信息hasp_read_infor，初始化CSafenet_Base各成员的信息
// 2，权限判断：根据CSafenet_Base各成员的信息判断授权信息
//
// 作为客户端的流程
// 1，CSafenet_Login::hasp_has_catalog==>>CSafenet_XUser::hasp_has_catalog
// 2，在CXSafenetXUserDlg中读取
//               1）OnInitDialog==>>SAFENET_XUSER_CMD_CATALOG
//               2）OnTimer==>>XUserTcpClient_Wait(SAFENET_XUSER_CMD_CATALOG)
//               3）OnXUserCmdResult==>>SAFENET_XUSER_CMD_GETINFOR
//               4）OnTimer==>>XUserTcpClient_Wait(SAFENET_XUSER_CMD_GETINFOR)
//               5）OnXUserCmdResult==>>初始化XUSER_CMD_GETINFOR
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XSafenetLogin.h"
#include "XSafenetXUser.h"
#include "SentinelLDKInterface.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

void hasp_get_develop(CString &strDevelop)
{
	strDevelop = CSafenet_Login::hasp_get_develop();
}

void hasp_get_ownership(CString &strOwnership)
{
	strOwnership = CSafenet_Login::hasp_get_ownership();
}

void hasp_get_user_cop(CString &strUserCop)
{
	strUserCop = CSafenet_Login::hasp_get_user_cop();
}

void hasp_get_user_name(CString &strUserName)
{
	strUserName = CSafenet_Login::hasp_get_user_name();
}

void hasp_get_user_psw(CString &strUserPsw)
{
	strUserPsw = CSafenet_Login::hasp_get_user_psw();
}

void hasp_get_sys_name(CString &strsys_name)
{
	strsys_name = CSafenet_Login::hasp_get_sys_name();
}

CString hasp_get_develop(BOOL bHasTitle)
{
	return CSafenet_Login::hasp_get_develop(bHasTitle);
}

CString hasp_get_ownership(BOOL bHasTitle)
{
	return CSafenet_Login::hasp_get_ownership(bHasTitle);
}

CString hasp_get_user_cop(BOOL bHasTitle)
{
	return CSafenet_Login::hasp_get_user_cop(bHasTitle);
}

CString hasp_get_user_name(BOOL bHasTitle)
{
	return CSafenet_Login::hasp_get_user_name(bHasTitle);
}

CString hasp_get_user_psw()
{
	return CSafenet_Login::hasp_get_user_psw();
}

CString hasp_get_sys_name()
{
	return CSafenet_Login::hasp_get_sys_name();
}

BOOL hasp_can_use_test_app(const CString &strTestApp)
{
	return CSafenet_Login::hasp_can_use_test_app(strTestApp);
}

BOOL hasp_can_use_test(UINT nTestID)
{
	return CSafenet_Login::hasp_can_use_test(nTestID);
}

static BOOL g_n_hasp_ViewEntitlementInfor = FALSE;

void hasp_ViewEntitlementInfor(UINT nFetureID)
{
	if (g_n_hasp_ViewEntitlementInfor)
	{
		return;
	}

	g_n_hasp_ViewEntitlementInfor = TRUE;

	CString strMsg;
	
	strMsg = CSafenet_Login::hasp_get_sys_name();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), strMsg);

	hasp_get_ownership(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"), g_sLangTxt_RightsReserved /*_T("版权所有：%s")*/, strMsg);

	hasp_get_develop(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"),  g_sLangTxt_SystemDevelop/*_T("系统开发：%s")*/, strMsg);

	hasp_get_user_cop(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s %s"), g_sLangTxt_ClientUnit, strMsg);

	hasp_get_user_name(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s %s"),  g_sLangTxt_UserName/*_T("使用用户：%s")*/, strMsg);
}



//////////////////////////////////////////////////////////////////////////
//CSafenet_Login
long CSafenet_Login::g_nSafenetLoginRef = 0;
CSafenet_Login *CSafenet_Login::g_pSafenetLogin = NULL;


CSafenet_Login::CSafenet_Login(UINT nFetureID)
{
	CSafenetXMLRWKeys::Create();
	CSafenetConfig::Create(FALSE);

	if (CSafenetConfig::IsSafenetServer())
	{
		CSafenet_XUser::Create(nFetureID);
	}
	else
	{
		CSafenet_hasp::Create(nFetureID);
	}
}


CSafenet_Login::~CSafenet_Login()
{
	if (CSafenetConfig::IsSafenetServer())
	{
		CSafenet_XUser::Release();
	}
	else
	{
		CSafenet_hasp::Release();
	}

	CSafenetConfig::Release();
	CSafenetXMLRWKeys::Release();
}

CSafenet_Login* CSafenet_Login::Create(UINT nFetureID)
{
	CSafenetAuthorityXmlRWKeys::Create();
	CSafenetAuthoritysMngr::Create();

	g_nSafenetLoginRef++;

	if (g_nSafenetLoginRef == 1)
	{
		g_pSafenetLogin = new CSafenet_Login(nFetureID);
	}

	return g_pSafenetLogin;
}

void CSafenet_Login::Release()
{
	CSafenetAuthorityXmlRWKeys::Release();
	CSafenetAuthoritysMngr::Release();

	if (g_nSafenetLoginRef == 0)
	{
		return;
	}

	g_nSafenetLoginRef--;

	if (g_nSafenetLoginRef == 0)
	{
		delete g_pSafenetLogin;
		g_pSafenetLogin = NULL;
	}
}

BOOL CSafenet_Login::IsSafenetServer()
{
	return CSafenetConfig::IsSafenetServer();
}

BOOL CSafenet_Login::hasp_has_catalog()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_has_catalog();
	}
	else
	{
		return CSafenet_hasp::hasp_has_catalog();
	}
}

BOOL CSafenet_Login::hasp_has_catalog(UINT nFetureID, BOOL bShowLoginMsg)
{
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_has_catalog(nFetureID, bShowLoginMsg);
	}
	else
	{
		return CSafenet_hasp::hasp_has_catalog(nFetureID, bShowLoginMsg);
	}
}

CString CSafenet_Login::hasp_get_develop(BOOL bHasTitle)
{
	ASSERT (g_pSafenetLogin != NULL);
	CString strText;

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_develop(bHasTitle);
	}
	else
	{
		return CSafenet_hasp::hasp_get_develop(bHasTitle);
	}
}

CString CSafenet_Login::hasp_get_ownership(BOOL bHasTitle)
{
	ASSERT (g_pSafenetLogin != NULL);
	CString strText;

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_ownership(bHasTitle);
	}
	else
	{
		return CSafenet_hasp::hasp_get_ownership(bHasTitle);
	}
}

CString CSafenet_Login::hasp_get_user_cop(BOOL bHasTitle)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_cop(bHasTitle);
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_cop(bHasTitle);
	}
}

CString CSafenet_Login::hasp_get_user_name(BOOL bHasTitle)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_name(bHasTitle);
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_name(bHasTitle);
	}
}

CString CSafenet_Login::hasp_get_user_psw()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_psw();
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_psw();
	}
}


CString CSafenet_Login::hasp_get_sys_name()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_sys_name();
	}
	else
	{
		return CSafenet_hasp::hasp_get_sys_name();
	}
}

CString CSafenet_Login::hasp_get_test_macros()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_test_macros();
	}
	else
	{
		return CSafenet_hasp::hasp_get_test_macros();
	}
}


CString CSafenet_Login::hasp_get_template_authority_sn()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_template_authority_sn();
	}
	else
	{
		return CSafenet_hasp::hasp_get_template_authority_sn();
	}
}

CString CSafenet_Login::hasp_get_user_cop_sn()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_cop_sn();
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_cop_sn();
	}
}

CString CSafenet_Login::hasp_get_safenet_sn()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_safenet_sn();
	}
	else
	{
		return CSafenet_hasp::hasp_get_safenet_sn();
	}
}

void CSafenet_Login::hasp_set_develop(const CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_set_develop(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_set_develop(strData);
	}
}

void CSafenet_Login::hasp_set_ownership(const CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_set_ownership(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_set_ownership(strData);
	}
}

void CSafenet_Login::hasp_set_user_cop(const CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_set_user_cop(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_set_user_cop(strData);
	}
}

void CSafenet_Login::hasp_set_user_name(const CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_set_user_name(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_set_user_name(strData);
	}
}

void CSafenet_Login::hasp_set_user_psw(const CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_set_user_psw(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_set_user_psw(strData);
	}
}


void CSafenet_Login::hasp_get_develop(CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_develop(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_get_develop(strData);
	}
}

void CSafenet_Login::hasp_get_ownership(CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_ownership(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_get_ownership(strData);
	}
}

void CSafenet_Login::hasp_get_user_cop(CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_cop(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_cop(strData);
	}
}

void CSafenet_Login::hasp_get_user_name(CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_name(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_name(strData);
	}
}

void CSafenet_Login::hasp_get_user_psw(CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);
	
	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_user_psw(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_get_user_psw(strData);
	}
}

void CSafenet_Login::hasp_get_sys_name(CString &strData)
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_get_sys_name(strData);
	}
	else
	{
		return CSafenet_hasp::hasp_get_sys_name(strData);
	}
}

BOOL CSafenet_Login::hasp_can_use_test_app(const CString &strTestApp)
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_can_use_test_app(strTestApp);
	}
	else
	{
		return CSafenet_hasp::hasp_can_use_test_app(strTestApp);
	}
}

BOOL CSafenet_Login::hasp_can_use_test_macro(const CString &strTestMacro)
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_can_use_test_macro(strTestMacro);
	}
	else
	{
		return CSafenet_hasp::hasp_can_use_test_macro(strTestMacro);
	}
}

BOOL CSafenet_Login::hasp_can_use_test(UINT nTestID)
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_can_use_test(nTestID);
	}
	else
	{
		return CSafenet_hasp::hasp_can_use_test(nTestID);
	}
}


BOOL CSafenet_Login::hasp_is_power_sky()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_is_power_sky();
	}
	else
	{
		return CSafenet_hasp::hasp_is_power_sky();
	}
}

BOOL CSafenet_Login::hasp_is_power_sky(const CString &strCopSN)
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return CSafenet_XUser::hasp_is_power_sky(strCopSN);
	}
	else
	{
		return CSafenet_hasp::hasp_is_power_sky(strCopSN);
	}
}

BOOL CSafenet_Login::hasp_is_overdue()
{
	ASSERT (g_pSafenetLogin != NULL);

	if (CSafenetConfig::IsSafenetServer())
	{
		return FALSE;
	}
	
	if (!CSafenet_Login::hasp_has_catalog())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, g_sLangTxt_NotAuthorized);
		return TRUE;
	}

	if (!CSafenet_hasp::hasp_has_time_authority())
	{
		return FALSE;
	}

	DWORD dwDaysLeft = CSafenet_hasp::hasp_get_days_left();

	if (dwDaysLeft > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("你的授权期限还剩 %d  天"), dwDaysLeft);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("你的授权期限已经到期"));
	}

	return (dwDaysLeft == 0);
}

