// EpotoInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpotoInterface.h"
#include "..\XLanguage\XLanguageResource.h"

// EP_GETEPOTOSTRING 								Pp_GetEpotoString = NULL;


#define EPOTO_STRING_ID_EPOTO     0X00F00000
#define EPOTO_STRING_ID_DEV       0X00F00001
#define EPOTO_STRING_ID_COMPANY   0X00F00002
#define EPOTO_STRING_ID_USER      0X00F00003
#define EPOTO_STRING_ID_TITLE     0X00F00004
#define EPOTO_STRING_ID_MAIL      0X00F00005
#define EPOTO_STRING_ID_TEL       0X00F00006
#define EPOTO_STRING_ID_QQ        0X00F00007
#define EPOTO_STRING_ID_AUTHORITY 0X00F00008

#ifdef _use_safenet_dog

BOOL HasLoadEpotoLib()
{
	return TRUE;
}

void ReleaseEpotoLib()
{
	
}

BOOL LoadEpotoLib(const CString &strPath)
{
	return TRUE;
}

LONG GetEpotoString(long nStringID, char *pString, long &nStringLen)
{
	CString strText;

	switch (nStringID)
	{
	case EPOTO_STRING_ID_COMPANY:
		strText = g_sLangTxt_RightsReserved/*_T("版权所有：")*/ + hasp_get_ownership();
		CString_to_char(strText, pString);
		nStringLen = strlen(pString);
		break;

	case EPOTO_STRING_ID_USER:
		strText = g_sLangTxt_LicensedTo/*_T("授权给：")*/ + hasp_get_user_cop();
		CString_to_char(strText, pString);
		nStringLen = strlen(pString);
		break;

	default:
		*pString = 0;
		nStringLen = 0;
		break;
	}
	return 0;
}

BOOL Encrypt_IsEncrypt_Devlop(UINT nFetureID, BOOL bShowHaspMsg)
{
	return Encrypt_IsEncrypt(nFetureID, bShowHaspMsg);
}

BOOL Encrypt_IsEncrypt(UINT nFetureID, BOOL bShowHaspMsg)
{
	if (!CSafenet_Login::hasp_has_catalog(nFetureID, bShowHaspMsg))
	{
		return FALSE;
	}

	return TRUE;
}

#else
//////////////////////////////////////////////////////////////////////////
HINSTANCE g_hEpotoLib;

BOOL HasLoadEpotoLib()
{
	return (g_hEpotoLib != NULL);
}

void ReleaseEpotoLib()
{
	if (g_hEpotoLib != NULL)
	{
		FreeLibrary(g_hEpotoLib);
		g_hEpotoLib = NULL;
	}
}


LONG GetEpotoString(long nStringID, char *pString, long &nStringLen)
{
	CString strText;

	switch (nStringID)
	{
	case EPOTO_STRING_ID_COMPANY:
		strText = _T("版权所有：") + Encrypt_GetCompany();
		CString_to_char(strText, pString);
		nStringLen = strlen(pString);
		break;

	case EPOTO_STRING_ID_USER:
		strText = _T("授权：") + Encrypt_GetUser();
		CString_to_char(strText, pString);
		nStringLen = strlen(pString);
		break;

	default:
		*pString = 0;
		nStringLen = 0;
		break;
	}
	return 0;
}


BOOL LoadEpotoLib(const CString &strPath)
{
// 	ReleaseEpotoLib();
// 
// 	CString strDll = strPath;
// 	strDll = strDll.Left(strPath.GetLength() - 1);
// 	long nPos = strDll.ReverseFind('\\');
// 	strDll = strDll.Left(nPos);
// 	strDll += _T("\\Common\\Bin\\Epoto.dll");
// 
// 	BOOL bSucc = TRUE;
// 	g_hEpotoLib = LoadLibrary(strDll);
// 
// 	if(g_hEpotoLib != NULL)
// 	{
// 		Pp_GetEpotoString = (EP_GETEPOTOSTRING)GetProcAddress(g_hEpotoLib, "Ep_GetEpotoString");
// 	}
// 	else
// 	{
// 		bSucc = FALSE;
// 	}	
// 
// 	return bSucc;
	Pp_GetEpotoString = GetEpotoString;
	
#ifdef use_Encrypt_SafeNetTool
	Encrypt_RegisterSafeNetTool();
#else
	Encrypt_RegisterFileTool();
#endif

	return Encrypt_IsEncrypt();
}


BOOL Encrypt_IsEncrypt_Demo()
{
	CString strMode = g_pEncryptTool->GetMode();

	if (strMode == Encrypt_Mode_Demo)
	{
		DWORD dwTimeEnd = g_pEncryptTool->GetEndTime();
		DWORD dwTimeBegin = g_pEncryptTool->GetBeginTime();
		SYSTEMTIME tmSys;
		::GetLocalTime(&tmSys);
		DWORD dwTimeCurr = 0;
		dwTimeCurr = Encrypt_GetTime(tmSys);
		
		if (dwTimeBegin <= dwTimeCurr && dwTimeCurr <= dwTimeEnd)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL Encrypt_IsEncrypt_Test()
{
	CString strMode = g_pEncryptTool->GetMode();

	if (strMode == Encrypt_Mode_Test)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL Encrypt_IsEncrypt_Devlop(UINT nFetureID)
{
	CString strMode = g_pEncryptTool->GetMode();

	if (strMode == Encrypt_Mode_Develop)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL Encrypt_IsEncrypt_CanUseAutoTest()
{
	if (!Encrypt_IsEncrypt())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("你使用的系统没有授权"));
		return FALSE;
	}

	if (Encrypt_IsEncrypt_Devlop())
	{
		return TRUE;
	}

	if (Encrypt_IsEncrypt_Test())
	{
		return TRUE;
	}

	if (Encrypt_IsEncrypt_Demo())
	{
		return TRUE;
	}

	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("你使用的系统没有授权"));

	return FALSE;
}

#endif

#ifdef ENCRYPT_USE_REGISTER_FILE
#include "../Encrypt/EncryptTool.h"

BOOL Encrypt_IsEncrypt_CanUseAutoTest()
{
	if (Encrypt_IsUseRegisterFile())
	{
		return Encrypt_IsEncrypt();
	}
	else
	{
		if ( CSafenet_Login::hasp_is_overdue() )
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
}
#endif
