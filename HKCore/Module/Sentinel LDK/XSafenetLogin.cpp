// ����˵����Ȩ�������ļ���ʽ��
/*
<authoritys-mngr use-server="0">
	<authoritys name="���Թ�����Ȩ" id="Test">
		<authority name="���ֻ����վ��վ����" id="1"/>
		<authority name="��װ�ö��Լ����" id="2"/>
		<authority name="��װ�õ���Լ����" id="3"/>
		<authority name="��װ�ö������" id="4"/>
		<authority name="ģ��ӳ�乤��DvmMap" id="5"/>
		<authority name="ģ�Ͳ��Թ���DvmTest" id="6"/>
		<authority name="���������ù���XLangDev" id="7"/>
		<authority name="����ģ�����" id="8"/>
		<authority name="����ģ����Ȩ" id="9"/>
		<authority name="�����������" id="10"/>
	</authoritys>
	<authoritys name="������ʹ��Ȩ��" id="TestApp">
		<authority name="���������" id="PonovoVm.TestEngine"/>
		<authority name="����������" id="OnlyCtrl.DeviceCtrlApp"/>
		<authority name="�����������������" id="PqtVm.TestEngine"/>
		<authority name="FLUKE��׼Դ" id="Fluke.TestEngine"/>
	</authoritys>
	<authoritys name="�����Ȩ" id="hasp_info">
		<authority name="�Զ�����AutoTest" id="100"/>
		<authority name="����ģ��༭ReportTemplateDev" id="102"/>
		<authority name="����ģ��༭GuideBookDev" id="101"/>
		<authority name="��ģ�忪��GuidBookDev.Stxml" id="103"/>
		<authority name="��Լģ�忪��PpDev" id="104"/>
		<authority name="��ͳ��Լ����PpEngine" id="105"/>
		<authority name="61850MMS��Լ����PpMmsEngine" id="106"/>
		<authority name="�������ȨAtsRegister" id="107"/>
		<authority name="�����������SafenetServer" id="108"/>
	</authoritys>
	<authoritys name="��������" id="TestMacros">
		<authority name="���ֱ������Թ���" id="RelayTest"/>
		<authority name="��ͳ�������Թ���" id="JZRelayTest"/>
		<authority name="104��Լ����" id="Protocl104Test"/>
		<authority name="PQT�����������Թ���" id="PqtTest"/>
		<authority name="DT��ѹ����ǲ��Թ���" id="DTTest"/>
		<authority name="PQC�����������Թ���" id="PqcTest"/>
		<authority name="�����Ǽ����Թ���" id="TesterTest"/>
		<authority name="�������������ǲ��Թ���" id="TunkiaVmTest"/>
		<authority name="GZ����ָʾ�����Թ���" id="GZTest"/>
		<authority name="Md����ն˲��Թ���" id="MdTest"/>
	</authoritys>

</authoritys-mngr>
*/
//����˵����
//	1��CSafenet_hasp��ȡ��Ϣhasp_read_infor����ʼ��CSafenet_Base����Ա����Ϣ
// 2��Ȩ���жϣ�����CSafenet_Base����Ա����Ϣ�ж���Ȩ��Ϣ
//
// ��Ϊ�ͻ��˵�����
// 1��CSafenet_Login::hasp_has_catalog==>>CSafenet_XUser::hasp_has_catalog
// 2����CXSafenetXUserDlg�ж�ȡ
//               1��OnInitDialog==>>SAFENET_XUSER_CMD_CATALOG
//               2��OnTimer==>>XUserTcpClient_Wait(SAFENET_XUSER_CMD_CATALOG)
//               3��OnXUserCmdResult==>>SAFENET_XUSER_CMD_GETINFOR
//               4��OnTimer==>>XUserTcpClient_Wait(SAFENET_XUSER_CMD_GETINFOR)
//               5��OnXUserCmdResult==>>��ʼ��XUSER_CMD_GETINFOR
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
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"), g_sLangTxt_RightsReserved /*_T("��Ȩ���У�%s")*/, strMsg);

	hasp_get_develop(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"),  g_sLangTxt_SystemDevelop/*_T("ϵͳ������%s")*/, strMsg);

	hasp_get_user_cop(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s %s"), g_sLangTxt_ClientUnit, strMsg);

	hasp_get_user_name(strMsg);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s %s"),  g_sLangTxt_UserName/*_T("ʹ���û���%s")*/, strMsg);
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�����Ȩ���޻�ʣ %d  ��"), dwDaysLeft);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�����Ȩ�����Ѿ�����"));
	}

	return (dwDaysLeft == 0);
}

