#include "stdafx.h"
#include "SttTestClientUser.h"
#include <ctime>  

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttTestClientUser::CSttTestClientUser()
{
	m_pRefSttSckt = NULL;
}

CSttTestClientUser::~CSttTestClientUser()
{

}

CString CSttTestClientUser::os()
{
	return GetValueByID(ID_STT_USER_ATTR_os);
}

void CSttTestClientUser::os(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_os, strValue);
}

CString CSttTestClientUser::id_soft()
{
	return GetValueByID(ID_STT_USER_ATTR_id_soft);
}

void CSttTestClientUser::id_soft(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_id_soft, strValue);
}

CString CSttTestClientUser::ver_soft()
{
	return GetValueByID(ID_STT_USER_ATTR_ver_soft);
}

void CSttTestClientUser::ver_soft(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_ver_soft, strValue);
}

CString CSttTestClientUser::ID_Terminal()
{
	return GetValueByID(ID_STT_USER_ATTR_ID_Terminal);
}

void CSttTestClientUser::ID_Terminal(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_ID_Terminal, strValue);
}

CString CSttTestClientUser::SN_TestApp()
{
	return GetValueByID(ID_STT_USER_ATTR_SN_TestApp);
}

void CSttTestClientUser::SN_TestApp(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_SN_TestApp, strValue);
}

CString CSttTestClientUser::Code_Register()
{
	return GetValueByID(ID_STT_USER_ATTR_Code_Register);
}

void CSttTestClientUser::Code_Register(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_Code_Register, strValue);
}

CString CSttTestClientUser::Name_Cop()
{
	return GetValueByID(ID_STT_USER_ATTR_Name_Cop);
}

void CSttTestClientUser::Name_Cop(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_Name_Cop, strValue);
}

CString CSttTestClientUser::Name_User()
{
	return GetValueByID(ID_STT_USER_ATTR_Name_User);
}

void CSttTestClientUser::Name_User(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_Name_User, strValue);
}

CString CSttTestClientUser::IP_User()
{
	return GetValueByID(ID_STT_USER_ATTR_IP_User);
}

void CSttTestClientUser::IP_User(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_IP_User, strValue);
}

DWORD CSttTestClientUser::ID_Tester()
{
	DWORD nValue = 0;
	GetValueByID(STT_CMD_PARA_IDTESTER,nValue);
	return nValue;
}

void CSttTestClientUser::ID_Tester(DWORD nValue)
{
	SetValue(STT_CMD_PARA_IDTESTER, nValue);

	if((m_pRefSttSckt != NULL) && (nValue != 0))
	{
		m_pRefSttSckt->m_nIDTester = nValue;
	}
}

void CSttTestClientUser::SetLogInTime()
{
//  	SYSTEMTIME tmSys;
//  	::GetLocalTime(&tmSys);
 	CString strLogInTime;
// 	CTime tm(tmSys);
// 	double dTime = (double)tm.GetTime();

	std::time_t tmLocal = std::time(NULL);
// 	struct tm *pUtcTime = std::gmtime(&tmLocal);
// 	std::time_t tmUtcTime = mktime(pUtcTime); 
	long nTime = tmLocal;
	strLogInTime.Format("%ld",nTime);

// 	long nZone = 0;
// #ifndef _PSX_QT_LINUX_
// 	TIME_ZONE_INFORMATION tz;  
//	GetTimeZoneInformation(&tz);
// 	nZone = -tz.Bias/60;
// #endif
// 
// 	strLogInTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d [%d]"), tm.wYear, tm.wMonth, tm.wDay
// 		, tm.wHour, tm.wMinute, tm.wSecond,nZone);
	SetValue(STT_CMD_PARA_LogInTime, strLogInTime);
}

BOOL CSttTestClientUser::IsEqual(CBaseObject* pObj)
{
	CSttTestClientUser *pUser = (CSttTestClientUser *)pObj;

	if (id_soft() != pUser->id_soft())
	{
		return FALSE;
	}
	if (ID_Terminal() != pUser->ID_Terminal())
	{
		return FALSE;
	}
	if (SN_TestApp() != pUser->SN_TestApp())
	{
		return FALSE;
	}
	if (Name_Cop() != pUser->Name_Cop())
	{
		return FALSE;
	}
	if (Name_User() != pUser->Name_User())
	{
		return FALSE;
	}

	return TRUE;
}

DWORD CSttTestClientUser::GetIDTest()
{
	return ID_Tester();
}

BOOL CSttTestClientUser::HasAuthority(const CString &strModuleID)
{
	long nValue = 0;
	GetValueByID(strModuleID, nValue);

	return (nValue != 0);
}

void CSttTestClientUser::SetAuthority(const CString &strModuleID, long nValue)
{
	SetValue(strModuleID, nValue);
}

void CSttTestClientUser::SetAuthority(CDvmData *pData)
{
	SetValue(pData->m_strID, pData->m_strValue);
}

void CSttTestClientUser::OnLogout()
{
	DeleteAll();
	ID_Tester(0);

// 	SetAuthority(KEY_AUTHORITY_MODULE_Test, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_Ats, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_PpMmsEngine, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_PpEngine, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_SttTestStudio, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_SttTestCntr, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_Iec61850Config, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_DvmTest, 0);
// 	SetAuthority(KEY_AUTHORITY_MODULE_SmartTest, 0);
}

void CSttTestClientUser::AnalysisLoginUser(CSttSystemCmd &oSysCmd)
{
	CSttParas* pParas = oSysCmd.GetSttParas();
	
	if (pParas == NULL)
	{
		return;
	}

	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pParas->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pData = (CDvmData *)p;

		SetValue(pData->m_strID, pData->m_strValue);
	}
}

void CSttTestClientUser::InitSttSystemCmd(CSttSystemCmd &oSysCmd)
{
	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while(pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);

		oSysCmd.AddNewParasData(p->m_strID, p->m_strValue);
	}
}

void CSttTestClientUser::SetAuthoritys(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	long nValue = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);
		nValue = CString_To_long(pData->m_strValue);
		SetAuthority(pData->m_strID, nValue);
	}
}

void CSttTestClientUser::ClearAuthoritys(CExBaseList *pParas)
{
	POS pos = pParas->GetHeadPosition();
	CDvmData *pData = NULL;
	long nValue = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pParas->GetNext(pos);
		nValue = CString_To_long(pData->m_strValue);
		
		if (nValue == 1)
		{
			SetAuthority(pData->m_strID, 0);
		}
	}
}

void CSttTestClientUser::SetIDTest(long nIDTest)
{
	ID_Tester(nIDTest);

	if (m_pRefSttSckt != NULL)
	{
		m_pRefSttSckt->m_nIDTester = nIDTest;
	}
}

long CSttTestClientUser::CompareUserPriority(CSttTestClientUser *pUser)
{
	if (pUser == NULL)
	{
		return 1;
	}

	if (ID_Terminal() == pUser->ID_Terminal())
	{
		return 0;
	}

	if (IsTerminalType_Native() 
		|| IsTerminalType_OwnTest()
		|| IsTerminalType_OwnAts())
	{
		return 1;
	}

	if (IsTerminalType_Remote())
	{
		return -1;
	}

	if (pUser->IsTerminalType_Native()
		|| pUser->IsTerminalType_OwnTest()
		|| pUser->IsTerminalType_OwnAts())
	{
		return -1;
	}

	return 1;
}