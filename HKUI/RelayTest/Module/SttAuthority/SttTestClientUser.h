#pragma once
#include "SttTestRemoteRegister.h"
#include "../SttSocket/SttSocketDataBase.h"

class CSttTestClientUser : public CDvmData
{
public:
	CSttTestClientUser();
	virtual ~CSttTestClientUser();

public:
	virtual BOOL IsEqual(CBaseObject* pObj);

	CString os();
	void os(const CString &strValue);
	CString id_soft();
	void id_soft(const CString &strValue);
	CString ver_soft();
	void ver_soft(const CString &strValue);
	CString ID_Terminal();
	void ID_Terminal(const CString &strValue);
	CString SN_TestApp();
	void SN_TestApp(const CString &strValue);
	CString Code_Register();
	void Code_Register(const CString &strValue);
	CString Name_Cop();
	void Name_Cop(const CString &strValue);
	CString Name_User();
	void Name_User(const CString &strValue);
	CString IP_User();
	void IP_User(const CString &strValue);
	DWORD ID_Tester();
	void ID_Tester(DWORD nValue);
	void SetLogInTime();

	BOOL HasAuthority(const CString &strModuleID);
	void SetAuthority(const CString &strModuleID, long nValue);
	void SetAuthority(CDvmData *pData);
	void SetAuthoritys(CExBaseList *pParas);
	void ClearAuthoritys(CExBaseList *pParas);
	long CompareUserPriority(CSttTestClientUser *pUser);

public:
	DWORD GetIDTest();
	void SetIDTest(long nIDTest);
	BOOL IsMatchIDTest(long nIDTest)	{	return (GetIDTest() == nIDTest);	}
	void OnLogout();

public:
	CSttXcmdChInterface *m_pRefSttSckt;
	void SetRefSttSckt(CSttXcmdChInterface *pRefSttSckt){	m_pRefSttSckt = pRefSttSckt;	}

public:
	BOOL IsTerminalType_Remote()	{	return (ID_Terminal() == STT_TERMINAL_TYPE_REMOTE);	}
	BOOL IsTerminalType_Local()		{	return (ID_Terminal() == STT_TERMINAL_TYPE_LOCAL);	}
	BOOL IsTerminalType_Native()	{	return (ID_Terminal() == STT_TERMINAL_TYPE_NATIVE);	}
	BOOL IsTerminalType_OwnAts()	{	return (ID_Terminal() == STT_TERMINAL_TYPE_NATIVE_ATS);	}
	BOOL IsTerminalType_OwnTest()	{	return (ID_Terminal() == STT_TERMINAL_TYPE_NATIVE_TEST);	}
	BOOL IsTerminalType_TestControl()	{	return (ID_Terminal() == STT_TERMINAL_TYPE_NATIVE_TESTCONTROL);	}

// 	BOOL HasAuthority(const CString &strModuleID){	return m_oModuleAuthorityMngr.HasAuthority(strModuleID);	}
// 	void SetAuthority(const CString &strModuleID, long nValue){	return m_oModuleAuthorityMngr.SetAuthority(strModuleID,nValue);	}
	
public:
	void AnalysisLoginUser(CSttSystemCmd &oSysCmd);
	void InitSttSystemCmd(CSttSystemCmd &oSysCmd);
};

/////////////////////////////
static long g_nSttCurrGenerateLocalID = 0;

inline long stt_GenerateLocalID()
{
	g_nSttCurrGenerateLocalID++;

	if (g_nSttCurrGenerateLocalID > 32767)
	{
		g_nSttCurrGenerateLocalID = 0;
	}

	return g_nSttCurrGenerateLocalID;
}

// inline long stt_generate_idtester()
// {
//	return 2;
//}